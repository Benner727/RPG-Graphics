#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

class LoginScreen : public GameEntity
{
public:
	LoginScreen();

	~LoginScreen();

	void Update();
	void Render();

	void ResetAnimation();

	int SelectedMode();
private:
	Timer* mTimer;
	AudioManager* mAudioManager;
	InputManager* mInputManager;

	Texture* mBackground;
	Texture* mLogoText;
	Texture* mNewButton;
	Texture* mLoginButton;

	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	bool mMusicPlaying;

	int mSelectedMode;
};

#endif