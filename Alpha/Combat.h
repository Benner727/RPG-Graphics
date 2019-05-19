#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Npc.h"
#include "Ground.h"
#include "CombatAssistant.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

class Combat
{
public:
	Combat(Player*, int);
	~Combat();

	void Update();
	void Render();

	bool ExitCombat() { return exitCombat; }
private:
	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Player *player;
	Npc *npc;
	Ground *ground;

	CombatAssistant *combatAssistant;

	Texture* mBackground;

	Texture* mNameText;
	Texture* mHPBase;
	Texture* mHPOverlay;

	Texture* mWarningText;

	Texture* mPlayerHit;
	Texture* mPlayerSplat;

	Texture* mNpcHit;
	Texture* mNpcSplat;

	Texture* mFightText;

	Texture* mEscapeButton;

	int playerInput,
		playerHit,
		npcHit;

	bool attack;
	bool exitCombat;

	unsigned int mStartTicks;

	void SetHealthBar();
	void RenderHealthBar();

	int meleeAttack(Player*, Npc*);
	int rangedAttack(Player*, Npc*);
	int magicAttack(Player*, Npc*);

	int meleeAttack(Npc*, Player*);
	int rangedAttack(Npc*, Player*);
	int magicAttack(Npc*, Player*);

	bool cantAttack();

	int getPlayerDamage();
	int getNpcDamage();

	void fight();

	void CreatePlayerSplat();
	void CreateNpcSplat();
};

#endif