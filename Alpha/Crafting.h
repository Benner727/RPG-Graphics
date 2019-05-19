#ifndef CRAFTING_H
#define CRAFTING_H

#include "Inventory.h"
#include "Skills.h"

class Player;

class Crafting
{
public:
	Crafting(Player*);
	~Crafting();

	void Update();
	void Render();
private:
	Player *player;

	InputManager *mInputManager;

	std::vector<Texture*> mOptions;
	Texture* mBackground;
	int mSelected;

	int slotOne, slotTwo;

	void Clear();

	void craftLeather(int);
	void craftHardLeather(int);
	void craftDhide(int);
	void craftJewellery();
public:
	void pickFlax();
	bool spinFlax(int);

	void tan(int);
	void craft(int, int);
};

#endif