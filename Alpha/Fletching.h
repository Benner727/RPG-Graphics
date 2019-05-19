#ifndef FLETCHING_H
#define FLETCHING_H

#include "Inventory.h"
#include "Skills.h"

class Player;

class Fletching
{
public:
	Fletching(Player*);

	~Fletching();

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

	void knifeOnLog(int);
	void stringShortbow(int, int);
	void stringCrossbow(int, int, int);
	void fletchArrow(int, int);
	void fletchBolt(int, int, int);
	void makeCrossbow(int, int);
public:
	void fletch(int, int);
};

#endif