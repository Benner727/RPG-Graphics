#include "Mining.h"

#include "Skills.h"
#include "Inventory.h"
#include "Equipment.h"

Mining::Mining(Player* player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mBackground = new Texture("DirtBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mMineText = nullptr;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	mMining = false;
	mCurrentOre = 0;

	mOres[0] = new Ore(0, Vector2(350.0f, 500.0f));
	mOres[1] = new Ore(1, Vector2(265.0f, 75.0f));
	mOres[2] = new Ore(2, Vector2(335.0f, 75.0f));
	mOres[3] = new Ore(3, Vector2(250.0f, 250.0f));
	mOres[4] = new Ore(4, Vector2(150.0f, 150.0f));
	mOres[5] = new Ore(5, Vector2(275.0f, 375.0f));
	mOres[6] = new Ore(6, Vector2(100.0f, 275.0f));
	mOres[7] = new Ore(7, Vector2(100.0f, 400.0f));
	mOres[8] = new Ore(8, Vector2(150.0f, 450.0f));
	mOres[9] = new Ore(9, Vector2(200.0f, 500.0f));

	exitMining = false;
}

Mining::~Mining()
{
	mPlayer = nullptr;

	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	if (mMineText != nullptr)
	{
		delete mMineText;
		mMineText = nullptr;
	}

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void Mining::Update()
{
	static int mStartTicks = SDL_GetTicks();

	OreUpdate();

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
		{
			mMining - false;
			exitMining = true;
		}

		for (int i = 0; i < 10; i++)
		{
			if (mOres[i]->mTex->Intersects(mInputManager->MousePos()) && !mOres[i]->mDepleted)
			{
				if (!mMining || mCurrentOre != i)
					mStartTicks = SDL_GetTicks();

				mMining = true;
				mCurrentOre = i;
			}
		}
	}

	if (mMining && (SDL_GetTicks() > mStartTicks + 600))
	{
		mine();
		mStartTicks = SDL_GetTicks();
	}

	for (int i = 0; i < 10; i++)
	{
		if (mOres[i]->mTex->Intersects(mInputManager->MousePos()) && !mOres[i]->mDepleted)
		{
			if (mMining)
				if (mCurrentOre == i)
					break;

			if (mMineText == nullptr)
				mMineText = new Texture("Mine", "alagard.ttf", 24, { 255, 255, 0 });

			mMineText->Pos(mInputManager->MousePos());
			break;
		}
		else if (mMineText != nullptr)
		{
			delete mMineText;
			mMineText = nullptr;
		}
	}
}

void Mining::Render()
{
	mBackground->Render();
	mEscapeButton->Render();

	for (int i = 0; i < 10; i++)
		if (!mOres[i]->mDepleted)
			mOres[i]->mTex->Render();

	if (mMineText != nullptr)
		mMineText->Render();
}

void Mining::OreUpdate()
{
	for (int i = 0; i < 10; i++)
	{
		if (mOres[i]->mDepleted)
		{
			mOres[i]->mTimer--;

			if (mOres[i]->mTimer < 1)
			{
				if (rand() % 5)
					mOres[i]->mDepleted = false;
				else
					mOres[i]->mTimer = 60 * i;
			}
		}
	}
}

void Mining::mine()
{
	static int callNum = 0;
	callNum++;

	int base = 0, bonus = -1,
		pickaxes[8] = { 236, 238, 240, 242, 244, 246, 248, 250 },
		req[8] = { 1, 1, 6, 11, 21, 31, 41, 61 },
		playerChance,
		gem = rand() % 100;
	bool success = false;

	if (!mPlayer->inventory->getFreeSlots())
	{
		mMining = false;
		return;
	}

	if (!mOres[mCurrentOre]->mDepleted)
	{
		for (int i = 0; i < 8; i++)
		{
			if (mPlayer->equipment->getItem(3) != nullptr)
			{
				if (mPlayer->equipment->getItem(3)->getId() == pickaxes[i])
				{
					if (mPlayer->skills->getLevel(SKILL::mining) >= req[i])
					{
						if (bonus < i)
							bonus = i;
					}
				}
			}

			if (mPlayer->inventory->hasItem(pickaxes[i]))
			{
				if (mPlayer->skills->getLevel(SKILL::mining) >= req[i])
				{
					if (bonus < i)
						bonus = i;
				}
			}
		}

		if (bonus == -1)
		{
			mMining = false;
			return;
		}

		switch (mOres[mCurrentOre]->mIndex)
		{
		case 0: //Essence
			base = 4;
			break;
		case 1: //Copper
			base = 8;
			break;
		case 2: //Tin
			base = 8;
			break;
		case 3: //Iron
			base = 16;
			if (mPlayer->skills->getLevel(SKILL::mining) < 15)
			{
				mMining = false;
				return;
			}
			break;
		case 4: //Coal
			base = 32;
			if (mPlayer->skills->getLevel(SKILL::mining) < 30)
			{
				mMining = false;
				return;
			}
			break;
		case 5: //Gold
			base = 40;
			if (mPlayer->skills->getLevel(SKILL::mining) < 40)
			{
				mMining = false;
				return;
			}
			break;
		case 6: //Gems
			base = 40;
			if (mPlayer->skills->getLevel(SKILL::mining) < 40)
			{
				mMining = false;
				return;
			}
			break;
		case 7: //Mithril
			base = 60;
			if (mPlayer->skills->getLevel(SKILL::mining) < 55)
			{
				mMining = false;
				return;
			}
			break;
		case 8: //Adamant
			base = 90;
			if (mPlayer->skills->getLevel(SKILL::mining) < 70)
			{
				mMining = false;
				return;
			}
			break;
		case 9: //Rune
			base = 125;
			if (mPlayer->skills->getLevel(SKILL::mining) < 85)
			{
				mMining = false;
				return;
			}
			break;
		}

		playerChance = (base - ((mPlayer->skills->getEffect(SKILL::mining) + bonus) / 3));
		if (playerChance < 1)
			playerChance = 1;

		if (callNum % 2) mAudioManager->PlaySFX("ImpactStone.wav", 0, 1);

		if (!(rand() % playerChance)) //Roll for ore (use Formula)
		{
			switch (mOres[mCurrentOre]->mIndex)
			{
			case 0:
				mPlayer->inventory->add(Item(218, 1));
				mPlayer->skills->addExperience(5, SKILL::mining);
				break;
			case 1:
				mPlayer->inventory->add(Item(220, 1));
				mPlayer->skills->addExperience(18, SKILL::mining);
				break;
			case 2:
				mPlayer->inventory->add(Item(222, 1));
				mPlayer->skills->addExperience(18, SKILL::mining);
				break;
			case 3:
				mPlayer->inventory->add(Item(224, 1));
				mPlayer->skills->addExperience(35, SKILL::mining);
				break;
			case 4:
				mPlayer->inventory->add(Item(226, 1));
				mPlayer->skills->addExperience(50, SKILL::mining);
				break;
			case 5:
				mPlayer->inventory->add(Item(228, 1));
				mPlayer->skills->addExperience(70, SKILL::mining);
				break;
			case 6:
				if (gem < 77)
					mPlayer->inventory->add(Item(842, 1));
				else if (gem < 86)
					mPlayer->inventory->add(Item(844, 1));
				else if (gem < 91)
					mPlayer->inventory->add(Item(846, 1));
				else if (gem < 96)
					mPlayer->inventory->add(Item(848, 1));
				else if (gem < 100)
					mPlayer->inventory->add(Item(850, 1));

				mPlayer->skills->addExperience(65, SKILL::mining);
				break;
			case 7:
				mPlayer->inventory->add(Item(230, 1));
				mPlayer->skills->addExperience(80, SKILL::mining);
				break;
			case 8:
				mPlayer->inventory->add(Item(232, 1));
				mPlayer->skills->addExperience(95, SKILL::mining);
				break;
			case 9:
				mPlayer->inventory->add(Item(234, 1));
				mPlayer->skills->addExperience(125, SKILL::mining);
				break;
			}

			success = true;
		}

		if (mCurrentOre == 4 || mCurrentOre == 6)
		{
			if (success && !(rand() % 6))
			{
				mOres[mCurrentOre]->mDepleted = true;
				mOres[mCurrentOre]->mTimer = 60 * mCurrentOre;
				mMining = false;
			}
		}
		else if (success && !(rand() % 3))
		{
			if (mCurrentOre)
			{
				mOres[mCurrentOre]->mDepleted = true;
				mOres[mCurrentOre]->mTimer = 60 * mCurrentOre;
				mMining = false;
			}
		}
	}
}