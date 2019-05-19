#include "EscapeMenu.h"


EscapeMenu::EscapeMenu()
{
	mInputManager = InputManager::Instance();

	mBackground = new Texture("EscapeMenu.png");
	mBackground->Scale(Vector2(4.0f, 4.0f));
	mBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLogoText = new Texture("E S C A P E", "alagard.ttf", 28, { 0, 0, 0 });
	mLogoText->Pos(Vector2(400.0f, 200.0f));

	mContinueButton = new Texture("Continue", "alagard.ttf", 28, { 0, 0, 0 });
	mContinueButton->Pos(Vector2(400.0f, 265.0f));

	mExitButton = new Texture("Exit", "alagard.ttf", 28, { 0, 0, 0 });
	mExitButton->Pos(Vector2(400.0f, 340.0f));

	mBackground->Parent(this);
	mLogoText->Parent(this);
	mContinueButton->Parent(this);
	mExitButton->Parent(this);
}


EscapeMenu::~EscapeMenu()
{
	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mLogoText;
	mLogoText = nullptr;

	delete mContinueButton;
	mContinueButton = nullptr;

	delete mExitButton;
	mExitButton = nullptr;
}

int EscapeMenu::SelectedMode()
{
	return mSelectedMode;
}

void EscapeMenu::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mInputManager->MousePos().Between(Vector2(309, 234), 182, 57))
			mSelectedMode = 1;
		else if (mInputManager->MousePos().Between(Vector2(309, 306), 182, 57))
			mSelectedMode = 2;
	}
	else
		mSelectedMode = 0;
}

void EscapeMenu::Render()
{
	mBackground->Render();
	mLogoText->Render();
	mContinueButton->Render();
	mExitButton->Render();
}