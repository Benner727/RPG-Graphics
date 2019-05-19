#include "ScreenManager.h"

#include <fstream>

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInputManager = InputManager::Instance();

	mLoginScreen = new LoginScreen();

	mEscapeMenu = new EscapeMenu();
	mShowEscapeMenu = false;

	mPlayer = nullptr;

	mPlayerHUD = nullptr;

	mWorldMap = nullptr;

	mCurrentScreen = login;
}


ScreenManager::~ScreenManager()
{
	mInputManager = nullptr;

	delete mLoginScreen;
	mLoginScreen = nullptr;

	delete mEscapeMenu;
	mEscapeMenu = nullptr;

	if (mPlayerHUD != nullptr)
	{
		delete mPlayerHUD;
		mPlayerHUD = nullptr;
	}

	if (mWorldMap != nullptr)
	{
		delete mWorldMap;
		mWorldMap = nullptr;
	}

	if (mPlayer != nullptr)
	{
		delete mPlayer;
		mPlayer = nullptr;
	}
}

void ScreenManager::Update()
{
	if (mShowEscapeMenu)
	{
		mEscapeMenu->Update();
		if (mEscapeMenu->SelectedMode() == 1)
			mShowEscapeMenu = false;
		else if (mEscapeMenu->SelectedMode() == 2)
		{
			mShowEscapeMenu = false;
			mCurrentScreen = login;
			delete mWorldMap;
			mWorldMap = new WorldMap(mPlayer);
		}
	}
	else
	{
		switch (mCurrentScreen)
		{
		case login:
			mLoginScreen->Update();
			if (mLoginScreen->SelectedMode() == 1)
			{
				mCurrentScreen = newplayer;
				mLoginScreen->ResetAnimation();
			}
			else if (mLoginScreen->SelectedMode() == 2)
			{
				std::ifstream myfile("save.txt");

				if (myfile.is_open())
				{
					myfile.close();
					mPlayer = new Player("Temp");
					mPlayer->load();

					mCurrentScreen = playgame;
					mLoginScreen->ResetAnimation();
				}
			}
			break;
		case newplayer:
			mPlayer = new Player("Reginald");
			mCurrentScreen = playgame;
			break;
		case playgame:
			mPlayerHUD->Update();
			mWorldMap->Update();
			break;
		}
	}

	if (mInputManager->KeyPressed(SDL_SCANCODE_ESCAPE) && mCurrentScreen != login)
		mShowEscapeMenu = !mShowEscapeMenu;
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case login:
		mLoginScreen->Render();
		break;
	case newplayer:
		break;
	case playgame:
		if (mPlayerHUD == nullptr)
			mPlayerHUD = new PlayerHUD(mPlayer);
		if (mWorldMap == nullptr)
			mWorldMap = new WorldMap(mPlayer);

		mPlayerHUD->Render();
		mWorldMap->Render();
		break;
	}

	if (mShowEscapeMenu)
		mEscapeMenu->Render();
}