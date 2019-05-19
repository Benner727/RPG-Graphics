#include "CombatTab.h"

#include "Player.h"

CombatTab::CombatTab(Player* p)
{
	mPlayer = p;

	mInputManager = InputManager::Instance();

	mTabText = new Texture("Combat", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	for (int i = 0; i < 4; i++)
		mCombatButton[i] = nullptr;

	mSelectedButton = nullptr;

	for (int i = 0; i < 4; i++)
		mButtonText[i] = nullptr;

	mCurrentStyle = -1;
}

CombatTab::~CombatTab()
{
	mPlayer = nullptr;
	
	mInputManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	clear();
}

void CombatTab::Update()
{
	if (mCurrentStyle != mPlayer->getAttackStyle())
	{
		mCurrentStyle = mPlayer->getAttackStyle();
		clear();

		switch (mCurrentStyle)
		{
		case 0:
			MeleeSetup();
			break;
		case 1:
			RangedSetup();
			break;
		case 2:
			MagicSetup();
			break;
		}
	}

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		for (int i = 0; i < 4; i++)
		{
			if (mCombatButton[i] != nullptr)
			{
				if (mCombatButton[i]->Intersects(mInputManager->MousePos()))
				{
					mSelectedButton->Pos(mCombatButton[i]->Pos());
					mPlayer->setCombatStance(i);
				}
			}
		}
	}
}

void CombatTab::Render()
{
	mTabText->Render();

	for (int i = 0; i < 4; i++)
	{
		if (mCombatButton[i] != nullptr)
			mCombatButton[i]->Render();
	}

	mSelectedButton->Render();

	for (int i = 0; i < 4; i++)
	{
		if (mButtonText[i] != nullptr)
			mButtonText[i]->Render();
	}
}

void CombatTab::clear()
{
	for (int i = 0; i < 4; i++)
	{
		if (mCombatButton[i] != nullptr)
		{
			delete mCombatButton[i];
			mCombatButton[i] = nullptr;
		}
	}

	if (mSelectedButton != nullptr)
	{
		delete mSelectedButton;
		mSelectedButton = nullptr;
	}

	for (int i = 0; i < 4; i++)
	{
		if (mButtonText[i] != nullptr)
		{
			delete mButtonText[i];
			mButtonText[i] = nullptr;
		}
	}
}

void CombatTab::MeleeSetup()
{
	for (int i = 0; i < 4; i++)
	{
		mCombatButton[i] = new Texture("CombatButton.png");
		mCombatButton[i]->Pos(Vector2(610.0f, 310 + 80 * i));
		mCombatButton[i]->Scale(Vector2(4.0f, 4.0f));
	}

	mSelectedButton = new Texture("CombatSelect.png");
	mSelectedButton->Pos(mCombatButton[0]->Pos());
	mSelectedButton->Scale(Vector2(4.0f, 4.0f));

	mButtonText[0] = new Texture("Accurate", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[1] = new Texture("Aggressive", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[2] = new Texture("Defensive", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[3] = new Texture("Controlled", "alagard.ttf", 24, { 255, 255, 255 });

	for (int i = 0; i < 4; i++)
		mButtonText[i]->Pos(Vector2(610.0, 310 + 81 * i));
}

void CombatTab::RangedSetup()
{
	for (int i = 0; i < 2; i++)
	{
		mCombatButton[i] = new Texture("CombatButton.png");
		mCombatButton[i]->Pos(Vector2(610.0f, 310 + 80 * i));
		mCombatButton[i]->Scale(Vector2(4.0f, 4.0f));
	}

	mSelectedButton = new Texture("CombatSelect.png");
	mSelectedButton->Pos(mCombatButton[0]->Pos());
	mSelectedButton->Scale(Vector2(4.0f, 4.0f));

	mButtonText[0] = new Texture("Rapid", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[1] = new Texture("Longrange", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[2] = nullptr;
	mButtonText[3] = nullptr;

	for (int i = 0; i < 2; i++)
		mButtonText[i]->Pos(Vector2(610.0, 310 + 81 * i));
}

void CombatTab::MagicSetup()
{
	for (int i = 0; i < 1; i++)
	{
		mCombatButton[i] = new Texture("CombatButton.png");
		mCombatButton[i]->Pos(Vector2(610.0f, 310 + 80 * i));
		mCombatButton[i]->Scale(Vector2(4.0f, 4.0f));
	}

	mSelectedButton = new Texture("CombatSelect.png");
	mSelectedButton->Pos(mCombatButton[0]->Pos());
	mSelectedButton->Scale(Vector2(4.0f, 4.0f));

	mButtonText[0] = new Texture("Autocast", "alagard.ttf", 24, { 255, 255, 255 });
	mButtonText[1] = nullptr;
	mButtonText[2] = nullptr;
	mButtonText[3] = nullptr;

	for (int i = 0; i < 1; i++)
		mButtonText[i]->Pos(Vector2(610.0, 310 + 81 * i));
}