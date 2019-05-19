#ifndef DEFINITIONLOADER_H
#define DEFINITIONLOADER_H

#include "ItemDefinition.h"
#include "ItemBonusDefinition.h"
#include "EquipmentDefinition.h"
#include "FoodDefinition.h"
#include "PotionDefinition.h"
#include "RangedDefinition.h"
#include "WeaponDefinition.h"

#include "NpcDefinition.h"
#include "LootDefinition.h"

#include "DungeonDefinition.h"

#include "ShopDefinition.h"

class DefinitionLoader
{
public:
	static DefinitionLoader* Instance();
	static void Release();

	ItemDefinition* GetItemDefinition(int id);
	ItemBonusDefinition* GetItemBonusDefinition(int id);
	EquipmentDefinition* GetEquipmentDefinition(int id);
	FoodDefinition* GetFoodDefinition(int id);
	PotionDefinition* GetPotionDefinition(int id);
	RangedDefinition* GetRangedDefinition(int id);
	WeaponDefinition* GetWeaponDefinition(int id);
	NpcDefinition* GetNpcDefinition(int id);
	LootDefinition* GetLootDefinition(int id);
	DungeonDefinition* GetDungeonDefinition(int id);
	ShopDefinition* GetShopDefinition(int id);

private:
	DefinitionLoader();
	~DefinitionLoader();
	
	static DefinitionLoader* sInstance;

	std::vector<ItemDefinition*> mItemDefinition;
	std::vector<ItemBonusDefinition*> mItemBonusDefinition;
	std::vector<EquipmentDefinition*> mEquipmentDefinition;
	std::vector<FoodDefinition*> mFoodDefinition;
	std::vector<PotionDefinition*> mPotionDefinition;
	std::vector<RangedDefinition*> mRangedDefinition;
	std::vector<WeaponDefinition*> mWeaponDefinition;
	std::vector<NpcDefinition*> mNpcDefinition;
	std::vector<LootDefinition*> mLootDefinition;
	std::vector<DungeonDefinition*> mDungeonDefinition;
	std::vector<ShopDefinition*> mShopDefinition;

	void loadItemDefinition();
	void loadItemBonusDefinition();
	void loadEquipmentDefinition();
	void loadFoodDefinition();
	void loadPotionDefinition();
	void loadRangedDefinition();
	void loadWeaponDefinition();
	void loadNpcDefinition();
	void loadLootDefinition();
	void loadDungeonDefinition();
	void loadShopDefinition();
};

#endif