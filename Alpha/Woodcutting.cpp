#include "Woodcutting.h"

#include "Skills.h"
#include "Inventory.h"
#include "Equipment.h"

Woodcutting::Woodcutting(Player *player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mBackground = new Texture("GrassBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mChopText = nullptr;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	mChopping = false;
	mCurrentTree = 0;

	exitWoodcutting = false;

	mTrees[0] = new Tree(0, Vector2(50.0f, 100.0f));
	mTrees[1] = new Tree(0, Vector2(50.0f, 175.0f));
	mTrees[2] = new Tree(0, Vector2(50.0f, 250.0f));
	mTrees[3] = new Tree(0, Vector2(50.0f, 325.0f));
	mTrees[4] = new Tree(0, Vector2(125.0f, 100.0f));
	mTrees[5] = new Tree(1, Vector2(230.0f, 125.0f));
	mTrees[6] = new Tree(1, Vector2(280.0f, 75.0f));
	mTrees[7] = new Tree(1, Vector2(365.0f, 125.0f));
	mTrees[8] = new Tree(1, Vector2(302.0f, 150.0f));
	mTrees[9] = new Tree(1, Vector2(210.0f, 50.0f));
	mTrees[10] = new Tree(2, Vector2(350.0f, 250.0f));
	mTrees[11] = new Tree(2, Vector2(300.0f, 300.0f));
	mTrees[12] = new Tree(2, Vector2(350.0f, 350.0f));
	mTrees[13] = new Tree(2, Vector2(300.0f, 410.0f));
	mTrees[14] = new Tree(2, Vector2(360.0f, 470.0f));
	mTrees[15] = new Tree(3, Vector2(75.0f, 400.0f));
	mTrees[16] = new Tree(3, Vector2(150.0f, 430.0f));
	mTrees[17] = new Tree(3, Vector2(200.0f, 500.0f));
	mTrees[18] = new Tree(3, Vector2(275.0f, 550.0f));
	mTrees[19] = new Tree(4, Vector2(200.0f, 325.0f));
	mTrees[20] = new Tree(4, Vector2(75.0f, 525.0f));
	mTrees[21] = new Tree(5, Vector2(180.0f, 225.0f));
}

Woodcutting::~Woodcutting()
{
	mPlayer = nullptr;

	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	if (mChopText != nullptr)
	{
		delete mChopText;
		mChopText = nullptr;
	}

	delete mEscapeButton;
	mEscapeButton = nullptr;

	for (int i = 0; i < 22; i++)
	{
		delete mTrees[i];
		mTrees[i] = nullptr;
	}
}

void Woodcutting::Update()
{
	static int mStartTicks = SDL_GetTicks();

	TreeUpdate();

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
		{
			mChopping - false;
			exitWoodcutting = true;
		}
		
		for (int i = 0; i < 22; i++)
		{
			if (mTrees[i]->mTex->Intersects(mInputManager->MousePos()) && !mTrees[i]->mFallen)
			{
				if (!mChopping || mCurrentTree != i)
					mStartTicks = SDL_GetTicks();

				mChopping = true;
				mCurrentTree = i;
			}
		}
	}

	if (mChopping && (SDL_GetTicks() > mStartTicks + 600))
	{
		chop();
		mStartTicks = SDL_GetTicks();
	}

	for (int i = 0; i < 22; i++)
	{
		if (mTrees[i]->mTex->Intersects(mInputManager->MousePos()) && !mTrees[i]->mFallen)
		{
			if (mChopping)
				if (mCurrentTree == i)
					break;

			if (mChopText == nullptr)
				mChopText = new Texture("Chop", "alagard.ttf", 24, { 255, 255, 0 });

			mChopText->Pos(mInputManager->MousePos());
			break;
		}
		else if (mChopText != nullptr)
		{
			delete mChopText;
			mChopText = nullptr;
		}
	}
}

void Woodcutting::Render()
{
	mBackground->Render();
	mEscapeButton->Render();

	for (int i = 0; i < 22; i++)
		if (!mTrees[i]->mFallen)
			mTrees[i]->mTex->Render();

	if (mChopText != nullptr)
		mChopText->Render();
}

void Woodcutting::TreeUpdate()
{
	for (int i = 0; i < 22; i++)
	{
		if (mTrees[i]->mFallen)
		{
			mTrees[i]->mTimer--;

			if (mTrees[i]->mTimer == 0)
			{
				if (rand() % 4)
					mTrees[i]->mFallen = false;
				else
					mTrees[i]->mTimer = 600;
			}
		}
	}
}

void Woodcutting::chop()
{
	static int callNum = 0;
	callNum++;

	int base = 0, bonus = -1,
		axes[8] = { 12, 14, 16, 18, 20, 22, 24, 26 },
		req[8] = {1, 1, 6, 11, 21, 31, 41, 61},
		playerChance;
	bool success = false;

	if (!mPlayer->inventory->getFreeSlots())
	{
		mChopping = false;
		return;
	}

	if (!mTrees[mCurrentTree]->mFallen)
	{
		for (int i = 0; i < 8; i++)
		{
			if (mPlayer->equipment->getItem(3) != nullptr)
			{
				if (mPlayer->equipment->getItem(3)->getId() == axes[i])
				{
					if (mPlayer->skills->getLevel(SKILL::woodcutting) >= req[i])
					{
						if (bonus < i)
							bonus = i;
					}
				}
			}

			if (mPlayer->inventory->hasItem(axes[i]))
			{
				if (mPlayer->skills->getLevel(SKILL::woodcutting) >= req[i])
				{
					if (bonus < i)
						bonus = i;
				}
			}
		}

		if (bonus == -1)
		{
			mChopping = false;
			return;
		}

		switch (mTrees[mCurrentTree]->mIndex)
		{
		case 0:
			base = 8;
			break;
		case 1:
			base = 16;
			if (mPlayer->skills->getLevel(SKILL::woodcutting) < 15)
			{
				mChopping = false;
				return;
			}
			break;
		case 2:
			base = 32;
			if (mPlayer->skills->getLevel(SKILL::woodcutting) < 30)
			{
				mChopping = false;
				return;
			}
			break;
		case 3:
			base = 40;
			if (mPlayer->skills->getLevel(SKILL::woodcutting) < 40)
			{
				mChopping = false;
				return;
			}
			break;
		case 4:
			base = 60;
			if (mPlayer->skills->getLevel(SKILL::woodcutting) < 61)
			{
				mChopping = false;
				return;
			}
			break;
		case 5:
			base = 100;
			if (mPlayer->skills->getLevel(SKILL::woodcutting) < 75)
			{
				mChopping = false;
				return;
			}
			break;
		}

		playerChance = (base - ((mPlayer->skills->getEffect(SKILL::woodcutting) + bonus) / 3));
		if (playerChance < 1)
			playerChance = 1;

		if (callNum % 2) mAudioManager->PlaySFX("ImpactWood.wav", 0, 1);

		if (!(rand() % 50)) //Roll for bird's nest (1 / 50)
		{
			switch (mTrees[mCurrentTree]->mIndex)
			{
			case 0:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(25, SKILL::woodcutting);
				break;
			case 1:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(38, SKILL::woodcutting);
				break;
			case 2:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(68, SKILL::woodcutting);
				break;
			case 3:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(100, SKILL::woodcutting);
				break;
			case 4:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(175, SKILL::woodcutting);
				break;
			case 5:
				mPlayer->inventory->add(Item(593, 1));
				mPlayer->skills->addExperience(250, SKILL::woodcutting);
				break;
			}

			success = true;
		}
		else if (!(rand() % playerChance)) //Roll for log (use Formula)
		{
			switch (mTrees[mCurrentTree]->mIndex)
			{
			case 0:
				mPlayer->inventory->add(Item(0, 1));
				mPlayer->skills->addExperience(25, SKILL::woodcutting);
				break;
			case 1:
				mPlayer->inventory->add(Item(2, 1));
				mPlayer->skills->addExperience(38, SKILL::woodcutting);
				break;
			case 2:
				mPlayer->inventory->add(Item(4, 1));
				mPlayer->skills->addExperience(68, SKILL::woodcutting);
				break;
			case 3:
				mPlayer->inventory->add(Item(6, 1));
				mPlayer->skills->addExperience(100, SKILL::woodcutting);
				break;
			case 4:
				mPlayer->inventory->add(Item(8, 1));
				mPlayer->skills->addExperience(175, SKILL::woodcutting);
				break;
			case 5:
				mPlayer->inventory->add(Item(10, 1));
				mPlayer->skills->addExperience(250, SKILL::woodcutting);
				break;
			}

			success = true;
		}

		//Roll to fall tree if log obtained (1 / 8)
		//If tree fall roll is successfull, set timer to 9000
		if (success && !(rand() % 8))
		{
			mTrees[mCurrentTree]->mFallen = true;
			mTrees[mCurrentTree]->mTimer = 600;
			mChopping = false;
		}

	}
}