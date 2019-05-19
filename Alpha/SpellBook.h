#include <string>

#include "Item.h"

#ifndef SPELLBOOK_H
#define SPELLBOOK_H

class SpellBook
{
public:
	SpellBook(std::string _name, std::vector<Item> _runes, int _requirement, int _damage, int _baseExp)
	{
		name = _name;
		runes = _runes;
		requirement = _requirement;
		damage = _damage;
		baseExp = _baseExp;
	}

	~SpellBook()
	{

	}

private:
	std::string name;
	std::vector<Item> runes;
	int requirement,
		damage,
		baseExp;

public:
	std::string getName() const { return name; }
	std::vector<Item> getRunes() const { return runes; }
	int getRequirement() const { return requirement; }
	int getDamage() const { return damage; }
	int getBaseExp() const { return baseExp; }
};

#endif