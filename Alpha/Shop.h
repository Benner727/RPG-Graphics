#ifndef SHOP_H
#define SHOP_H

#include "Player.h"
#include "Inventory.h"
#include "ShopDefinition.h"
#include "DefinitionLoader.h"

class Shop
{
public:
	Shop(int, Player*);
	~Shop();

	void Update();
	void Render();

	bool LeaveShop() { if (exitShop) { exitShop = false; mPlayer->setInShop(false); return true; } else return false; }
private:
	std::string name;
	std::vector<Item> stock;

	Player *mPlayer;

	int mSelectedSlot;

	InputManager *mInputManager;

	DefinitionLoader *mDefinitionLoader;

	Texture *mNameText;

	std::vector<Texture*> mPrice;

	Texture* mRightClick[4];
	Texture* mAltBackground;
	bool mRightClicked;

	bool inventory;

	Texture *mItemText;
	Vector2 mTextPos;

	Texture* mEscapeButton;
	bool exitShop;

	void SetPrice();

	bool canAdd(Item);
	void add(Item*, int);

	void buy(int);
	void sell(int);
};

#endif