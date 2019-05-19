#ifndef SLAYERTASK_H
#define SLAYERTASK_H

#include <string>
#include <vector>

class SlayerTask
{
public:
	SlayerTask(std::string _name, int _level, std::vector<int> _id)
	{
		name = _name;
		level = _level;
		id = _id;
	}


	~SlayerTask() 
	{
	}

private:
	std::string name;
	int level;
	std::vector<int> id;

public:
	std::string getName() { return name; }
	int getLevel() { return level; }
	std::vector<int> getId() { return id; }
};

#endif