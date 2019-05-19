#include "Shop.h"


Shop::Shop(int id, Player *player)
{	
	mPlayer = player;

	mInputManager = InputManager::Instance();
	mDefinitionLoader = DefinitionLoader::Instance();

	name = mDefinitionLoader->GetShopDefinition(id)->getName();

	int x = 0, y = 0;
	for (int i = 0; i < mDefinitionLoader->GetShopDefinition(id)->getStock().size(); i++)
	{
		stock.push_back(Item(mDefinitionLoader->GetShopDefinition(id)->getStock()[i].first, mDefinitionLoader->GetShopDefinition(id)->getStock()[i].second));
		stock[i].Pos(Vector2(48 + x, 128 + y));

		if (!((i + 1) % 5))
		{
			x = 0;
			y += 64;
		}
		else
			x += 80;
	}

	mSelectedSlot = -1;

	mNameText = new Texture(name, "alagard.ttf", 42, { 25, 25, 25 });
	mNameText->Pos(Vector2(232, 35));

	mRightClick[0] = new Texture("  1    ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[1] = new Texture("  10   ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[2] = new Texture("  25   ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[3] = new Texture("  100  ", "Romulus.ttf", 16, { 255, 255, 255 });

	mAltBackground = new Texture("AltBackground.png");
	mAltBackground->Scale(Vector2(3.0f, 4.0f));

	mItemText = nullptr;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	exitShop = false;

	inventory = false;
}


Shop::~Shop()
{
	mPlayer = nullptr;

	mInputManager = nullptr;
	mDefinitionLoader = nullptr;

	delete mNameText;
	mNameText = nullptr;
	
	delete mEscapeButton;
	mEscapeButton = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete mRightClick[i];
		mRightClick[i] = nullptr;
	}

	delete mAltBackground;
	mAltBackground = nullptr;

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Shop::Update()
{
	mPlayer->setInShop(true);

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
			exitShop = true;
		else if (mRightClicked)
		{
			for (int i = 0; i < 4; i++)
			{
				if (mRightClick[i]->Intersects(mInputManager->MousePos()))
				{
					switch (i)
					{
					case 0:
						if (inventory)
							sell(1);
						else
							buy(1);
						break;
					case 1:
						if (inventory)
							sell(10);
						else
							buy(10);
						break;
					case 2:
						if (inventory)
							sell(25);
						else
							buy(25);
						break;
					case 3:
						if (inventory)
							sell(100);
						else
							buy(100);
						break;
					}
					break;
				}
			}

			mSelectedSlot = -1;
			mRightClicked = inventory = false;
		}
		else
		{
			for (int i = 0; i < stock.size(); i++)
			{
				if (stock[i].Intersects(mInputManager->MousePos()))
				{
					mSelectedSlot = i;
					inventory = false;
					SetPrice();
				}
			}

			for (int i = 0; i < 20; i++)
			{
				if (mPlayer->inventory->getSlot(i) != nullptr)
				{
					if (mPlayer->inventory->getSlot(i)->Intersects(mInputManager->MousePos()))
					{
						mSelectedSlot = i;
						inventory = true;
						SetPrice();
					}
				}
			}
		}
	}
	else if (mInputManager->MouseButtonPressed(InputManager::right))
	{
		for (int i = 0; i < stock.size(); i++)
		{
			if (stock[i].Intersects(mInputManager->MousePos()))
			{
				mSelectedSlot = i;
				mRightClicked = true;
				inventory = false;

				for (int i = 0; i < 4; i++)
					mRightClick[i]->Pos(Vector2(stock[mSelectedSlot].Pos().x + 24, ((stock[mSelectedSlot].Pos().y - 16) + 12 * i)));

				mAltBackground->Pos(Vector2(stock[mSelectedSlot].Pos().x + 24, ((stock[mSelectedSlot].Pos().y - 16) + 12 * 1.5)));
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (mPlayer->inventory->getSlot(i) != nullptr)
			{
				if (mPlayer->inventory->getSlot(i)->Intersects(mInputManager->MousePos()))
				{
					mSelectedSlot = i;
					mRightClicked = inventory = true;

					for (int i = 0; i < 4; i++)
						mRightClick[i]->Pos(Vector2(mPlayer->inventory->getSlot(mSelectedSlot)->Pos().x + 24, ((mPlayer->inventory->getSlot(mSelectedSlot)->Pos().y - 16) + 12 * i)));

					mAltBackground->Pos(Vector2(mPlayer->inventory->getSlot(mSelectedSlot)->Pos().x + 24, ((mPlayer->inventory->getSlot(mSelectedSlot)->Pos().y - 16) + 12 * 1.5)));
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < stock.size(); i++)
		{
			if (stock[i].Intersects(mInputManager->MousePos()))
			{
				if (mItemText == nullptr)
				{
					mItemText = new Texture(stock[i].getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = stock[i].Pos();
					mItemText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mItemText != nullptr) || 
		mInputManager->MouseButtonPressed(InputManager::left) || mInputManager->MouseButtonPressed(InputManager::right))
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Shop::Render()
{
	mNameText->Render();
	mEscapeButton->Render();

	if (stock.size())
	{
		for (int i = 0; i < stock.size(); i++)
		{
			stock[i].Render();
		}
	}

	if (mItemText != nullptr)
		mItemText->Render();

	if (mRightClicked)
	{
		mAltBackground->Render();

		for (int i = 0; i < 4; i++)
			mRightClick[i]->Render();
	}

	if (mPrice.size())
	{
		for (int i = 0; i < mPrice.size(); i++)
			mPrice[i]->Render();
	}
}

void Shop::SetPrice()
{
	if (mPrice.size())
	{
		for (int i = 0; i < mPrice.size(); i++)
		{
			delete mPrice[i];
			mPrice[i] = nullptr;
		}
		mPrice.clear();
	}

	std::string str = "";

	if (inventory)
		str = mPlayer->inventory->getSlot(mSelectedSlot)->getName() + ": " + std::to_string((int)(mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getAlchemyPrice() * 0.66)) + "g";
	else
		str = stock[mSelectedSlot].getName() + ": " + std::to_string(stock[mSelectedSlot].getItemDefinition()->getGeneralPrice()) + "g";

	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mPrice.push_back(new Texture(str.substr(i, 1), "Romulus.ttf", 16, { 255, 255, 255 }));
		mPrice[i]->Pos(Vector2(232 + (8 * str.length() / 2) - 8.0f * (lastIndex - i), 70));
	}
}

bool Shop::canAdd(Item _item)
{
	if (stock.size() < 15)
		return true;
	else
	{
		for (int i = 0; i < stock.size(); i++)
		{
			if (stock[i].getId() == _item.getId())
				return true;
		}
		return false;
	}
}

void Shop::add(Item *_item, int amount)
{
	if (canAdd(*_item))
	{
		for (int i = 0; i < stock.size(); i++)
		{
			if (stock[i].getId() == _item->getId())
			{
				stock[i].add(amount);
				return;
			}
		}
	}
	stock.push_back(Item(_item->getId(), amount));

	int x = 0, y = 0;
	for (int i = 0; i < stock.size(); i++)
	{
		stock[i].Pos(Vector2(48 + x, 128 + y));

		if (!((i + 1) % 5))
		{
			x = 0;
			y += 64;
		}
		else
			x += 80;
	}
}

void Shop::buy(int amount)
{
	if (mSelectedSlot <= stock.size() && mSelectedSlot > -1)
	{
		if (!stock[mSelectedSlot].getItemDefinition()->isStackable())
			if (amount > mPlayer->inventory->getFreeSlots())
				amount = mPlayer->inventory->getFreeSlots();

		if (mPlayer->inventory->canAdd(stock[mSelectedSlot]))
		{
			if (amount > 0)
			{
				if (amount > stock[mSelectedSlot].getAmount())
					amount = stock[mSelectedSlot].getAmount();

				if (stock[mSelectedSlot].getItemDefinition()->getGeneralPrice())
					if (amount > mPlayer->inventory->hasAmount(516) / (stock[mSelectedSlot].getItemDefinition()->getGeneralPrice()))
						amount = mPlayer->inventory->hasAmount(516) / (stock[mSelectedSlot].getItemDefinition()->getGeneralPrice());

				if (amount)
				{
					if (mPlayer->inventory->hasItem(516, (stock[mSelectedSlot].getItemDefinition()->getGeneralPrice()) * amount))
					{
						int price = stock[mSelectedSlot].getItemDefinition()->getGeneralPrice() * amount;
						if (!price) price = stock[mSelectedSlot].getItemDefinition()->getAlchemyPrice() * amount;

						mPlayer->inventory->removeItem(516, price);

						if (stock[mSelectedSlot].getItemDefinition()->isStackable())
							mPlayer->inventory->add(Item(stock[mSelectedSlot].getId(), amount));
						else
						{
							for (int i = 0; i < amount; i++)
								mPlayer->inventory->add(Item(stock[mSelectedSlot].getId(), 1));
						}

						stock[mSelectedSlot].remove(amount);
						if (stock[mSelectedSlot].getAmount() < 1)
						{
							stock.erase(stock.begin() + mSelectedSlot);

							int x = 0, y = 0;
							for (int i = 0; i < stock.size(); i++)
							{
								stock[i].Pos(Vector2(48 + x, 128 + y));

								if (!((i + 1) % 5))
								{
									x = 0;
									y += 64;
								}
								else
									x += 80;
							}
						}
					}
				}
			}
		}
	}
}

void Shop::sell(int amount)
{
	if (mSelectedSlot < 0 || mSelectedSlot > 19)
		return;

	if (mPlayer->inventory->getSlot(mSelectedSlot) != nullptr)
	{
		if (mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getId() != 516)
		{
			if ((mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->isStackable() && mPlayer->inventory->getSlot(mSelectedSlot)->getAmount() > 1) 
				|| (mPlayer->inventory->hasAmount(mPlayer->inventory->getSlot(mSelectedSlot)->getId()) > 1))
			{
				if (amount > mPlayer->inventory->hasAmount(mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getId()))
					amount = mPlayer->inventory->hasAmount(mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getId());
			}
			else
				amount = 1;

			if (amount > 0)
			{
				int price = mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getAlchemyPrice() * 0.66;

				if (mPlayer->inventory->canAdd(Item(516, price * amount)))
				{
					add(mPlayer->inventory->getSlot(mSelectedSlot), amount);
					if (price)
						mPlayer->inventory->add(Item(516, price * amount));
					mPlayer->inventory->removeItem(mPlayer->inventory->getSlot(mSelectedSlot)->getItemDefinition()->getId(), amount);
				}
			}
		}
	}
}