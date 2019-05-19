#ifndef MARKET_H
#define MARKET_H

#include "Shop.h"

class Market
{
public:
	Market(Player*);
	~Market();

	void Update();
	void Render();

private:
	Player *mPlayer;
	int mCurrentShop;

	InputManager *mInputManager;

	DefinitionLoader *mDefinitionLoader;

	Texture *mBackground;
	Texture *mTabText;

	Texture* mEscapeButton;
	bool exitMarket;

	std::vector<Texture*> mShops;

	std::map<int, Shop*> mShopMap;
	Shop* mShop;

	Shop* AssignShop(int);
public:
	bool LeaveMarket();
};

#endif