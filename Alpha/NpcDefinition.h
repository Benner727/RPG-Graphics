#ifndef NPCDEFINITION_H
#define NPCDEFINITION_H

#include <string>

class NpcDefinition
{
public:
	NpcDefinition() {};

	NpcDefinition(int _id, std::string _name, int _level, int _hitpoints, int _maxHit, int _weakness, int _attackStyle, int _attackSpeed, int _attackStat, int _defenseStat, std::string _texture)
	{
		id = _id;
		name = _name;
		level = _level;
		hitpoints = _hitpoints;
		maxHit = _maxHit;
		weakness = _weakness;
		attackStyle = _attackStyle;
		attackSpeed = _attackSpeed;
		attackStat = _attackStat;
		defenseStat = _defenseStat;
		texture = _texture;
	};

	~NpcDefinition() {};

private:
	int id;
	std::string name;
	int level,
		hitpoints,
		maxHit,
		weakness, //0 = none, 1 = melee, 2 = ranged, 3 = mage
		attackStyle, // 0 = melee, 1 = ranged, 2 = magic
		attackSpeed,
		attackStat,
		defenseStat;
	std::string texture;

public:
	int getId() const { return id; }
	std::string getName() const { return name; }
	int getLevel() const { return level; }
	int getHitpoints() const { return hitpoints; }
	int getMaxHit() const { return maxHit; }
	int getWeakness() const { return weakness; }
	int getAttackStyle() const { return attackStyle; }
	int getAttackSpeed() const { return attackSpeed; }
	int getAttackStat() const { return attackStat; }
	int getDefenseStat() const { return defenseStat; }
	std::string getTexture() const { return texture; }
};

#endif