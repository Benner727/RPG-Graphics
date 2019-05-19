#ifndef ITEMBONUSDEFINITION_H
#define ITEMBONUSDEFINITION_H

class ItemBonusDefinition
{
public:
	ItemBonusDefinition() {};

	ItemBonusDefinition(int _id, int _meleeatt, int _magicatt, int _rangeatt, int _meleedef, int _magicdef, int _rangedef, int _str, int _prayer)
	{
		id = _id;
		bonus[0] = _meleeatt;
		bonus[1] = _magicatt;
		bonus[2] = _rangeatt;
		bonus[3] = _meleedef;
		bonus[4] = _magicdef;
		bonus[5] = _rangedef;
		bonus[6] = _str;
		bonus[7] = _prayer;
	};

	~ItemBonusDefinition() {};

private:
	int id;
	int bonus[8];

public:
	int getId() const { return id; }
	int getMeleeAtt() const { return bonus[0]; }
	int getMagicAtt() const { return bonus[1]; }
	int getRangeAtt() const { return bonus[2]; }
	int getMeleeDef() const { return bonus[3]; }
	int getMagicDef() const { return bonus[4]; }
	int getRangeDef() const { return bonus[5]; }
	int getStrength() const { return bonus[6]; }
	int getPrayer() const { return bonus[7]; }
};

#endif