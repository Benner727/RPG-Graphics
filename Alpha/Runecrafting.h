#ifndef RUNECRAFTING_H
#define RUNECRAFTNG_H

#include "Player.h"
#include "Texture.h"
#include "InputManager.h"

class Runecrafting
{
public:
	Runecrafting(Player*);
	~Runecrafting();

	void Update();
	void Render();

private:
	Player* mPlayer;

	InputManager *mInputManager;

	Texture *mBackground;

	Texture *mAltars[10];

	Texture* mEscapeButton;
	bool exitRunecrafting;

	void runecraft(int);
public:
	bool LeaveRunecrafting() { if (exitRunecrafting) { exitRunecrafting = false; return true; } else return false; }
};

#endif