#include "Combat.h"

#include <iostream>
#include "FormulaData.h"
#include "MeleeFormulas.h"
#include "RangedFormulas.h"
#include "MagicFormulas.h"
#include <random>
#include <ctime>
#include "Skills.h"
#include "Equipment.h"
#include "Magic.h"
#include "PrayerBook.h"
#include "Inventory.h"
#include "Slayer.h"
#include "Prayer.h"


Combat::Combat(Player *_player, int id)
{
	player = _player;

	npc = new Npc(id);
	npc->Pos(Vector2(190, 170));

	ground = new Ground(player);

	combatAssistant = new CombatAssistant;

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	playerInput = -1;
	playerHit = 0;
	npcHit = 0;

	attack = false;

	mStartTicks = SDL_GetTicks();

	mBackground = new Texture("CombatBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	//Npc Display
	delete mNameText;
	mNameText = new Texture(npc->getNpcDefinition().getName() + " (Level " + std::to_string(npc->getNpcDefinition().getLevel()) + ")", "alagard.ttf", 18, { 0, 0, 128 });
	mNameText->Pos(Vector2(190, 108));

	mHPBase = new Texture("PlayerHPBar.png", 0, 0, 192, 65);
	mHPBase->Scale(Vector2(1.0f, 0.47f));
	mHPBase->Pos(Vector2(190, 130));

	mHPOverlay = new Texture("PlayerHPBar.png", 0, 65, 188, 60);

	SetHealthBar();

	mWarningText = nullptr;

	mPlayerHit = nullptr;
	mPlayerSplat = nullptr;

	mNpcHit = nullptr;
	mNpcSplat = nullptr;

	mFightText = nullptr;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	exitCombat = false;
}

Combat::~Combat()
{
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	player->setInCombat(false);
	player->resetDelay();
	player = nullptr;

	delete npc;
	npc = nullptr;

	delete ground;
	ground = nullptr;

	delete combatAssistant;
	combatAssistant = nullptr;

	delete mBackground;
	mBackground = nullptr;

	if (mPlayerSplat != nullptr)
	{
		delete mPlayerHit;
		mPlayerHit = nullptr;

		delete mPlayerSplat;
		mPlayerSplat = nullptr;
	}

	if (mNpcSplat != nullptr)
	{
		delete mNpcHit;
		mNpcHit = nullptr;

		delete mNpcSplat;
		mNpcSplat = nullptr;
	}

	if (mFightText != nullptr)
	{
		delete mFightText;
		mFightText = nullptr;
	}

	delete mEscapeButton;
	mEscapeButton = nullptr;
}


void Combat::Update()
{
	if (exitCombat)
		exitCombat = false;

	if (attack)
	{
		fight();

		if (!npc->getHitpoints() || !player->skills->getEffect(SKILL::hitpoints))
		{
			if (SDL_GetTicks() > mStartTicks + 600)
			{
				if (!npc->getHitpoints())
				{
					int id = npc->getId();
					ground->AddLoot(id);
					delete npc;
					npc = new Npc(id);
					npc->Pos(Vector2(190, 170));
				}
				else if (!player->skills->getEffect(SKILL::hitpoints))
				{
					player->respawn();
					exitCombat = true;
				}

				attack = false;
				player->setInCombat(false);
				player->resetDelay();

				if (mPlayerSplat != nullptr)
				{
					delete mPlayerHit;
					mPlayerHit = nullptr;

					delete mPlayerSplat;
					mPlayerSplat = nullptr;
				}

				if (mNpcSplat != nullptr)
				{
					delete mNpcHit;
					mNpcHit = nullptr;

					delete mNpcSplat;
					mNpcSplat = nullptr;
				}
			}
		}
		SetHealthBar();
	}
	else if (mInputManager->MouseButtonPressed(InputManager::left) && npc->Intersects(mInputManager->MousePos()))
			attack = true;

	if (mInputManager->MouseButtonPressed(InputManager::left) && mEscapeButton->Intersects(mInputManager->MousePos()))
		exitCombat = true;

	if (npc->Intersects(mInputManager->MousePos()) && !attack)
	{
		if(mFightText == nullptr)
			mFightText = new Texture("Attack", "alagard.ttf", 24, { 139, 0, 0 });
		mFightText->Pos(mInputManager->MousePos());
	}
	else if ((mFightText != nullptr && !npc->Intersects(mInputManager->MousePos())) || attack)
	{
		delete mFightText;
		mFightText = nullptr;
	}

	ground->Update();
}

void Combat::Render()
{
	mBackground->Render();

	npc->Render();
	RenderHealthBar();
	mNameText->Render();

	if (mPlayerSplat != nullptr)
	{
		mPlayerSplat->Render();
		mPlayerHit->Render();
	}

	if (mNpcSplat != nullptr)
	{
		mNpcSplat->Render();
		mNpcHit->Render();
	}

	if (mWarningText != nullptr)
		mWarningText->Render();

	if (mFightText != nullptr)
		mFightText->Render();

	mEscapeButton->Render();

	ground->Render();
}

void Combat::SetHealthBar()
{
	float healthRatio = (float)npc->getHitpoints() / (float)npc->getNpcDefinition().getHitpoints();

	mHPOverlay->Scale(Vector2(1.0f * healthRatio, 0.47f));
	mHPOverlay->Pos(Vector2(190 - (94 * (1.0 - healthRatio)), 130));
}

void Combat::RenderHealthBar()
{
	mHPBase->Render();
	mHPOverlay->Render();
}

int Combat::meleeAttack(Player* player, Npc* npc)
{
	MeleeFormulas meleeFormulas;
	double attackRoll = meleeFormulas.getAttackRoll(*player);
	double defenseRoll = meleeFormulas.getDefenseRoll(*npc);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % (int)meleeFormulas.calculateBasedamage(*player) + 1;
		return damage;
	}
	else
		return 0;
}

int Combat::rangedAttack(Player* player, Npc* npc)
{
	RangedFormulas rangedFormulas;
	double attackRoll = rangedFormulas.getAttackRoll(*player);
	double defenseRoll = rangedFormulas.getDefenseRoll(*npc);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % (int)rangedFormulas.calculateBasedamage(*player) + 1;
		return damage;
	}
	else
		return 0;
}

int Combat::magicAttack(Player* player, Npc* npc)
{
	MagicFormulas magicFormulas;
	double attackRoll = magicFormulas.getAttackRoll(*player);
	double defenseRoll = magicFormulas.getDefenseRoll(*npc);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % (int)magicFormulas.calculateBasedamage(*player) + 1;
		return damage;
	}
	else
		return 0;
}

int Combat::meleeAttack(Npc* npc, Player* player)
{
	MeleeFormulas meleeFormulas;
	double attackRoll = meleeFormulas.getAttackRoll(*npc);
	double defenseRoll = meleeFormulas.getDefenseRoll(*player);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % npc->getNpcDefinition().getMaxHit() + 1;
		return damage;
	}
	else
		return 0;
}

int Combat::rangedAttack(Npc* npc, Player* player)
{
	RangedFormulas rangedFormulas;
	double attackRoll = rangedFormulas.getAttackRoll(*npc);
	double defenseRoll = rangedFormulas.getDefenseRoll(*player);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % npc->getNpcDefinition().getMaxHit() + 1;
		return damage;
	}
	else
		return 0;
}

int Combat::magicAttack(Npc* npc, Player* player)
{
	MagicFormulas magicFormulas;
	double attackRoll = magicFormulas.getAttackRoll(*npc);
	double defenseRoll = magicFormulas.getDefenseRoll(*player);

	FormulaData formulaData;
	if (formulaData.isAccurateHit(attackRoll, defenseRoll))
	{
		int damage = rand() % npc->getNpcDefinition().getMaxHit() + 1;
		return damage;
	}
	else
		return 0;
}

bool Combat::cantAttack()
{
	if (player->getAttackStyle() == 1)
	{
		if (!player->equipment->hasAmmo())
		{
			mWarningText = new Texture("You are out of ammo!", "alagard.ttf", 32, { 178, 34, 34 });
			mWarningText->Pos(Vector2(215, 25));
			return true;
		}
	}
	else if (player->getAttackStyle() == 2)
	{
		if (!player->magic->hasRunes())
		{
			mWarningText = new Texture("You don't have the runes to cast that spell!", "alagard.ttf", 32, { 178, 34, 34 });
			mWarningText->Pos(Vector2(215, 25));
			return true;
		}
	}
	
	return false;
}

int Combat::getPlayerDamage()
{
	switch (player->getAttackStyle())
	{
	case 0:
		playerHit = meleeAttack(player, npc);
		break;
	case 1:
		playerHit = rangedAttack(player, npc);
		player->equipment->useAmmo();
		break;
	case 2:
		playerHit = magicAttack(player, npc);
		player->magic->castSpell();
		break;
	}

	if (!combatAssistant->canAttack(player, npc))
		playerHit = 0;

	playerHit = combatAssistant->playerDamageModifier(player, npc, playerHit);
	if (player->getAttackStyle() == npc->getNpcDefinition().getWeakness()) playerHit *= 1.10;

	if (playerHit >= npc->getHitpoints())
		if (combatAssistant->canKill(player, npc))
		{
			playerHit = npc->getHitpoints();
			player->slayer->checkKill(npc);
		}
		else
			playerHit = npc->getHitpoints() - 1;

	return playerHit;
}

int Combat::getNpcDamage()
{
	switch (npc->getNpcDefinition().getAttackStyle())
	{
	case 0:
		npcHit = meleeAttack(npc, player);
		break;
	case 1:
		npcHit = rangedAttack(npc, player);
		break;
	case 2:
		npcHit = magicAttack(npc, player);
		break;
	}

	npcHit = combatAssistant->npcDamageModifier(npc, player, npcHit);

	if (npcHit > player->skills->getEffect(hitpoints))
		npcHit = player->skills->getEffect(hitpoints);

	return npcHit;
}

void Combat::fight()
{
	static bool playerAttack = true;
	static bool npcAttack = true;

	if (!player->getInCombat())
		playerAttack = npcAttack = true;

	if (player->skills->getEffect(hitpoints) && npc->getHitpoints())
	{
		player->setInCombat(true);

		//Player is attacking npc
		if (!player->getCombatDelay() && playerAttack)
		{
			if (!cantAttack())
			{
				playerHit = getPlayerDamage();

				//Create splat
				CreatePlayerSplat();

				//Play Sound
				mAudioManager->PlaySFX("hit.wav", 0, 2);

				npc->subHitpoints(playerHit);
				player->skills->addCombatExperience(playerHit);
			}
			
			playerAttack = false;
		}

		//Npc is attacking player
		if (!npc->getDelay() && npcAttack)
		{
			npcHit = getNpcDamage();

			//Create splat
			CreateNpcSplat();

			//Play Sound
			mAudioManager->PlaySFX("hit.wav", 0, 2);

			player->skills->subHitpoints(npcHit);

			npcAttack = false;
		}

		if (SDL_GetTicks() > mStartTicks + 600)
		{
			if (player->getCombatDelay())
			{
				if (mPlayerSplat != nullptr)
				{
					delete mPlayerHit;
					mPlayerHit = nullptr;

					delete mPlayerSplat;
					mPlayerSplat = nullptr;
				}
				
				if (mWarningText != nullptr)
				{
					delete mWarningText;
					mWarningText = nullptr;
				}
			}

			if (npc->getDelay())
			{
				if (mNpcSplat != nullptr)
				{
					delete mNpcHit;
					mNpcHit = nullptr;

					delete mNpcSplat;
					mNpcSplat = nullptr;
				}
			}

			player->tickDelay();
			npc->tickDelay();
			mStartTicks = SDL_GetTicks();

			playerAttack = true;
			npcAttack = true;
		}
	}
}

void Combat::CreatePlayerSplat()
{
	int x = rand() % 30;
	int y = rand() % 30;

	mPlayerHit = new Texture(std::to_string(playerHit), "alagard.ttf", 20, { 255, 255, 255 });
	mPlayerHit->Pos(Vector2(230 + x, 172 + y));

	if (!playerHit)
	{
		mPlayerSplat = new Texture("Miss_Splat.png");
		mPlayerSplat->Scale(Vector2(1.1f, 1.1f));
	}
	else if (playerHit < 0)
	{
		mPlayerSplat = new Texture("Heal_Splat.png");
	}
	else if (playerHit > 0)
	{
		mPlayerSplat = new Texture("Hit_Splat.png");
	}

	mPlayerSplat->Pos(Vector2(230 + x, 170 + y));

	if (playerHit > 9)
		mPlayerSplat->Scale(Vector2(1.33f, 1.33f));
	else if (playerHit > 99)
		mPlayerSplat->Scale(Vector2(1.66f, 1.66f));
}

void Combat::CreateNpcSplat()
{
	int x = rand() % 30;
	int y = rand() % 30;

	mNpcHit = new Texture(std::to_string(npcHit), "alagard.ttf", 20, { 255, 255, 255 });
	mNpcHit->Pos(Vector2(200 + x, 302 + y));

	if (!npcHit)
	{
		mNpcSplat = new Texture("Miss_Splat.png");
		mNpcSplat->Scale(Vector2(1.1f, 1.1f));
	}
	else if (npcHit < 0)
	{
		mNpcSplat = new Texture("Heal_Splat.png");
	}
	else if (npcHit > 0)
	{
		mNpcSplat = new Texture("Hit_Splat.png");
	}

	mNpcSplat->Pos(Vector2(200 + x, 300 + y));

	if (npcHit > 9)
		mNpcSplat->Scale(Vector2(1.33f, 1.33f));
	else if (npcHit > 99)
		mNpcSplat->Scale(Vector2(1.66f, 1.66f));
}