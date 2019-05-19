#ifndef WORKSHOP_H
#define WORKSHOP_H

#include "Player.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Smithing.h"
#include "Cooking.h"

class Workshop
{
public:
	Workshop(Player*);
	~Workshop();

	void Update();
	void Render();

private:
	enum ACTIVITY { none, smelting, smithing, cooking, spinning, tanning };
	ACTIVITY activity;

	Player *mPlayer;

	InputManager *mInputManager;

	Texture *mBackground;

	Texture *mAnvilIcon;
	AnimatedTexture *mForgeIcon;
	Smithing *mSmithing;

	AnimatedTexture *mCampfireIcon;
	Cooking *mCooking;

	Texture *mPrayIcon;
	
	Texture *mSpinnerIcon;
	
	Texture *mTannerIcon;
	Texture *mTanOptions[6];
	Texture *mAltBackground;

	Texture *mLabels[6];

	Texture* mEscapeButton;
	bool exitWorkshop;

public:
	bool LeaveWorkshop() { if (exitWorkshop) { exitWorkshop = false; return true; } else return false; }
};

#endif