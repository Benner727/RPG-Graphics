#ifndef LOOTDEFINITION_H
#define LOOTDEFINITION_H

#include "DropDefinition.h"
#include <vector>

class LootDefinition
{
public:
	LootDefinition(int _id, std::vector<DropDefinition> _lootTable)
	{
		id = _id;
		lootTable = _lootTable;
	}

	~LootDefinition() {}

private:
	int id;
	std::vector<DropDefinition> lootTable;

public:
	int getId() { return id; }
	std::vector<DropDefinition> getLootTable() { return lootTable; }
};

#endif