#ifndef RANGEDFORMULAS_H
#define RANGEDFORMULAS_H

#include "Player.h"
#include "Npc.h"

class RangedFormulas
{
public:
	RangedFormulas();

	~RangedFormulas();

private:
	double getEffectiveDefense(const Player&);
	double getEffectiveRange(const Player&);
	double getRangedStrength(const Player&);

public:
	double getDefenseRoll(const Player&);
	double getDefenseRoll(const Npc&);
	double getAttackRoll(const Player&);
	double getAttackRoll(const Npc&);

	double calculateBasedamage(const Player&);
};

#endif