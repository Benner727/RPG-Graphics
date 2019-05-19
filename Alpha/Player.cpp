#include "Player.h"

#include "Skills.h"
#include "Inventory.h"
#include "Equipment.h"
#include "PrayerBook.h"
#include "Prayer.h"
#include "Magic.h"
#include "Slayer.h"
#include "Bank.h"

#include "Fletching.h"
#include "Crafting.h"
#include "Herblore.h"

#include <fstream>

Player::Player(std::string _username)
{
	username = _username;
	initialize();
}

Player::~Player()
{
	save();

	delete skills;
	skills = nullptr;

	delete inventory;
	inventory = nullptr;

	delete equipment;
	equipment = nullptr;

	delete prayerBook;
	prayerBook = nullptr;

	delete prayer;
	prayer = nullptr;

	delete magic;
	magic = nullptr;

	delete slayer;
	slayer = nullptr;

	delete bank;
	bank = nullptr;

	delete fletching;
	fletching = nullptr;

	delete crafting;
	crafting = nullptr;

	delete herblore;
	herblore = nullptr;
}

void Player::initialize()
{
	combatDelay = 0, foodDelay = 0, potionDelay = 0;
	combatStance = 0;
	autoCast = false;
	inCombat = false;
	inBank = false;
	inShop = false;

	skills = new Skills(this);
	inventory = new Inventory(this);
	equipment = new Equipment(this);
	prayerBook = new PrayerBook(this);
	prayer = new Prayer(this);
	magic = new Magic(this);
	slayer = new Slayer(this);
	bank = new Bank(this);

	fletching = new Fletching(this);
	crafting = new Crafting(this);
	herblore = new Herblore(this);
}

void Player::tickDelay()
{
	if (combatDelay > 0)
		combatDelay--;
	else
	{
		if (equipment->getItem(3) != nullptr)
			combatDelay = equipment->getItem(3)->getWeaponDefinition()->getSpeed();
		else
			combatDelay = 5;
	}

	if (foodDelay > 0)
		foodDelay--;
	if (potionDelay > 0)
		potionDelay--;
}

void Player::eatDelay()
{
	if (inCombat)
	{
		combatDelay += 3 - potionDelay;
		foodDelay = 3;
	}
}

void Player::drinkDelay()
{
	if (inCombat)
	{
		combatDelay += 3 - foodDelay;
		potionDelay = 3;
	}
}

int Player::getAttackStyle() const
{
	if (autoCast)
		return 2;
	else if (equipment->getItem(3) != nullptr)
	{
		if (equipment->getItem(3)->getRangedDefinition() != nullptr)
			return 1;
	}
	return 0;
}

void Player::setCombatStance(int stance)
{
	switch (getAttackStyle())
	{
	case 0:
		if(combatStance < 4) combatStance = stance;
		else combatStance = 0;
		break;
	case 1:
		if (stance == 1) combatStance = 5;
		else combatStance = 4;
		break;
	case 2:
		combatStance = 6;
		break;
	}
}

void Player::respawn()
{
	inCombat = false;
	resetDelay();
	inventory->clear();
	equipment->clear();
	skills->reset();
}

void Player::save()
{
	std::ofstream outFile("save.txt");

	outFile << username << std::endl << std::endl;
	slayer->save();
	skills->save();
	inventory->save();
	equipment->save();
	bank->save();

	outFile.close();
}

void Player::load()
{
	std::ifstream infile("save.txt");

	std::getline(infile, username);
	slayer->load();
	skills->load();
	inventory->load();
	equipment->load();
	bank->load();

	infile.close();
}