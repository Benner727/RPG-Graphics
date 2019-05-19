#include "Workshop.h"

#include "Prayer.h"
#include "Crafting.h"

Workshop::Workshop(Player *player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();

	mBackground = new Texture("WorkshopBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mAnvilIcon = new Texture("Entities/Anvil.png");
	mAnvilIcon->Pos(Vector2(345, 170));
	mAnvilIcon->Scale(Vector2(3.0f, 3.0f));

	mForgeIcon = new AnimatedTexture("Entities/Forge.png", 0, 0, 16, 16, 2, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mForgeIcon->Pos(Vector2(245, 95));
	mForgeIcon->Scale(Vector2(4.0f, 4.0f));

	mSmithing = new Smithing(mPlayer);

	mCampfireIcon = new AnimatedTexture("Entities/Campfire.png", 0, 0, 16, 16, 2, 1.0f, AnimatedTexture::ANIM_DIR::horizontal);
	mCampfireIcon->Pos(Vector2(90, 275));
	mCampfireIcon->Scale(Vector2(3.0f, 3.0f));

	mCooking = new Cooking(mPlayer);

	mPrayIcon = new Texture("Entities/PrayAlter.png");
	mPrayIcon->Pos(Vector2(90, 90));
	mPrayIcon->Scale(Vector2(3.0f, 3.0f));

	mSpinnerIcon = new Texture("Entities/SpinningWheel.png");
	mSpinnerIcon->Pos(Vector2(225, 325));
	mSpinnerIcon->Scale(Vector2(3.0f, 3.0f));

	mTannerIcon = new Texture("Entities/Tanner.png");
	mTannerIcon->Pos(Vector2(135, 560));
	mTannerIcon->Scale(Vector2(3.0f, 3.0f));

	mTanOptions[0] = new Texture("Soft", "alagard.ttf", 16, { 255, 255, 255 });
	mTanOptions[1] = new Texture("Hard", "alagard.ttf", 16, { 255, 255, 255 });
	mTanOptions[2] = new Texture("Green", "alagard.ttf", 16, { 255, 255, 255 });
	mTanOptions[3] = new Texture("Blue", "alagard.ttf", 16, { 255, 255, 255 });
	mTanOptions[4] = new Texture("Red", "alagard.ttf", 16, { 255, 255, 255 });
	mTanOptions[5] = new Texture("Black", "alagard.ttf", 16, { 255, 255, 255 });

	for (int i = 0; i < 6; i++)
	{
		mTanOptions[i]->Pos(Vector2(175, 464 + (i * 16)));
	}

	mAltBackground = new Texture("BlankBackground.png");
	mAltBackground->Pos(Vector2(175.0f, 504.0f));
	mAltBackground->Scale(Vector2(2.75f, 6.5f));

	mLabels[0] = new Texture("Smith", "alagard.ttf", 24, { 255, 255, 0 });
	mLabels[1] = new Texture("Smelt", "alagard.ttf", 24, { 255, 255, 0 });
	mLabels[2] = new Texture("Cook", "alagard.ttf", 24, { 255, 255, 0 });
	mLabels[3] = new Texture("Pray", "alagard.ttf", 24, { 255, 255, 0 });
	mLabels[4] = new Texture("Spin", "alagard.ttf", 24, { 255, 255, 0 });
	mLabels[5] = new Texture("Tan", "alagard.ttf", 24, { 255, 255, 0 });

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	activity = none;
}

Workshop::~Workshop()
{
	mPlayer = nullptr;

	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mSmithing;
	mSmithing = nullptr;

	delete mCooking;
	mCooking = nullptr;

	delete mAnvilIcon;
	mAnvilIcon = nullptr;

	delete mForgeIcon;
	mForgeIcon = nullptr;

	delete mCampfireIcon;
	mCampfireIcon = nullptr;

	delete mPrayIcon;
	mPrayIcon = nullptr;

	delete mSpinnerIcon;
	mSpinnerIcon = nullptr;

	delete mTannerIcon;
	mTannerIcon = nullptr;

	for (int i = 0; i < 6; i++)
	{
		delete mTanOptions[i];
		mTanOptions[i] = nullptr;

		delete mLabels[i];
		mLabels[i] = nullptr;
	}

	delete mAltBackground;
	mAltBackground = nullptr;

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void Workshop::Update()
{
	static int mStartTicks = SDL_GetTicks();

	mForgeIcon->Update();
	mCampfireIcon->Update();

	switch (activity)
	{
	case none:
	case cooking:
	case spinning:
	case tanning:
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			if (mEscapeButton->Intersects(mInputManager->MousePos()))
			{
				activity = none;
				exitWorkshop = true;
			}
			else if (mAnvilIcon->Intersects(mInputManager->MousePos()))
			{
				activity = smithing;
			}
			else if (mForgeIcon->Intersects(mInputManager->MousePos()))
			{
				activity = smelting;
			}
			else if (mCampfireIcon->Intersects(mInputManager->MousePos()))
			{
				activity = cooking;
			}
			else if (mPrayIcon->Intersects(mInputManager->MousePos()))
			{
				mPlayer->skills->restore(SKILL::prayer);
				mPlayer->prayer->offerBones();
			}
			else if (mSpinnerIcon->Intersects(mInputManager->MousePos()))
			{
				activity = spinning;
			}
			else if (mTannerIcon->Intersects(mInputManager->MousePos()))
			{
				activity = tanning;
			}
			else if (activity == tanning)
			{
				for (int i = 0; i < 6; i++)
				{
					if (mTanOptions[i]->Intersects(mInputManager->MousePos()))
					{
						mPlayer->crafting->tan(i);
						break;
					}
				}

				activity = none;
			}
		}

		if (activity == cooking)
		{
			mCooking->Update();
		}
		else if (activity == spinning)
		{
			if (SDL_GetTicks() >= mStartTicks + 600)
			{
				mStartTicks = SDL_GetTicks();

				for (int i = 0; i < 20; i++)
				{
					if (mPlayer->crafting->spinFlax(i))
						break;
				}
			}
		}
		break;
	case smelting:
		mSmithing->Update();

		if (mSmithing->LeaveSmithing())
			activity = none;
		break;
	case smithing:
		mSmithing->setSmithing();
		mSmithing->Update();

		if (mSmithing->LeaveSmithing())
			activity = none;
		break;
	}
}

void Workshop::Render()
{
	mBackground->Render();
	mAnvilIcon->Render();
	mForgeIcon->Render();
	mCampfireIcon->Render();
	mPrayIcon->Render();
	mSpinnerIcon->Render();
	mTannerIcon->Render();

	if (mAnvilIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[0]->Pos(mInputManager->MousePos());
		mLabels[0]->Render();
	}
	else if (mForgeIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[1]->Pos(mInputManager->MousePos());
		mLabels[1]->Render();
	}
	else if (mCampfireIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[2]->Pos(mInputManager->MousePos());
		mLabels[2]->Render();
	}
	else if (mPrayIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[3]->Pos(mInputManager->MousePos());
		mLabels[3]->Render();
	}
	else if (mSpinnerIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[4]->Pos(mInputManager->MousePos());
		mLabels[4]->Render();
	}
	else if (mTannerIcon->Intersects(mInputManager->MousePos()))
	{
		mLabels[5]->Pos(mInputManager->MousePos());
		mLabels[5]->Render();
	}

	switch (activity)
	{
	case none:
	case cooking:
	case spinning:
		mEscapeButton->Render();
		break;
	case smelting:
		mSmithing->Render();
		break;
	case smithing:
		mSmithing->Render();
		break;
	case tanning:
		mEscapeButton->Render();
		mAltBackground->Render();
		for (int i = 0; i < 6; i++)
			mTanOptions[i]->Render();
		break;
	}
}