#ifndef DUNGEONDEFINITION_H
#define DUNGEONDEFINITION_H

#include <string>
#include <vector>

class DungeonDefinition
{
public:
	DungeonDefinition() {};

	DungeonDefinition(int _id, std::string _name, std::vector<int> _npcId)
	{
		id = _id;
		name = _name;
		npcId = _npcId;
	}

	~DungeonDefinition() {};

private:
	int id;
	std::string name;
	std::vector<int> npcId;

public:
	int getId() const { return id; }
	std::string getName() const { return name; }
	std::vector<int> getNpcId() const { return npcId; }
};

#endif