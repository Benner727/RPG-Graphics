#include "RangedFormulas.h"
#include "Skills.h"
#include "Equipment.h"
#include "PrayerBook.h"
#include "SetBonus.h"


RangedFormulas::RangedFormulas()
{
}


RangedFormulas::~RangedFormulas()
{
}


double RangedFormulas::getEffectiveDefense(const Player &player)
{
	double effectiveDefense = player.skills->getEffect(defense);

	if (player.getCombatStance() == 6) effectiveDefense += 1;

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

double RangedFormulas::getEffectiveRange(const Player &player)
{
	double effectiveAttack = player.skills->getEffect(ranged);

	if (player.getCombatStance() == 5) effectiveAttack += 3;
	else if (player.getCombatStance() == 6) effectiveAttack += 1;

	if (player.prayerBook->getActivated(3))
		effectiveAttack *= 1.05;
	else if (player.prayerBook->getActivated(8))
		effectiveAttack *= 1.10;
	else if (player.prayerBook->getActivated(16))
		effectiveAttack *= 1.15;

	return effectiveAttack;
}

double RangedFormulas::getRangedStrength(const Player &player)
{

	if (player.equipment->getItem(3)->getRangedDefinition()->getType())
	{
		switch (player.equipment->getItem(3)->getId())
		{
		case 835: //Bronze knife
			return 3;
			break;
		case 836: //Iron knife
			return 4;
			break;
		case 837: //Steel knife
			return 7;
			break;
		case 838: //Black knife
			return 8;
			break;
		case 839: //Mithril knife
			return 10;
			break;
		case 840: //Adamant knife
			return 14;
			break;
		case 841: //Rune knife
			return 24;
			break;
		case 926: //Obsidian ring
			return 49;
			break;
		default:
			return 0;
			break;
		}
	}
	else
	{
		if (player.equipment->getItem(10) == nullptr)
			return 0;

		switch (player.equipment->getItem(10)->getId())
		{
		case 65: //Bronze arrow
			return 7;
			break;
		case 123: //Bronze bolt
		case 66: //Iron arrow
			return 10;
			break;
		case 67: //Steel arrow
			return 16;
			break;
		case 68: //Mithril arrow
			return 22;
			break;
		case 557: //Broad arrow
			return 28;
			break;
		case 69: //Adamant arrow
			return 31;
			break;
		case 124: //Iron bolt
		case 70: //Rune arrow
			return 49;
			break;
		case 125: //Steel bolt
			return 64;
			break;
		case 126: //Mithril bolt
			return 82;
			break;
		case 127: //Adamant bolt
		case 558: //Broad bolt
			return 100;
			break;
		case 128: //Rune bolt
			return 115;
			break;
		case 1064: //Bolt rack
			return 55;
			break;
		default:
			return 0;
			break;
		}
	}
}

double RangedFormulas::getDefenseRoll(const Player &player)
{
	return getEffectiveDefense(player) * (2.0 + (double)player.equipment->getBonus(4));
}

double RangedFormulas::getDefenseRoll(const Npc &npc)
{
	double bonus;

	switch (npc.getNpcDefinition().getAttackStyle())
	{
	case 0: //Melee
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.05;
		break;
	case 1: //Ranged
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.33;
		break;
	case 2: //Magic
		bonus = npc.getNpcDefinition().getDefenseStat() * 0.66;
		break;
	default:
		bonus = 0;
		break;
	}

	return npc.getNpcDefinition().getDefenseStat() * (2.0 + bonus);
}

double RangedFormulas::getAttackRoll(const Player &player)
{
	SetBonus setBonus;
	if (setBonus.voidSet(player))
		return getEffectiveRange(player) * (2.0 + (double)player.equipment->getBonus(1)) * 1.2;
	else
		return getEffectiveRange(player) * (2.0 + (double)player.equipment->getBonus(1));
}

double RangedFormulas::getAttackRoll(const Npc &npc)
{
	return npc.getNpcDefinition().getAttackStat() * (2.0 + npc.getNpcDefinition().getAttackStat() * 0.66);
}

double RangedFormulas::calculateBasedamage(const Player &player)
{
	return (13 + getEffectiveRange(player) + (getRangedStrength(player) / 8) + ((getEffectiveRange(player) * getRangedStrength(player)) / 64)) / 10;
}