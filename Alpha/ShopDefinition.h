#ifndef SHOPDEFINITION_H
#define SHOPDEFINITION_H

#include <string>
#include <vector>

class ShopDefinition
{
public:
	ShopDefinition(int _id, std::string _name, std::vector<std::pair<int, int>> _stock)
	{
		id = _id;
		name = _name;
		stock = _stock;
	};

	~ShopDefinition() {};

private:
	int id;
	std::string name;
	std::vector<std::pair<int, int>> stock;

public:
	int getId() { return id; }
	std::string getName() { return name; }
	std::vector<std::pair<int, int>> getStock() { return stock; }
};

#endif