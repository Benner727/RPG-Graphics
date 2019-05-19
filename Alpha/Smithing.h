#ifndef SMITHING_H
#define SMITHING_H

#include "Player.h"
#include "Inventory.h"

class Smithing
{
public:
	Smithing(Player*);
	~Smithing();

	void Update();
	void Render();
private:
	Player *player;

	InputManager *mInputManager;

	void smelt(std::vector<Item>, int, int);

	Texture *mBars[7];
	Texture *mBarBackground;

	Texture *mOptions[20];
	Texture *mOptionsBackground;

	Texture *mOutline;

	int mSelected;
	bool mSmelting;
	bool mSmithing;

	Texture *mEscapeButton;
	bool exitSmithing;
public:
	void smelt(int);
	void smith(int, int);

	void setSmithing() { mSmithing = true; }
	bool LeaveSmithing() { if (exitSmithing) { exitSmithing = mSmelting = mSmithing = false; return true; } else return false; }
};

#endif