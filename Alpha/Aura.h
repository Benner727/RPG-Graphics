#ifndef AURA_H
#define AURA_H

#include <string>

enum AuraType { ATTACK, STRENGTH, DEFENSE, COMBAT, MAGE_RANGE, OVER_HEAD };

class Aura
{
public:
	Aura(std::string _name, int _level, double _drainRate, AuraType _auraType)
	{
		name = _name;
		level = _level;
		drainRate = _drainRate;
		auraType = _auraType;
	}

	~Aura() 
	{

	}

private:
	std::string name;
	int level;
	double drainRate;
	AuraType auraType;

public:
	std::string getName() { return name; }
	int getLevel() { return level; }
	double getDrainRate() { return drainRate; }
	AuraType getAuraType() { return auraType; }
};

#endif