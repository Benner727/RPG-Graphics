#include "SetBonus.h"

#include "Equipment.h"
#include "Skills.h"


SetBonus::SetBonus()
{
}


SetBonus::~SetBonus()
{
}


bool SetBonus::dharokSet(const Player& player)
{
	if (player.equipment->getItem(0) != nullptr)
	{
		if (player.equipment->getItem(4) != nullptr)
		{
			if (player.equipment->getItem(6) != nullptr)
			{
				if (player.equipment->getItem(3) != nullptr)
				{
					if (player.equipment->getItem(0)->getId() == 1024 && //Dharok's helm
						player.equipment->getItem(4)->getId() == 1026 && //Dharok's platebody
						player.equipment->getItem(6)->getId() == 1028 && //Dharok's platelegs
						player.equipment->getItem(3)->getId() == 1030) //Dharok's greataxe
						return true;
				}
			}
		}
	}
	return false;
}

bool SetBonus::guthanSet(const Player& player)
{
	if (player.equipment->getItem(0) != nullptr)
	{
		if (player.equipment->getItem(4) != nullptr)
		{
			if (player.equipment->getItem(6) != nullptr)
			{
				if (player.equipment->getItem(3) != nullptr)
				{
					if (player.equipment->getItem(0)->getId() == 1032 && //Guthan's helm
						player.equipment->getItem(4)->getId() == 1034 && //Guthan's platebody
						player.equipment->getItem(6)->getId() == 1036 && //Guthan's chainskirt
						player.equipment->getItem(3)->getId() == 1038) //Guthan's warspear
						return true;
				}
			}
		}
	}
	return false;
}

bool SetBonus::voidSet(const Player& player)
{
	if (player.equipment->getItem(0) != nullptr)
	{
		if (player.equipment->getItem(4) != nullptr)
		{
			if (player.equipment->getItem(6) != nullptr)
			{
				if (player.equipment->getItem(3) != nullptr)
				{
					if (player.equipment->getItem(4)->getId() == 1010 && //Void knight top
						player.equipment->getItem(6)->getId() == 1012 && //Void knight robe
						player.equipment->getItem(3)->getId() == 1014) //Void knight gloves
					{
						switch (player.getAttackStyle())
						{
						case 0: //Melee
							if (player.equipment->getItem(0)->getId() == 1004)
								return true;
							break;
						case 1: //Ranged
							if (player.equipment->getItem(0)->getId() == 1006)
								return true;
							break;
						case 2: //Magic
							if (player.equipment->getItem(0)->getId() == 1008)
								return true;
							break;
						default:
							return false;
							break;
						}
					}
				}
			}
		}
	}
	return false;
}

double SetBonus::getDamageModifier(const Player& player)
{
	if (dharokSet(player))
		return 1 + ((double)player.skills->getEffect(0) / (double)player.skills->getLevel(0));
	else if (voidSet(player))
	{
		if (player.getAttackStyle() == 0)
			return 1.1;
		else if (player.getAttackStyle() == 1)
			return 1.2;
	}
	return 1;
}

void SetBonus::applyEffect(Player* player, int playerHit)
{
	if (guthanSet(*player))
		if (!(rand() % 4))
			player->skills->heal(playerHit);
}