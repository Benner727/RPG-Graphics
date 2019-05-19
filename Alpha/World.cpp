#include "World.h"

#include "Inventory.h"

World::World(Player *player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();

	mBackground = new Texture("MapBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mWoodcutting = new Woodcutting(mPlayer);
	mMining = new Mining(mPlayer);
	mFishing = new Fishing(mPlayer);
	mRunecrafting = new Runecrafting(mPlayer);

	mWoodcuttingIcon = new Texture("WoodcuttingIcon.png");
	mWoodcuttingIcon->Pos(Vector2(150.0f, 250.0f));
	mWoodcuttingIcon->Scale(Vector2(3.0f, 3.0f));

	mMiningIcon = new Texture("MiningIcon.png");
	mMiningIcon->Pos(Vector2(351.0f, 360.0f));
	mMiningIcon->Scale(Vector2(3.0f, 3.0f));
	
	mFishingIcon = new Texture("FishingIcon.png");
	mFishingIcon->Pos(Vector2(80.0f, 527.0f));
	mFishingIcon->Scale(Vector2(3.0f, 3.0f));

	mRunecraftingIcon = new Texture("RunecraftingIcon.png");
	mRunecraftingIcon->Pos(Vector2(230.0f, 85.0f));
	mRunecraftingIcon->Scale(Vector2(3.0f, 3.0f));

	mFlax[0] = new Flax(Vector2(225.0f, 475.0f));
	mFlax[1] = new Flax(Vector2(260.0f, 475.0f));
	mFlax[2] = new Flax(Vector2(295.0f, 475.0f));
	mFlax[3] = new Flax(Vector2(330.0f, 475.0f));
	mFlax[4] = new Flax(Vector2(225.0f, 525.0f));
	mFlax[5] = new Flax(Vector2(260.0f, 525.0f));
	mFlax[6] = new Flax(Vector2(295.0f, 525.0f));
	mFlax[7] = new Flax(Vector2(330.0f, 525.0f));
	mFlax[8] = new Flax(Vector2(225.0f, 575.0f));
	mFlax[9] = new Flax(Vector2(260.0f, 575.0f));
	mFlax[10] = new Flax(Vector2(295.0f, 575.0f));
	mFlax[11] = new Flax(Vector2(330.0f, 575.0f));

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	mCurrentLocation = world;
}

World::~World()
{
	mPlayer = nullptr;

	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mWoodcutting;
	mWoodcutting = nullptr;

	delete mMining;
	mMining = nullptr;

	delete mFishing;
	mFishing = nullptr;

	delete mRunecrafting;
	mRunecrafting = nullptr;

	delete mWoodcuttingIcon;
	mWoodcuttingIcon = nullptr;

	delete mMiningIcon;
	mMiningIcon = nullptr;

	delete mFishingIcon;
	mFishingIcon = nullptr;

	delete mRunecraftingIcon;
	mRunecraftingIcon = nullptr;

	for (int i = 0; i < 12; i++)
	{
		delete mFlax[i];
		mFlax[i] = nullptr;
	}

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void World::Update()
{
	for (int i = 0; i < 12; i++)
	{
		if (mFlax[i]->picked)
			mFlax[i]->mTimer--;

		if (mFlax[i]->mTimer < 1)
		{
			if (rand() % 2)
				mFlax[i]->picked = false;
			else
				mFlax[i]->mTimer = 300;
		}
	}

	switch (mCurrentLocation)
	{
	case world:
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			if (mEscapeButton->Intersects(mInputManager->MousePos()))
				exitWorld = true;
			else if (mWoodcuttingIcon->Intersects(mInputManager->MousePos()))
				mCurrentLocation = woodcutting;
			else if (mMiningIcon->Intersects(mInputManager->MousePos()))
				mCurrentLocation = mining;
			else if (mFishingIcon->Intersects(mInputManager->MousePos()))
				mCurrentLocation = fishing;
			else if (mRunecraftingIcon->Intersects(mInputManager->MousePos()))
				mCurrentLocation = runecrafting;
			else
			{
				for (int i = 0; i < 12; i++)
				{
					if (!mFlax[i]->picked && mFlax[i]->mTex->Intersects(mInputManager->MousePos()))
					{
						if (mPlayer->inventory->getFreeSlots())
						{
							mPlayer->inventory->add(Item(28, 1));
							mFlax[i]->picked = true;
							mFlax[i]->mTimer = 300;
						}
					}
				}
			}
		}
		break;
	case woodcutting:
		mWoodcutting->Update();

		if (mWoodcutting->LeaveWoodcutting())
			mCurrentLocation = world;
		break;
	case mining:
		mMining->Update();

		if (mMining->LeaveMining())
			mCurrentLocation = world;
		break;
	case fishing:
		mFishing->Update();

		if (mFishing->LeaveFishing())
			mCurrentLocation = world;
		break;
	case runecrafting:
		mRunecrafting->Update();

		if (mRunecrafting->LeaveRunecrafting())
			mCurrentLocation = world;
	}
}

void World::Render()
{
	switch (mCurrentLocation)
	{
	case world:
		mBackground->Render();
		mEscapeButton->Render();
		mWoodcuttingIcon->Render();
		mMiningIcon->Render();
		mFishingIcon->Render();
		mRunecraftingIcon->Render();

		for (int i = 0; i < 12; i++)
		{
			if (!mFlax[i]->picked)
				mFlax[i]->mTex->Render();
		}
		break;
	case woodcutting:
		mWoodcutting->Render();
		break;
	case mining:
		mMining->Render();
		break;
	case fishing:
		mFishing->Render();
		break;
	case runecrafting:
		mRunecrafting->Render();
	}
}