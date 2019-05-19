#include "DefinitionLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <SDL.h>

DefinitionLoader* DefinitionLoader::sInstance = nullptr;

DefinitionLoader* DefinitionLoader::Instance()
{
	if (sInstance == nullptr)
		sInstance = new DefinitionLoader();

	return sInstance;
}

void DefinitionLoader::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

DefinitionLoader::DefinitionLoader()
{
	std::cout << "Loading game defitions..." << std::endl;
	loadItemDefinition();
	loadItemBonusDefinition();
	loadEquipmentDefinition();
	loadFoodDefinition();
	loadPotionDefinition();
	loadRangedDefinition();
	loadWeaponDefinition();
	loadNpcDefinition();
	loadLootDefinition();
	loadDungeonDefinition();
	loadShopDefinition();
	std::cout << "Game defitions loaded!" << std::endl;
}

DefinitionLoader::~DefinitionLoader()
{
	for (auto it = mItemDefinition.begin(); it != mItemDefinition.end();)
		it = mItemDefinition.erase(it);

	for (auto it = mItemBonusDefinition.begin(); it != mItemBonusDefinition.end();)
		it = mItemBonusDefinition.erase(it);

	for (auto it = mEquipmentDefinition.begin(); it != mEquipmentDefinition.end();)
		it = mEquipmentDefinition.erase(it);

	for (auto it = mFoodDefinition.begin(); it != mFoodDefinition.end();)
		it = mFoodDefinition.erase(it);

	for (auto it = mPotionDefinition.begin(); it != mPotionDefinition.end();)
		it = mPotionDefinition.erase(it);

	for (auto it = mRangedDefinition.begin(); it != mRangedDefinition.end();)
		it = mRangedDefinition.erase(it);

	for (auto it = mWeaponDefinition.begin(); it != mWeaponDefinition.end();)
		it = mWeaponDefinition.erase(it);

	for (auto it = mNpcDefinition.begin(); it != mNpcDefinition.end();)
		it = mNpcDefinition.erase(it);

	for (auto it = mLootDefinition.begin(); it != mLootDefinition.end();)
		it = mLootDefinition.erase(it);

	for (auto it = mDungeonDefinition.begin(); it != mDungeonDefinition.end();)
		it = mDungeonDefinition.erase(it);

	for (auto it = mShopDefinition.begin(); it != mShopDefinition.end();)
		it = mShopDefinition.erase(it);
}

void DefinitionLoader::loadItemDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "ItemDefinition.txt");
	if (!infile) std::cerr << "ItemDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading item definitions..." << std::endl;

	std::string name, texture;
	int id;
	bool stackable, note;
	int noteId, alchemyPrice, generalPrice;

	while (infile >> std::quoted(name) >> id >> stackable >> note >> noteId >> alchemyPrice >> generalPrice >> texture)
	{
		mItemDefinition.push_back(new ItemDefinition(name, id, stackable, note, noteId, alchemyPrice, generalPrice, texture));
	}

	infile.close();
	std::cout << "Item definitions loaded: " << mItemDefinition.size() << std::endl;
}

void DefinitionLoader::loadItemBonusDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "ItemBonusDefinition.txt");
	if (!infile) std::cerr << "ItemBonusDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading item bonus definitions..." << std::endl;

	int id, meleeatt, magicatt, rangeatt, meleedef, magicdef, rangedef, str, pray;

	while (infile >> id >> meleeatt >> magicatt >> rangeatt >> meleedef >> magicdef >> rangedef >> str >> pray)
	{
		mItemBonusDefinition.push_back(new ItemBonusDefinition(id, meleeatt, magicatt, rangeatt, meleedef, magicdef, rangedef, str, pray));
	}

	infile.close();
	std::cout << "Item bonus definitions loaded: " << mItemBonusDefinition.size() << std::endl;
}

void DefinitionLoader::loadEquipmentDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "EquipmentDefinition.txt", std::ifstream::in);
	if (!infile) std::cerr << "EquipmentDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading equipment definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id, slot, skillId, skillReq;
		char delim = ',';
		std::vector<EquipmentDefinition::SkillData> skillData;
		iss >> id >> slot;

		while (iss >> skillId >> delim >> skillReq)
			skillData.push_back(EquipmentDefinition::SkillData(skillId, skillReq));

		mEquipmentDefinition.push_back(new EquipmentDefinition(id, slot, skillData));
		skillData.clear();
	}

	infile.close();
	std::cout << "Equipment definitions loaded: " << mEquipmentDefinition.size() << std::endl;
}

void DefinitionLoader::loadFoodDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "FoodDefinition.txt");
	if (!infile) std::cerr << "FoodDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading food definitions..." << std::endl;

	int id, heal;

	while (infile >> id >> heal)
	{
		mFoodDefinition.push_back(new FoodDefinition(id, heal));
	}

	infile.close();
	std::cout << "Food definitions loaded: " << mFoodDefinition.size() << std::endl;
}

void DefinitionLoader::loadPotionDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "PotionDefinition.txt", std::ifstream::in);
	if (!infile) std::cerr << "PotionDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading potion definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id, replaceId, type, skillId, add;
		double modifier;
		char delim = ',';
		std::vector<PotionDefinition::SkillData> skillData;
		iss >> id >> replaceId >> type;

		while (iss >> skillId >> add >> delim >> modifier)
			skillData.push_back(PotionDefinition::SkillData(skillId, add, modifier));

		mPotionDefinition.push_back(new PotionDefinition(id, replaceId, type, skillData));
		skillData.clear();
	}

	infile.close();
	std::cout << "Potion definitions loaded: " << mPotionDefinition.size() << std::endl;
}

void DefinitionLoader::loadRangedDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "RangedDefinition.txt");
	if (!infile) std::cerr << "RangedDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading ranged definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id, type, _ammo;
		std::vector<int> ammo;

		iss >> id >> type;

		while (iss >> _ammo)
			ammo.push_back(_ammo);

		mRangedDefinition.push_back(new RangedDefinition(id, type != 0, ammo));
		ammo.clear();
	}

	infile.close();
	std::cout << "Ranged definitions loaded: " << mRangedDefinition.size() << std::endl;
}

void DefinitionLoader::loadWeaponDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "WeaponDefinition.txt");
	if (!infile) std::cerr << "WeaponDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading weapon definitions..." << std::endl;

	int id, is2h, speed;

	while (infile >> id >> is2h >> speed)
	{
		mWeaponDefinition.push_back(new WeaponDefinition(id, (is2h != 0), speed));
	}

	infile.close();
	std::cout << "Weapon definitions loaded: " << mWeaponDefinition.size() << std::endl;
}

void DefinitionLoader::loadNpcDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "NpcDefinition.txt");
	if (!infile) std::cerr << "NpcDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading npc definitions..." << std::endl;

	int id, level, hitpoints, maxHit, weakness, attackStyle, attackSpeed, attackStat, defenseStat;
	std::string name, texture;
	
	while (infile >> id >> std::quoted(name) >> level >> hitpoints >> maxHit >> weakness >> attackStyle >> attackSpeed >> attackStat >> defenseStat >> texture)
	{
		mNpcDefinition.push_back(new NpcDefinition(id, name, level, hitpoints, maxHit, weakness, attackStyle, attackSpeed, attackStat, defenseStat, texture));
	}

	infile.close();
	std::cout << "Npc definitions loaded: " << mNpcDefinition.size() << std::endl;
}

void DefinitionLoader::loadLootDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "LootDefinition.txt");
	if (!infile) std::cerr << "LootDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading loot definitions..." << std::endl;

	std::string line;
	std::vector<DropDefinition> loot;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id, chance, min, max, npc;
		char delim = ':';

		iss >> npc;

		while (iss >> id >> delim >> chance >> min >> delim >> max)
			loot.push_back(DropDefinition(id, chance, min, max));

		mLootDefinition.push_back(new LootDefinition(npc, loot));
		loot.clear();
	}

	infile.close();
	std::cout << "Loot definitions loaded: " << mLootDefinition.size() << std::endl;
}

void DefinitionLoader::loadDungeonDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "DungeonDefinition.txt");
	if (!infile) std::cerr << "DungeonDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading dungeon definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int id, temp;
		std::string name;
		std::vector<int> npcId;

		iss >> id >> std::quoted(name);

		while (iss >> temp)
			npcId.push_back(temp);

		mDungeonDefinition.push_back(new DungeonDefinition(id, name, npcId));
		npcId.clear();
	}

	infile.close();
	std::cout << "Dungeon definitions loaded: " << mDungeonDefinition.size() << std::endl;
}

void DefinitionLoader::loadShopDefinition()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Files/");

	std::ifstream infile(fullPath + "ShopDefinition.txt");
	if (!infile) std::cerr << "ShopDefinition.txt could not be opened!" << std::endl;
	else std::cout << "Loading shop definitions..." << std::endl;

	std::string line;
	std::vector<std::pair<int, int>> stock;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index, id, amount;
		std::string name;
		char delim = ',';
		iss >> index >> std::quoted(name);

		while (iss >> id >> delim >> amount)
			stock.push_back(std::make_pair(id, amount));

		mShopDefinition.push_back(new ShopDefinition(index, name, stock));
		stock.clear();
	}

	infile.close();
	std::cout << "Shop definitions loaded: " << mShopDefinition.size() << std::endl;
}

ItemDefinition* DefinitionLoader::GetItemDefinition(int id)
{
	for (int i = 0; i < mItemDefinition.size(); i++)
	{
		if (id == mItemDefinition[i]->getId())
			return mItemDefinition[i];
	}

	return nullptr;
}

ItemBonusDefinition* DefinitionLoader::GetItemBonusDefinition(int id)
{
	for (int i = 0; i < mItemBonusDefinition.size(); i++)
	{
		if (id == mItemBonusDefinition[i]->getId())
			return mItemBonusDefinition[i];
	}

	return nullptr;
}

EquipmentDefinition* DefinitionLoader::GetEquipmentDefinition(int id)
{
	for (int i = 0; i < mEquipmentDefinition.size(); i++)
	{
		if (id == mEquipmentDefinition[i]->getId())
			return mEquipmentDefinition[i];
	}

	return nullptr;
}

FoodDefinition* DefinitionLoader::GetFoodDefinition(int id)
{
	for (int i = 0; i < mFoodDefinition.size(); i++)
	{
		if (id == mFoodDefinition[i]->getId())
			return mFoodDefinition[i];
	}

	return nullptr;
}

PotionDefinition* DefinitionLoader::GetPotionDefinition(int id)
{
	for (int i = 0; i < mPotionDefinition.size(); i++)
	{
		if (id == mPotionDefinition[i]->getId())
			return mPotionDefinition[i];
	}

	return nullptr;
}

RangedDefinition* DefinitionLoader::GetRangedDefinition(int id)
{
	for (int i = 0; i < mRangedDefinition.size(); i++)
	{
		if (id == mRangedDefinition[i]->getId())
			return mRangedDefinition[i];
	}

	return nullptr;
}

WeaponDefinition* DefinitionLoader::GetWeaponDefinition(int id)
{
	for (int i = 0; i < mWeaponDefinition.size(); i++)
	{
		if (id == mWeaponDefinition[i]->getId())
			return mWeaponDefinition[i];
	}

	return nullptr;
}

NpcDefinition* DefinitionLoader::GetNpcDefinition(int id)
{
	for (int i = 0; i < mNpcDefinition.size(); i++)
	{
		if (id == mNpcDefinition[i]->getId())
			return mNpcDefinition[i];
	}

	return nullptr;
}

LootDefinition* DefinitionLoader::GetLootDefinition(int id)
{
	for (int i = 0; i < mLootDefinition.size(); i++)
	{
		if (id == mLootDefinition[i]->getId())
			return mLootDefinition[i];
	}

	return nullptr;
}

DungeonDefinition* DefinitionLoader::GetDungeonDefinition(int id)
{
	for (int i = 0; i < mDungeonDefinition.size(); i++)
	{
		if (id == mDungeonDefinition[i]->getId())
			return mDungeonDefinition[i];
	}

	return nullptr;
}

ShopDefinition* DefinitionLoader::GetShopDefinition(int id)
{
	for (int i = 0; i < mShopDefinition.size(); i++)
	{
		if (id == mShopDefinition[i]->getId())
			return mShopDefinition[i];
	}

	return nullptr;
}