#include "MeleeFormulas.h"
#include "Skills.h"
#include "PrayerBook.h"
#include "Equipment.h"
#include "SetBonus.h"


MeleeFormulas::MeleeFormulas()
{
}


MeleeFormulas::~MeleeFormulas()
{
}


double MeleeFormulas::getEffectiveDefense(const Player &player)
{
	double effectiveDefense = player.skills->getEffect(defense);

	if (player.getCombatStance() == 3) effectiveDefense += 3;
	else if (player.getCombatStance() == 4) effectiveDefense += 1;

	if (player.prayerBook->getActivated(0))
		effectiveDefense *= 1.05;
	else if (player.prayerBook->getActivated(5))
		effectiveDefense *= 1.10;
	else if (player.prayerBook->getActivated(10))
		effectiveDefense *= 1.15;
	else if (player.prayerBook->getActivated(18))
		effectiveDefense *= 1.20;
	else if (player.prayerBook->getActivated(19))
		effectiveDefense *= 1.25;

	return effectiveDefense;
}

double MeleeFormulas::getEffectiveAttack(const Player &player)
{
	double effectiveAttack = player.skills->getEffect(attack);

	if (player.getCombatStance() == 1) effectiveAttack += 3;
	else if (player.getCombatStance() == 4) effectiveAttack += 1;

	if (player.prayerBook->getActivated(2))
		effectiveAttack *= 1.05;
	else if (player.prayerBook->getActivated(7))
		effectiveAttack *= 1.10;
	else if (player.prayerBook->getActivated(12))
		effectiveAttack *= 1.15;
	else if (player.prayerBook->getActivated(18))
		effectiveAttack *= 1.20;
	else if (player.prayerBook->getActivated(19))
		effectiveAttack *= 1.25;

	return effectiveAttack;
}

double MeleeFormulas::getEffectiveStrength(const Player &player)
{
	double effectiveStrength = player.skills->getEffect(strength);

	if (player.getCombatStance() == 2) effectiveStrength += 3;
	else if (player.getCombatStance() == 4) effectiveStrength += 1;

	if (player.prayerBook->getActivated(1))
		effectiveStrength *= 1.05;
	else if (player.prayerBook->getActivated(6))
		effectiveStrength *= 1.10;
	else if (player.prayerBook->getActivated(11))
		effectiveStrength *= 1.15;
	else if (player.prayerBook->getActivated(18))
		effectiveStrength *= 1.20;
	else if (player.prayerBook->getActivated(19))
		effectiveStrength *= 1.25;

	return effectiveStrength;
}

double MeleeFormulas::getDefenseRoll(const Player &player)
{
	return getEffectiveDefense(player) * (2.0 + (double)player.equipment->getBonus(3));
}

double MeleeFormulas::getDefenseRoll(const Npc &npc)
{
	double bonus;

	switch (npc.getNpcDefinition().getAttackStyle())
	{
	case 0: //Melee
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.33;
		break;
	case 1: //Ranged
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.66;
		break;
	case 2: //Magic
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.05;
		break;
	default:
		bonus = 0;
		break;
	}

	return npc.getNpcDefinition().getDefenseStat() * (2.0 + bonus);
}

double MeleeFormulas::getAttackRoll(const Player &player)
{
	SetBonus setBonus;
	if (setBonus.voidSet(player))
		return getEffectiveAttack(player) * (2.0 + (double)player.equipment->getBonus(0)) * 1.1;
	else
		return getEffectiveAttack(player) * (2.0 + (double)player.equipment->getBonus(0));
}

double MeleeFormulas::getAttackRoll(const Npc &npc)
{
	return npc.getNpcDefinition().getAttackStat() * (2.0 + npc.getNpcDefinition().getAttackStat() * 0.66);
}

double MeleeFormulas::calculateBasedamage(const Player &player)
{
	return (13 + getEffectiveStrength(player) + ((double)player.equipment->getBonus(6) / 8) + ((double)(getEffectiveStrength(player) * (double)player.equipment->getBonus(6)) / 64)) / 10;
}