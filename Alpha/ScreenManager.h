#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Player.h"

#include "LoginScreen.h"
#include "EscapeMenu.h"
#include "PlayerHUD.h"
#include "WorldMap.h"

class ScreenManager
{
private:

	enum SCREEN { login, newplayer, playgame };
	
	static ScreenManager* sInstance;

	InputManager* mInputManager;

	LoginScreen* mLoginScreen;

	EscapeMenu* mEscapeMenu;
	bool mShowEscapeMenu;

	PlayerHUD *mPlayerHUD;

	WorldMap *mWorldMap;

	SCREEN mCurrentScreen;

	Player* mPlayer;
public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();
	
private:
	ScreenManager();
	~ScreenManager();
};

#endif