#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ScreenManager.h"

class GameManager
{
private:
	static GameManager* sInstance;

	const int FRAME_RATE = 120;

	bool mQuit;
	Graphics* mGraphics;
	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Timer* mTimer;

	SDL_Event mEvent;

	ScreenManager *mScreenManager;

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

public:
	static GameManager* Instance();
	static void Release();

	void Run();
};

#endif