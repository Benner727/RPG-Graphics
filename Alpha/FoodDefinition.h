#ifndef FOODDEFINITION_H
#define FOODDEFINITION_H

class FoodDefinition
{
public:
	FoodDefinition() {};

	FoodDefinition(int _id, int _heal)
	{
		id = _id;
		heal = _heal;
	}

	~FoodDefinition() {};

private:
	int id,
		heal;

public:
	int getId() const { return id; }
	int getHeal() const { return heal; }
};

#endif