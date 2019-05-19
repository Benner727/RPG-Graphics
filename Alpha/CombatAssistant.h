#ifndef COMBAT_ASSISTANT
#define COMBAT_ASSISTANT

#include "Player.h"
#include "Npc.h"

class CombatAssistant
{
public:
	CombatAssistant();

	~CombatAssistant();

private:
	bool hasSlayerLevel(Player*, Npc*);
	bool hasWeaponRequirement(Player*, Npc*);
	bool hasEquipmentRequirement(Player*, Npc*);

public:
	bool canAttack(Player*, Npc*);
	bool canKill(Player*, Npc*);
	int playerDamageModifier(Player*, Npc*, int);
	int npcDamageModifier(Npc*, Player*, int);
};

#endif