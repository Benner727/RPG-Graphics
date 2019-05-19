#include "GameManager.h"
#include <ctime>

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();

	mScreenManager = ScreenManager::Instance();

	srand(time(NULL));
}


GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenManager = nullptr;

	AudioManager::Release();
	mAudioManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;
}

void GameManager::EarlyUpdate()
{
	mInputManager->Update();
}

void GameManager::Update()
{
	mScreenManager->Update();
}

void GameManager::LateUpdate()
{
	mInputManager->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	mScreenManager->Render();

	mGraphics->Render();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT)
				mQuit = true;
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}