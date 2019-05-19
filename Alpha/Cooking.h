#ifndef COOKING_H
#define COOKING_H

#include "Player.h"

class Cooking
{
public:
	Cooking(Player*);
	~Cooking();

	void Update();
private:
	Player *player;
	bool cook(int);
};

#endif