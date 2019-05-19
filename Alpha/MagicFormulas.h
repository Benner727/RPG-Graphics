#ifndef MAGICFORMULAS_H
#define MAGICFORMULAS_H

#include "player.h"
#include "Npc.h"

class MagicFormulas
{
public:
	MagicFormulas();

	~MagicFormulas();

private:
	double getEffectiveDefense(const Player&);
	double getEffectiveMagic(const Player&);

public:
	double getDefenseRoll(const Player&);
	double getDefenseRoll(const Npc&);
	double getAttackRoll(const Player&);
	double getAttackRoll(const Npc&);

	double calculateBasedamage(const Player&);
};

#endif