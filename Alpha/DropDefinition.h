#ifndef DROPDEFINITION_H
#define DROPDEFINITION_H

class DropDefinition
{
public:
	DropDefinition(int _index, int _chance, int _min, int _max)
	{
		index = _index;
		chance = _chance;
		min = _min;
		max = _max;
	}

	~DropDefinition() {}

private:
	int index,
		chance,
		min,
		max;

public:
	int getIndex() { return index; }
	int getChance() { return chance; }
	int getMin() { return min; }
	int getMax() { return max; }
};

#endif