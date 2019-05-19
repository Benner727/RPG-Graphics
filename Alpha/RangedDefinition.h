#ifndef RANGEDDEFINITION_H
#define RANGEDDEFINITION_H

#include <vector>

class RangedDefinition
{
public:
	RangedDefinition() {};

	RangedDefinition(int _id, bool _type, std::vector<int> _ammo)
	{
		id = _id;
		type = _type;
		ammo = _ammo;
	};

	~RangedDefinition() {};

private:
	int id;
	bool type; //Shot or thrown
	std::vector<int> ammo;

public:
	int getId() const { return id; }
	bool getType() const { return type; }
	std::vector<int> getAmmo() const { return ammo; }
};

#endif