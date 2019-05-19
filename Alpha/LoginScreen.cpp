#include "LoginScreen.h"


LoginScreen::LoginScreen()
{
	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();
	mInputManager = InputManager::Instance();

	mBackground = new Texture("LoginScreen.png");
	mBackground->Scale(Vector2(4.0f, 4.0f));
	mBackground->Pos(Vector2(400.0f, 300.0f));

	mLogoText = new Texture("W E L C O M E", "alagard.ttf", 28, { 0, 0, 0 });
	mLogoText->Pos(Vector2(400.0f, 210.0f));

	mNewButton = new Texture("New User", "alagard.ttf", 22, { 0, 0, 0 });
	mNewButton->Pos(Vector2(275.0f, 313.0f));

	mLoginButton = new Texture("Existing User", "alagard.ttf", 22, { 0, 0, 0 });
	mLoginButton->Pos(Vector2(525.0f, 313.0f));

	mBackground->Parent(this);
	mLogoText->Parent(this);
	mNewButton->Parent(this);
	mLoginButton->Parent(this);

	ResetAnimation();
	
	mMusicPlaying = false;
}


LoginScreen::~LoginScreen()
{
	mTimer = nullptr;
	mAudioManager = nullptr;
	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mLogoText;
	mLogoText = nullptr;

	delete mNewButton;
	mNewButton = nullptr;

	delete mLoginButton;
	mLoginButton = nullptr;
}

void LoginScreen::ResetAnimation()
{
	mSelectedMode = 0;

	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;
	
	Pos(mAnimationStartPos);
}

int LoginScreen::SelectedMode()
{
	return mSelectedMode;
}

void LoginScreen::Update()
{
	if (!mMusicPlaying)
	{
		mAudioManager->PlayMusic("Soliloquy.wav");
		mMusicPlaying = true;
	}

	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
			mAnimationDone = true;

		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
			mAnimationTimer = mAnimationTotalTime;
	}
	else
	{
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			if (mInputManager->MousePos().Between(Vector2(188, 284), 183, 55))
			{
				mAudioManager->PauseMusic();
				mMusicPlaying = false;

				mSelectedMode = 1;
			}
			else if (mInputManager->MousePos().Between(Vector2(428, 284), 183, 55))
			{
				mAudioManager->PauseMusic();
				mMusicPlaying = false;

				mSelectedMode = 2;
			}
		}
	}
}

void LoginScreen::Render()
{
	mBackground->Render();
	mLogoText->Render();
	mNewButton->Render();
	mLoginButton->Render();
}