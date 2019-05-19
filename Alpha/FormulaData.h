#ifndef FORMULADATA_H
#define FORMULADATA_H

#include <random>

class FormulaData
{
public:
	FormulaData();
	~FormulaData();

private:
	std::uniform_real_distribution<> dist;
	std::default_random_engine generator;

	double getChance(double, double);

public:
	bool isAccurateHit(double, double);
};

#endif