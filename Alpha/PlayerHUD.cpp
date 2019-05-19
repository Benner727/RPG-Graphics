#include "PlayerHUD.h"

#include "Inventory.h"
#include "Equipment.h"
#include "Skills.h"
#include "PrayerBook.h"
#include "Magic.h"

PlayerHUD::PlayerHUD(Player *player)
{
	mInputManager = InputManager::Instance();

	mPlayer = player;
	mCombatTab = new CombatTab(mPlayer);

	//HUD Background
	mBackground = new Texture("PlayerHUDBase.png");
	mBackground->Scale(Vector2(4.0f, 4.0f));
	mBackground->Pos(Vector2(608, 300));

	//Player Name
	mNameText = new Texture(mPlayer->getName() + " (Level " + std::to_string(mPlayer->skills->getCombatLevel()) + ")", "alagard.ttf", 18, { 0, 0, 0 });
	mNameText->Pos(Vector2(610, 20));

	//Tabs
	mTabOutline = new Texture("TabOutline.png");
	mTabOutline->Scale(Vector2(4.0f, 4.0f));

	mTabSelected = inventory;
	mTabPos = Vector2(670, 274);

	//Health Bar
	mHPIcon = new Texture("HP_Icon.png");
	mHPIcon->Scale(Vector2(1.5f, 1.5f));
	mHPIcon->Pos(Vector2(458, 55));

	mHPBase = new Texture("PlayerHPBar.png", 0, 0, 192, 65);
	mHPBase->Scale(Vector2(1.5f, 0.70f));
	mHPBase->Pos(Vector2(632, 55));

	mHPOverlay = new Texture("PlayerHPBar.png", 0, 65, 188, 59);

	//Prayer Bar
	mPrayIcon = new Texture("Pray_Icon.png");
	mPrayIcon->Scale(Vector2(1.5f, 1.5f));
	mPrayIcon->Pos(Vector2(458, 115));

	mPrayBase = new Texture("PlayerPrayBar.png", 0, 0, 192, 65);
	mPrayBase->Scale(Vector2(1.5f, 0.70f));
	mPrayBase->Pos(Vector2(632, 115));

	mPrayOverlay = new Texture("PlayerPrayBar.png", 0, 65, 188, 59);
}


PlayerHUD::~PlayerHUD()
{
	mInputManager = nullptr;

	mPlayer = nullptr;

	delete mCombatTab;
	mCombatTab = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mNameText;
	mNameText = nullptr;

	delete mHPIcon;
	mHPIcon = nullptr;

	delete mHPBase;
	mHPBase = nullptr;

	delete mHPOverlay;
	mHPOverlay = nullptr;

	delete mPrayIcon;
	mHPIcon = nullptr;

	delete mPrayBase;
	mHPBase = nullptr;

	delete mPrayOverlay;
	mHPOverlay = nullptr;
}

void PlayerHUD::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mInputManager->MousePos().Between(Vector2(421, 168), 54, 30))
			mTabSelected = combat;
		else if (mInputManager->MousePos().Between(Vector2(485, 168), 54, 30))
			mTabSelected = skill;
		else if (mInputManager->MousePos().Between(Vector2(549, 168), 54, 30))
			mTabSelected = inventory;
		else if (mInputManager->MousePos().Between(Vector2(612, 168), 54, 30))
			mTabSelected = equipment;
		else if (mInputManager->MousePos().Between(Vector2(677, 168), 54, 30))
			mTabSelected = prayer;
		else if (mInputManager->MousePos().Between(Vector2(741, 168), 54, 30))
			mTabSelected = magic;
	}

	if (mPlayer->getInBank() || mPlayer->getInShop())
		mTabSelected = inventory;

	mTabOutline->Pos(Vector2(mTabPos.x + 64 * mTabSelected, mTabPos.y));
	
	SetBars();

	switch (mTabSelected)
	{
	case combat:
		mCombatTab->Update();
		break;
	case skill:
		mPlayer->skills->Update();
		break;
	case inventory:
		mPlayer->inventory->Update();
		break;
	case equipment:
		mPlayer->equipment->Update();
		break;
	case prayer:
		mPlayer->prayerBook->Update();
		break;
	case magic:
		mPlayer->magic->Update();
		break;
	}

	//Update player
	static int mStartTicks = SDL_GetTicks();
	if (SDL_GetTicks() > mStartTicks + 600)
	{
		mPlayer->skills->update();
		mStartTicks = SDL_GetTicks();
	}
}

void PlayerHUD::Render()
{
	mBackground->Render();

	delete mNameText;
	mNameText = new Texture(mPlayer->getName() + " (Level " + std::to_string(mPlayer->skills->getCombatLevel()) + ")", "alagard.ttf", 18, { 0, 0, 0 });
	mNameText->Pos(Vector2(610, 20));
	mNameText->Render();

	mTabOutline->Render();

	RenderBars();

	switch (mTabSelected)
	{
	case combat:
		mCombatTab->Render();
		break;
	case skill:
		mPlayer->skills->Render();
		break;
	case inventory:
		mPlayer->inventory->Render();
		break;
	case equipment:
		mPlayer->equipment->Render();
		break;
	case prayer:
		mPlayer->prayerBook->Render();
		break;
	case magic:
		mPlayer->magic->Render();
		break;
	}
}

void PlayerHUD::SetBars()
{
	float healthRatio = (float)mPlayer->skills->getEffect(SKILL::hitpoints) / (float)mPlayer->skills->getLevel(SKILL::hitpoints);
	float prayRatio = (float)mPlayer->skills->getEffect(SKILL::prayer) / (float)mPlayer->skills->getLevel(SKILL::prayer);

	mHPOverlay->Scale(Vector2(1.5f * healthRatio, 0.70f));
	mHPOverlay->Pos(Vector2(632 - (140.5 * (1.0 - healthRatio)), 55));

	mPrayOverlay->Scale(Vector2(1.5f * prayRatio, 0.70f));
	mPrayOverlay->Pos(Vector2(632 - (140.5 * (1.0 - prayRatio)), 115));
}

void PlayerHUD::RenderBars()
{
	mHPIcon->Render();
	mHPBase->Render();
	mHPOverlay->Render();
	
	mPrayIcon->Render();
	mPrayBase->Render();
	mPrayOverlay->Render();
}