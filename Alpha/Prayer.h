#ifndef PRAYER_H
#define PRAYER_H

#include "Item.h"

class Player;

class Prayer
{
public:
	Prayer(Player*);
	~Prayer();

private:
	Player* player;

	int getExp(int);
public:
	bool isBone(int);
	void buryBone(int);
	void offerBones();

	bool boneCrusher(Item*);
};

#endif