#include "Fishing.h"

#include "Skills.h"
#include "Inventory.h"
#include "Equipment.h"

Fishing::Fishing(Player *player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mBackground = new Texture("WaterBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	mFishing = false;
	mCurrentSpot = 0;

	exitFishing = false;

	mSpots[0] = new Spot(0, Vector2(100.0f, 150.0f));
	mSpots[1] = new Spot(1, Vector2(250.0f, 75.0f));
	mSpots[2] = new Spot(2, Vector2(100.0f, 420.0f));
	mSpots[3] = new Spot(3, Vector2(300.0f, 500.0f));
	mSpots[4] = new Spot(4, Vector2(200.0f, 300.0f));
	mSpots[5] = new Spot(5, Vector2(325.0f, 185.0f));
}

Fishing::~Fishing()
{
	mPlayer = nullptr;

	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mEscapeButton;
	mEscapeButton = nullptr;

	for (int i = 0; i < 6; i++)
	{
		delete mSpots[i];
		mSpots[i] = nullptr;
	}
}

void Fishing::Update()
{
	static int mStartTicks = SDL_GetTicks();

	SpotUpdate();

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
		{
			mFishing - false;
			exitFishing = true;
		}

		for (int i = 0; i < 6; i++)
		{
			mSpots[i]->mTex->Update();

			if (mSpots[i]->mTex->Intersects(mInputManager->MousePos()))
			{
				if (!mFishing || mCurrentSpot != i)
					mStartTicks = SDL_GetTicks();

				mFishing = true;
				mCurrentSpot = i;
			}
		}
	}

	if (mFishing && (SDL_GetTicks() > mStartTicks + 600))
	{
		fish();
		mStartTicks = SDL_GetTicks();
	}
}

void Fishing::Render()
{
	mBackground->Render();
	mEscapeButton->Render();

	for (int i = 0; i < 6; i++)
		mSpots[i]->mTex->Render();

	for (int i = 0; i < 6; i++)
	{
		if (mSpots[i]->mTex->Intersects(mInputManager->MousePos()))
		{
			if (mFishing)
				if (mCurrentSpot == i)
					break;

			mSpots[i]->mNameText->Pos(mInputManager->MousePos());
			mSpots[i]->mNameText->Render();
			break;
		}
	}
}

void Fishing::SpotUpdate()
{
	for (int i = 0; i < 6; i++)
		mSpots[i]->mTex->Update();
}

void Fishing::fish()
{
	static int callNum = 0;
	callNum++;

	int option = GetOption(),
	base, playerChance;

	if (!mPlayer->inventory->getFreeSlots())
	{
		mFishing = false;
		return;
	}

	switch (option)
	{
	case 0:
		base = 8;
		break;
	case 1:
		base = 16;
		break;
	case 2:
		base = 32;
		break;
	case 3:
		base = 48;
		break;
	case 4:
		base = 80;
		break;
	case 5:
		base = 64;
		break;
	case 6:
		base = 48;
		break;
	case 7:
		base = 120;
		break;
	case 8:
		base = 64;
		break;
	case 9:
		base = 96;
		break;
	case 10:
		base = 200;
		break;
	default:
		mFishing = false;
	}

	if (mFishing)
	{
		playerChance = (base - ((mPlayer->skills->getEffect(SKILL::fishing)) / 3));
		if (playerChance < 1)
			playerChance = 1;

		if (!(callNum % 5)) mAudioManager->PlaySFX("splash2.wav", 0, 1);

		if (!(rand() % playerChance))
		{
			switch (option)
			{
			case 0:
				if (mPlayer->skills->getEffect(fishing) >= 15) //shrimp and anchovies
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(131, 1));
						mPlayer->skills->addExperience(10, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(137, 1));
						mPlayer->skills->addExperience(40, fishing);
					}
				}
				else
				{
					mPlayer->inventory->add(Item(131, 1));
					mPlayer->skills->addExperience(10, fishing);
				}
				break;
			case 1:
				if (mPlayer->skills->getEffect(fishing) >= 10) //sardine and herring
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(133, 1));
						mPlayer->skills->addExperience(20, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(135, 1));
						mPlayer->skills->addExperience(30, fishing);
					}
					mPlayer->inventory->removeItem(207, 1);
				}
				else
				{
					mPlayer->inventory->add(Item(133, 1));
					mPlayer->skills->addExperience(20, fishing);
					mPlayer->inventory->removeItem(207, 1);
				}
				break;
			case 2:
				if (mPlayer->skills->getEffect(fishing) >= 30) //trout and salmon
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(141, 1));
						mPlayer->skills->addExperience(50, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(147, 1));
						mPlayer->skills->addExperience(70, fishing);
					}
					mPlayer->inventory->removeItem(57, 1);
				}
				else
				{
					mPlayer->inventory->add(Item(141, 1));
					mPlayer->skills->addExperience(50, fishing);
					mPlayer->inventory->removeItem(57, 1);
				}
				break;
			case 3:
				mPlayer->inventory->add(Item(145, 1));
				mPlayer->skills->addExperience(60, fishing);
				mPlayer->inventory->removeItem(207, 1);
				break;
			case 4:
				mPlayer->inventory->add(Item(151, 1));
				mPlayer->skills->addExperience(90, fishing);
				break;
			case 5:
				if (mPlayer->skills->getEffect(fishing) >= 50) //tuna and swordfish
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(149, 1));
						mPlayer->skills->addExperience(80, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(155, 1));
						mPlayer->skills->addExperience(100, fishing);
					}
				}
				else
				{
					mPlayer->inventory->add(Item(149, 1));
					mPlayer->skills->addExperience(80, fishing);
				}
				break;
			case 6:
				if (mPlayer->skills->getEffect(fishing) >= 46) //mackerel, cod and bass
				{
					switch (rand() % 3)
					{
					case 0:
						mPlayer->inventory->add(Item(139, 1));
						mPlayer->skills->addExperience(20, fishing);
						break;
					case 1:
						mPlayer->inventory->add(Item(143, 1));
						mPlayer->skills->addExperience(45, fishing);
						break;
					case 2:
						mPlayer->inventory->add(Item(153, 1));
						mPlayer->skills->addExperience(100, fishing);
						break;
					}
				}
				else if (mPlayer->skills->getEffect(fishing) >= 23)
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(139, 1));
						mPlayer->skills->addExperience(20, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(143, 1));
						mPlayer->skills->addExperience(45, fishing);
					}
				}
				else
				{
					mPlayer->inventory->add(Item(139, 1));
					mPlayer->skills->addExperience(20, fishing);
				}
				break;
			case 7:
				mPlayer->inventory->add(Item(159, 1));
				mPlayer->skills->addExperience(110, fishing);
				break;
			case 8:
				if (mPlayer->skills->getEffect(fishing) >= 50) //tuna and swordfish
				{
					if (rand() % 2)
					{
						mPlayer->inventory->add(Item(149, 1));
						mPlayer->skills->addExperience(80, fishing);
					}
					else
					{
						mPlayer->inventory->add(Item(155, 1));
						mPlayer->skills->addExperience(100, fishing);
					}
				}
				else
				{
					mPlayer->inventory->add(Item(149, 1));
					mPlayer->skills->addExperience(80, fishing);
				}
				break;
			case 9:
				mPlayer->inventory->add(Item(157, 1));
				mPlayer->skills->addExperience(120, fishing);
				break;
			case 10:
				mPlayer->inventory->add(Item(161, 1));
				mPlayer->skills->addExperience(150, fishing);
				break;
			}
		}
	}
}

int Fishing::GetOption()
{
	int option = -1;

	switch (mCurrentSpot)
	{
	case 0: //Net / Bait
		if (mPlayer->inventory->hasItem(195))
		{
			if (mPlayer->skills->getEffect(fishing) >= 1)
				option = 0;
		}
		else if (mPlayer->inventory->hasItem(199) && mPlayer->inventory->hasItem(207))
		{
			if (mPlayer->skills->getEffect(fishing) >= 5)
				option = 1;
		}
		else
			mFishing = false;
		break;
	case 1: //Lure / Bait
		if (mPlayer->inventory->hasItem(201) && mPlayer->inventory->hasItem(57))
		{
			if (mPlayer->skills->getEffect(fishing) >= 20)
				option = 2;
		}
		else if (mPlayer->inventory->hasItem(199) && mPlayer->inventory->hasItem(207))
		{
			if (mPlayer->skills->getEffect(fishing) >= 25)
				option = 3;
		}
		else
			mFishing = false;
		break;
	case 2: //Cage / Harpoon
		if (mPlayer->inventory->hasItem(205))
		{
			if (mPlayer->skills->getEffect(fishing) >= 40)
				option = 4;
		}
		else if (mPlayer->inventory->hasItem(203))
		{
			if (mPlayer->skills->getEffect(fishing) >= 35)
				option = 5;
		}
		else
			mFishing = false;
		break;
	case 3: //Big Net / Harpoon
		if (mPlayer->inventory->hasItem(197) && (mPlayer->skills->getEffect(fishing) >= 16))
			option = 6;
		else if (mPlayer->inventory->hasItem(203) && (mPlayer->skills->getEffect(fishing) >= 76))
			option = 7;
		else
			mFishing = false;
		break;
	case 4: //Harpoon / Small Net
		if (mPlayer->inventory->hasItem(203) && (mPlayer->skills->getEffect(fishing) >= 35))
			option = 8;
		else if (mPlayer->inventory->hasItem(195) && (mPlayer->skills->getEffect(fishing) >= 62))
			option = 9;
		else
			mFishing = false;
		break;
	case 5:
		if (mPlayer->inventory->hasItem(197) && mPlayer->skills->getEffect(SKILL::fishing) >= 90)
			option = 10;
		else
			mFishing = false;
		break;
	}

	return option;
}