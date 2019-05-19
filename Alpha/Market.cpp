#include "Market.h"

Market::Market(Player* player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();
	mDefinitionLoader = DefinitionLoader::Instance();

	mCurrentShop = -1;

	mBackground = new Texture("ShopBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mTabText = new Texture("Market", "alagard.ttf", 72, { 25, 25, 25 });
	mTabText->Pos(Vector2(205, 35));

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	exitMarket = false;

	mShop = nullptr;
	
	int i = 0;
	while (mDefinitionLoader->GetShopDefinition(i) != nullptr)
	{
		mShops.push_back(new Texture(mDefinitionLoader->GetShopDefinition(i)->getName(), "alagard.ttf", 22, { 255, 255, 255 }));
		mShops.back()->Pos(Vector2(205, 80 + 23 * i));
		i++;
	}
}

Market::~Market()
{
	mPlayer = nullptr;

	mInputManager = nullptr;
	mDefinitionLoader = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mTabText;
	mTabText = nullptr;

	delete mEscapeButton;
	mEscapeButton = nullptr;

	mShop = nullptr;

	for (auto it = mShops.begin(); it != mShops.end();)
		it = mShops.erase(it);

	for (auto _shop : mShopMap)
	{
		if (_shop.second != nullptr)
			delete _shop.second;
	}

	mShopMap.clear();
}

void Market::Update()
{
	if (mShop == nullptr)
	{
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{

			if (mEscapeButton->Intersects(mInputManager->MousePos()))
				exitMarket = true;

			for (int i = 0; i < mShops.size(); i++)
			{
				if (mShops[i]->Intersects(mInputManager->MousePos()))
					mShop = AssignShop(i);
			}
		}
	}
	else
	{
		mShop->Update();

		if (mShop->LeaveShop())
			mShop = nullptr;
	}
}

void Market::Render()
{
	mBackground->Render();

	if (mShop == nullptr)
	{
		mTabText->Render();
		mEscapeButton->Render();

		for (int i = 0; i < mShops.size(); i++)
			mShops[i]->Render();
	}
	else
		mShop->Render();
}

Shop* Market::AssignShop(int key)
{
	if (mShopMap[key] == nullptr)
		mShopMap[key] = new Shop(key, mPlayer);

	return mShopMap[key];
}

bool Market::LeaveMarket()
{
	if (exitMarket)
	{
		exitMarket = false; 
		return true;
	}
	else 
		return false;
}