#ifndef ITEM_H
#define ITEM_H

#include "Texture.h"
#include "DefinitionLoader.h"

class Item : public GameEntity
{
public:
	Item();
	Item(int, int);
	~Item();

	friend std::istream& operator >> (std::istream& in, Item& obj);
	friend std::ostream& operator << (std::ostream& in, const Item& obj);

private:
	int id,
		amount;

	Texture mItemTexture;
	Texture mNoteTexture;
	DefinitionLoader *mDefinitionLoader;

	std::vector<Texture*> mAmountText;

	void CreateAmountText();
public:
	int getId() { return id; }
	int getAmount() { return amount; }
	std::string getName();

	void setId(int i) { id = i; }
	void setAmount(int i) { amount = i; }

	void add() { amount++; }
	void add(int am) { amount += am; }
	void remove() { amount--; }
	void remove(int am) { amount -= am; }
	void note();
	void unNote();

	ItemDefinition* getItemDefinition() { return mDefinitionLoader->GetItemDefinition(id); }
	ItemBonusDefinition* getItemBonusDefinition() { return mDefinitionLoader->GetItemBonusDefinition(id); }
	EquipmentDefinition* getEquipmentDefinition() { return mDefinitionLoader->GetEquipmentDefinition(id); }
	FoodDefinition* getFoodDefinition() { return mDefinitionLoader->GetFoodDefinition(id); }
	PotionDefinition* getPotionDefinition() { return mDefinitionLoader->GetPotionDefinition(id); }
	RangedDefinition* getRangedDefinition() { return mDefinitionLoader->GetRangedDefinition(id); }
	WeaponDefinition* getWeaponDefinition() { return mDefinitionLoader->GetWeaponDefinition(id); }

	bool Intersects(Vector2);
	void Render();
};

#endif