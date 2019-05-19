#ifndef ESCAPEMENU_H
#define ESCAPEMENU_H

#include "AnimatedTexture.h"
#include "InputManager.h"

class EscapeMenu : public GameEntity
{
public:
	EscapeMenu();

	~EscapeMenu();

	void Update();
	void Render();

	int SelectedMode();
private:
	InputManager* mInputManager;

	Texture* mBackground;
	Texture* mLogoText;
	Texture* mContinueButton;
	Texture* mExitButton;

	int mSelectedMode;
};

#endif