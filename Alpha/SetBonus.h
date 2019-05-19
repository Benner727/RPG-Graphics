#ifndef SETBONUS_H
#define SETBONUS_H

#include "Player.h"

class SetBonus
{
public:
	SetBonus();

	~SetBonus();

private:

	bool dharokSet(const Player&);
	bool guthanSet(const Player&);
public:
	bool voidSet(const Player&);
	double getDamageModifier(const Player&);
	void applyEffect(Player*, int);
};

#endif