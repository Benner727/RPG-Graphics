#include "CombatAssistant.h"
#include <vector>
#include "Skills.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Magic.h"
#include "PrayerBook.h"
#include "Slayer.h"
#include "SetBonus.h"


std::vector<std::pair<int, int>> slayerMonster = {
	{ 0, 5 },{ 1, 5 },{ 2, 7 },{ 3, 7 },{ 4, 10 },{ 5, 15 },{ 6, 17 },
	{ 7, 20 },{ 8, 22 },{ 9, 25 },{ 10, 30 },{ 11, 32 },{ 12, 33 },{ 13, 35 },
	{ 14, 37 },{ 15, 39 },{ 16, 40 },{ 17, 40 },{ 18, 42 },{ 19, 45 },{ 20, 47 },
	{ 21, 50 },{ 22, 52 },{ 23, 55 },{ 24, 57 },{ 25, 58 },{ 26, 60 },{ 27, 63 },
	{ 28, 65 },{ 29, 68 },{ 30, 70 },{ 31, 72 },{ 32, 75 },{ 33, 80 },{ 34, 83 },
	{ 35, 85 },{ 36, 90 },{ 37, 93 } };


CombatAssistant::CombatAssistant()
{
}


CombatAssistant::~CombatAssistant()
{
}


bool CombatAssistant::hasSlayerLevel(Player* player, Npc* npc)
{
	for (int i = 0; i < slayerMonster.size(); i++)
	{
		if (npc->getId() == slayerMonster[i].first)
			if (player->skills->getLevel(slayer) < slayerMonster[i].second)
				return false;
	}
	return true;
}

bool CombatAssistant::hasWeaponRequirement(Player* player, Npc* npc)
{
	switch (npc->getId())
	{
	case 23: //Turoth
	case 30: //Kurask
		if (player->getAutoCast())
		{
			if (player->magic->getCurrentSpell()->getName() == "Magic Dart")
				return true;
		}
		else if (player->getAttackStyle() == 1)
		{
			if (player->equipment->getItem(10) != nullptr)
			{
				if (player->equipment->getItem(10)->getId() == 558) //Broad bolts
					return true;
				else if (player->equipment->getItem(10)->getId() == 557) //Broad arrows
					return true;
			}
		}
		else if (player->equipment->getItem(3) != nullptr)
		{
			if (player->equipment->getItem(3)->getId() == 756) //Leaf-Bladed Spear
				return true;
			else if (player->equipment->getItem(3)->getId() == 1065) //Leaf-Bladed Sword
				return true;
		}
		return false;
		break;
	case 12: //Harpie Bug Swarm
		if (player->equipment->getItem(5) != nullptr)
			if (player->equipment->getItem(5)->getId() == 744) //Bug Lantern
				return true;
		return false;
		break;
	case 15: //Molanisk
		if (player->inventory->hasItem(752)) //Slayer Bell
			return true;
		return false;
		break;
	default:
		return true;
		break;
	}
}

bool CombatAssistant::hasEquipmentRequirement(Player* player, Npc* npc)
{
	switch (npc->getId())
	{
	case 5:
	case 13:
	case 26:
	case 28:
	case 37:
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 733)
				return true;
		break;
	default:
		break;
	}

	switch (npc->getId())
	{
	case 5: //Banshee
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 737) //Earmuffs
				return true;
		return false;
		break;
	case 9: //Cockatrice
		if (player->equipment->getItem(5) != nullptr)
			if (player->equipment->getItem(5)->getId() == 741) //Mirror Shield
				return true;
		return false;
		break;
	case 13: //Wall Beast
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 733) //Spiny Helmet
				return true;
		return false;
		break;
	case 14: //Killerwatt
		if (player->equipment->getItem(8) != nullptr)
			if (player->equipment->getItem(8)->getId() == 750) //Insulated Boots
				return true;
		return false;
		break;
	case 16: //Basilisk
		if (player->equipment->getItem(5) != nullptr)
			if (player->equipment->getItem(5)->getId() == 741) //Mirror Shield
				return true;
		return false;
		break;
	case 18: //Fever Spider
		if (player->equipment->getItem(7) != nullptr)
			if (player->equipment->getItem(7)->getId() == 754) //Slayer Gloves
				return true;
		return false;
		break;
	case 25: //Cave Horror
		if (player->equipment->getItem(2) != nullptr)
			if (player->equipment->getItem(2)->getId() == 748) //Witchwood Icon
				return true;
		return false;
		break;
	case 26: //Aberrant Spectre
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 759) //Nosepeg
				return true;
		return false;
		break;
	case 28: //Dust Devil
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 735) //Facemask
				return true;
		return false;
		break;
	case 31: //Skeletal Wyvern
	case 70: //Green Dragon
	case 71: //Blue Dragon
	case 72: //Red Dragon
	case 73: //Black Dragon
	case 74: //Bronze Dragon
	case 75: //Iron Dragon
	case 76: //Steel Dragon
	case 77: //Mithril Dragon
	case 105: //Lava dragon
		if (player->equipment->getItem(5) != nullptr)
		{
			if (player->equipment->getItem(5)->getId() == 763) //Anti-dragon Shield
				return true;
			else if (player->equipment->getItem(5)->getId() == 799) //Dragonfire Shield
				return true;
		}
		return false;
		break;
	case 37: //Smoke Devil
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 735) //Facemask
				return true;
		return false;
		break;
	default:
		return true;
		break;
	}
}

bool CombatAssistant::canAttack(Player* player, Npc* npc)
{
	if (hasSlayerLevel(player, npc))
		if (hasWeaponRequirement(player, npc))
			return true;

	return false;
}

bool CombatAssistant::canKill(Player* player, Npc* npc)
{
	switch (npc->getId())
	{
	case 7: //Rockslug
		if (player->inventory->hasItem(739)) //Bag of Salt
		{
			player->inventory->removeItem(739, 1);
			return true;
		}
		else
			return false;
		break;
	case 8: //Desert Lizard
		if (player->inventory->hasItem(740)) //Ice Cooler
		{
			player->inventory->removeItem(740, 1);
			return true;
		}
		else
			return false;
		break;
	case 11: //Mogre
		if (player->inventory->hasItem(743))
		{
			player->inventory->removeItem(743, 1);
			return true;
		}
		else
			return false;
		break;
	case 24: //Mutated Zygomite
		if (player->inventory->hasItem(758)) //Fungicide Spray
		{
			player->inventory->removeItem(758, 1);
			return true;
		}
		else
			return false;
		break;
	case 32: //Gargoyle
		if (player->inventory->hasItem(761)) //Rock Hammer
			return true;
		else
			return false;
		break;
	default:
		return true;
		break;
	}
}

int CombatAssistant::playerDamageModifier(Player* player, Npc* npc, int playerHit)
{

	if (player->slayer->isTask(npc->getId())) //Slayer task
	{
		if (player->equipment->getItem(0) != nullptr)
			if (player->equipment->getItem(0)->getId() == 731) //Black Mask
				playerHit *= 1.15;
			else if (player->equipment->getItem(0)->getId() == 733) //Slayer Helmet
				playerHit *= 1.25;
	}

	SetBonus setBonus;
	playerHit *= setBonus.getDamageModifier(*player);
	setBonus.applyEffect(player, playerHit);

	return playerHit;
}

int CombatAssistant::npcDamageModifier(Npc* npc, Player* player, int npcHit)
{
	if (!hasEquipmentRequirement(player, npc))
	{
		switch (npc->getId())
		{
		case 5: //Banshee
			npcHit = 6;
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 9: //Cockatrice
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 13: //Wall Beast
			npcHit = rand() % 18 + 1;
			break;
		case 14: //Killerwatt
			npcHit = rand() % 14 + 1;
			break;
		case 16: //Basilisk
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 18: //Fever Spider
			npcHit += rand() % 6 + 1;
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 25: //Cave Horror
			npcHit = (double)player->skills->getLevel(hitpoints) / 10.0;
			break;
		case 26: //Aberrant Spectre
			npcHit = rand() % 14 + 1;
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 28: //Dust Devil
			npcHit = 14;
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		case 31: //Skeletal Wyvern
		case 70: //Green Dragon
		case 71: //Blue Dragon
		case 72: //Red Dragon
		case 73: //Black Dragon
		case 74: //Bronze Dragon
		case 75: //Iron Dragon
		case 76: //Steel Dragon
		case 77: //Mithril Dragon
		case 105: //Lava dragon
			npcHit = rand() % 50 + 1;
			break;
		case 37: //Smoke Devil
			npcHit = 14;
			for (int i = 0; i < 7; i++)
				player->skills->drainSkill((double)player->skills->getLevel(i) / 10.0, i);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (npc->getNpcDefinition().getAttackStyle())
		{
		case 0:
			if (player->prayerBook->getActivated(15)) //Protect from Melee
			{
				if (npc->getId() == 127) //Verac
				{
					if (npcHit) npcHit = rand() % 15 + 1;
				}
				else
					npcHit *= 0;
			}

			break;
		case 1:
			if (player->prayerBook->getActivated(14)) //Protect from Range
				npcHit *= 0;
			break;
		case 2:
			if (player->prayerBook->getActivated(13)) //Protect from Magic
				npcHit *= 0;
			break;
		default:
			break;
		}
	}

	switch (npc->getId())
	{
	case 113: //Dagannoth Prime
	case 114: //Dagannoth Rex
	case 115: //Dagannoth Supreme
		npcHit += rand() % 12;
		break;
	case 116: //Kalphite Queen
		npcHit = rand() % 31;
		break;
	case 121: //Wintertodt
		npcHit = (rand() % player->skills->getLevel(hitpoints) + 10) * 0.10;
		break;
	case 123: //Dharok
		npcHit *= 1 + ((double)npc->getHitpoints() / (double)npc->getNpcDefinition().getHitpoints());
		break;
	case 124:
		break;
		if (!(rand() % 4)) npc->addHitpoints(npcHit);
	default:
		break;
	}

	return npcHit;
}