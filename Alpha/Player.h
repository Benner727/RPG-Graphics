#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Skills;
class Inventory;
class Equipment;
class PrayerBook;
class Prayer;
class Magic;
class Slayer;
class Bank;

class Fletching;
class Crafting;
class Herblore;

class Player
{
public:
	Player(std::string);

	~Player();

	Skills *skills;
	Inventory *inventory;
	Equipment *equipment;
	PrayerBook *prayerBook;
	Prayer *prayer;
	Magic *magic;
	Slayer *slayer;
	Bank* bank;

	Fletching* fletching;
	Crafting* crafting;
	Herblore* herblore;

private:
	std::string username;
	int combatDelay, foodDelay, potionDelay,
		combatStance;
	bool autoCast, inCombat, inBank, inShop;

	void initialize();
public:
	void setName(std::string str) { username = str; }
	void tickDelay();
	void eatDelay();
	void drinkDelay();
	void resetDelay() { combatDelay = foodDelay = potionDelay = 0; }
	void setCombatStance(int);
	void toggleAutoCast() { autoCast = !autoCast; }
	void setAutoCast(bool b) { autoCast = b; }
	void setInCombat(bool b) { inCombat = b; }
	void setInBank(bool b) { inBank = b; }
	void setInShop(bool b) { inShop = b; }

	std::string getName() const { return username; }
	bool hasEatDelay() const { return foodDelay > 0; }
	bool hasDrinkDelay() const { return potionDelay > 0; }
	int getCombatDelay() const { return combatDelay; }
	int getAttackStyle() const;
	int getCombatStance() const { return combatStance; }
	bool getAutoCast() const { return autoCast; }
	bool getInCombat() { return inCombat; }
	bool getInBank() { return inBank; }
	bool getInShop() { return inShop; }

	void respawn();

	void save();
	void load();
};

#endif