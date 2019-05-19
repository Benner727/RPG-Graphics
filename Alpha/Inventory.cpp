#include "Inventory.h"

#include "Player.h"
#include "Equipment.h"
#include "Skills.h"
#include "Prayer.h"
#include "Bank.h"
#include "Fletching.h"
#include "Crafting.h"
#include "Herblore.h"

#include <fstream>
#include <sstream>

Inventory::Inventory(Player *p)
{
	player = p;

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mTabText = new Texture("Inventory", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	int y = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!(i % 4))
			y += 64;

		mInventoryPos[i] = Vector2(509 + 64 * (i % 4), 251 + y);
		mInventory[i] = nullptr;
	}

	mSelectedSlot = -1;
	mItemText = nullptr;

	mSelectedItem = new Texture("SelectOutline.png");
	mSelectedItem->Scale(Vector2(3.0f, 3.0f));
	mPrevSelected = -1;

	mRightClick[0] = new Texture("  10   ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[1] = new Texture("  100  ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[2] = new Texture("  1000 ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[3] = new Texture("  All  ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[4] = new Texture("Use", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[5] = new Texture("Select", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[6] = new Texture("Drop", "Romulus.ttf", 16, { 255, 255, 255 });

	mAltBackground = new Texture("AltBackground.png");

	bool mRightClicked = false;

	//Starting Items
	add(Item(268, 1)); //Bronze dagger
	add(Item(282, 1)); //Bronze sq shield
	add(Item(44, 1)); //Shortbow
	add(Item(65, 25)); //Bronze arrows
	add(Item(539, 30)); //Air runes
	add(Item(540, 30)); //Mind runes
	add(Item(212, 1)); //Cooked Chicken
	add(Item(12, 1)); //Bronze hatchet
	add(Item(195, 1)); //Small net
	add(Item(236, 1)); //Bronze pickaxe
	add(Item(519, 1)); //Air talisman
}

Inventory::~Inventory()
{
	player = nullptr;

	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	clear();

	for (int i = 0; i < 7; i++)
	{
		delete mRightClick[i];
		mRightClick[i] = nullptr;
	}

	delete mAltBackground;

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Inventory::Update()
{
	static Vector2 prevPos;

	static unsigned int mStartTicks = 0;
	static unsigned int mElapsedTicks = 0;

	if (!player->getInShop())
	{
		player->fletching->Update();
		player->crafting->Update();

		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			if (mRightClicked)
			{
				if (mInventory[mSelectedSlot] != nullptr)
				{
					if (player->getInBank())
					{
						for (int i = 0; i < 4; i++)
						{
							if (mRightClick[i]->Intersects(mInputManager->MousePos()))
							{
								switch (i)
								{
								case 0:
									player->bank->deposit(mSelectedSlot, 10);
									break;
								case 1:
									player->bank->deposit(mSelectedSlot, 100);
									break;
								case 2:
									player->bank->deposit(mSelectedSlot, 1000);
									break;
								case 3:
									player->bank->deposit(mSelectedSlot, hasAmount(mInventory[mSelectedSlot]->getId()));
									break;
								}
								break;
							}
						}
						mSelectedSlot = mPrevSelected = -1;
						mRightClicked = false;
					}
					else
					{
						for (int i = 4; i < 7; i++)
						{
							if (mRightClick[i]->Intersects(mInputManager->MousePos()))
							{
								switch (i)
								{
								case 4:
									use();
									break;
								case 5:
									if (mPrevSelected != -1)
									{
										player->fletching->fletch(mPrevSelected, mSelectedSlot);
										player->crafting->craft(mPrevSelected, mSelectedSlot);
										player->herblore->brew(mPrevSelected, mSelectedSlot);
										player->herblore->decant(mPrevSelected, mSelectedSlot);
										mPrevSelected = mSelectedSlot = -1;
									}
									else if (mSelectedSlot != -1)
									{
										mSelectedItem->Pos(mInventory[mSelectedSlot]->Pos());
										mPrevSelected = mSelectedSlot;
										mSelectedSlot = -1;
									}
									break;
								case 6:
									remove(mSelectedSlot);
									mAudioManager->PlaySFX("drop.wav", 0, 1);
									mPrevSelected = mSelectedSlot = -1;
									break;
								}
								break;
							}
							else if (i == 6)
							{
								mStartTicks = SDL_GetTicks();
								mPrevSelected = mSelectedSlot = -1;
							}
						}
						mRightClicked = false;
					}
				}
			}
			else
			{
				for (int i = 0; i < 20; i++)
				{
					if (mInventory[i] != nullptr)
					{
						if (mInventory[i]->Intersects(mInputManager->MousePos()))
						{
							mStartTicks = SDL_GetTicks();
							mSelectedSlot = i;
							prevPos = mInventory[mSelectedSlot]->Pos();
						}
					}
				}

				if (mSelectedSlot == -1)
					mPrevSelected = -1;
			}
		}
		else if (mInputManager->MouseButtonDown(InputManager::left))
		{
			if (!mRightClicked)
			{
				mElapsedTicks = SDL_GetTicks() - mStartTicks;

				if (mElapsedTicks > 100 && mSelectedSlot != -1)
					mInventory[mSelectedSlot]->Pos(mInputManager->MousePos());
			}
		}
		else if (mInputManager->MouseButtonPressed(InputManager::right))
		{
			if (player->getInBank())
			{
				for (int i = 0; i < 20; i++)
				{
					if (mInventory[i] != nullptr)
					{
						if (mInventory[i]->Intersects(mInputManager->MousePos()))
						{
							mSelectedSlot = i;
							mRightClicked = true;

							for (int i = 0; i < 4; i++)
								mRightClick[i]->Pos(Vector2(mInventory[mSelectedSlot]->Pos().x + 24, ((mInventory[mSelectedSlot]->Pos().y - 16) + 12 * i)));

							mAltBackground->Pos(Vector2(mInventory[mSelectedSlot]->Pos().x + 24, ((mInventory[mSelectedSlot]->Pos().y - 16) + 12 * 1.5)));
							mAltBackground->Scale(Vector2(3.0f, 4.0f));
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 20; i++)
				{
					if (mInventory[i] != nullptr)
					{
						if (mInventory[i]->Intersects(mInputManager->MousePos()))
						{
							mSelectedSlot = i;
							mRightClicked = true;

							for (int i = 4; i < 7; i++)
								mRightClick[i]->Pos(Vector2(mInventory[mSelectedSlot]->Pos().x + 24, ((mInventory[mSelectedSlot]->Pos().y - 16) + 12 * (i - 4))));

							mAltBackground->Pos(Vector2(mInventory[mSelectedSlot]->Pos().x + 24, ((mInventory[mSelectedSlot]->Pos().y - 16) + 12)));
							mAltBackground->Scale(Vector2(3.25f, 3.0f));
						}
					}
				}
			}
		}
		else if (mInputManager->MouseButtonReleased(InputManager::left))
		{
			if (mSelectedSlot != -1)
			{
				if (mElapsedTicks <= 100)
				{
					//Use items
					use();
				}
				else
				{
					for (int i = 0; i < 20; i++)
					{
						if (mInventory[mSelectedSlot]->Pos().Between(Vector2(mInventoryPos[i].x - 32.0f, mInventoryPos[i].y - 32.0f), 64.0f, 64.0f))
						{
							swap(i);
							return;
						}
					}
					mInventory[mSelectedSlot]->Pos(prevPos);
				}
				mSelectedSlot = -1;
			}
		}
	}

	for (int i = 0; i < 20; i++)
	{
		if (mInputManager->MousePos().Between(Vector2(mInventoryPos[i].x - 32.0f, mInventoryPos[i].y - 32.0f), 64.0f, 64.0f) && !mRightClicked)
		{
			if (mInventory[i] != nullptr && mItemText == nullptr)
			{
				mItemText = new Texture(mInventory[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
				mTextPos = mInventoryPos[i];
				mItemText->Pos(mTextPos);
			}
		}
	}
	
	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mItemText != nullptr) || mInputManager->MouseButtonDown(InputManager::left) || mRightClicked)
	{
			delete mItemText;
			mItemText = nullptr;
	}
}

void Inventory::Render()
{
	mTabText->Render();

	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
			mInventory[i]->Render();
	}

	if (mPrevSelected != -1)
		mSelectedItem->Render();

	if (mRightClicked)
	{
		mAltBackground->Render();

		if (player->getInBank())
		{
			for (int i = 0; i < 4; i++)
				mRightClick[i]->Render();
		}
		else
		{
			for (int i = 4; i < 7; i++)
				mRightClick[i]->Render();
		}
	}

	if (mItemText != nullptr)
		mItemText->Render();

	player->fletching->Render();
	player->crafting->Render();
}

void Inventory::use()
{
	if (mPrevSelected != -1)
	{
		player->fletching->fletch(mPrevSelected, mSelectedSlot);
		player->crafting->craft(mPrevSelected, mSelectedSlot);
		player->herblore->brew(mPrevSelected, mSelectedSlot);
		player->herblore->decant(mPrevSelected, mSelectedSlot);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_LSHIFT))
	{
		remove(mSelectedSlot);
		mAudioManager->PlaySFX("drop.wav", 0, 1);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (player->getInBank())
	{
		player->bank->deposit(mSelectedSlot, 1);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (mInventory[mSelectedSlot]->getEquipmentDefinition() != nullptr)
	{
		player->equipment->equip(mSelectedSlot);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (mInventory[mSelectedSlot]->getFoodDefinition() != nullptr)
	{
		eat(mSelectedSlot);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (mInventory[mSelectedSlot]->getPotionDefinition() != nullptr)
	{
		drink(mSelectedSlot);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (player->prayer->isBone(mSelectedSlot))
	{
		player->prayer->buryBone(mSelectedSlot);
		mPrevSelected = mSelectedSlot = -1;
	}
	else if (mSelectedSlot != -1)
	{
		mSelectedItem->Pos(mInventory[mSelectedSlot]->Pos());
		mPrevSelected = mSelectedSlot;
		mSelectedSlot = -1;
	}
}

bool Inventory::canAdd(Item item)
{
	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] == nullptr)
			return true;
		else if (mInventory[i]->getItemDefinition()->isStackable() && mInventory[i]->getId() == item.getId())
			return true;
	}
	return false;
}

void Inventory::add(Item item)
{
	if (canAdd(item))
	{
		for (int i = 0; i < 20; i++)
		{
			if (mInventory[i] != nullptr)
			{
				if (mInventory[i]->getId() == item.getId())
				{
					if (mInventory[i]->getItemDefinition()->isStackable())
					{
						mInventory[i]->add(item.getAmount());
						return;
					}
				}
			}
		}
		for (int i = 0; i < 20; i++)
		{
			if (mInventory[i] == nullptr)
			{
				mInventory[i] = new Item(item.getId(), item.getAmount());
				mInventory[i]->Pos(mInventoryPos[i]);
				return;
			}
		}
	}
}

void Inventory::remove(int slot)
{
	if (mInventory[slot] != nullptr)
	{
		delete mInventory[slot];
		mInventory[slot] = nullptr;
	}
}

void Inventory::remove(int slot, int amount)
{
	mInventory[slot]->remove(amount);

	if (mInventory[slot]->getAmount() < 1)
	{
		delete mInventory[slot];
		mInventory[slot] = nullptr;
	}
}

void Inventory::remove(std::vector<Item> items)
{
	for (int i = 0; i < items.size(); i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (mInventory[j] != nullptr)
			{
				if (mInventory[j]->getId() == items[i].getId())
				{
					remove(j, items[i].getAmount());
				}
			}
		}
	}
}

void Inventory::eat(int slot)
{
	player->skills->heal(mInventory[slot]->getFoodDefinition()->getHeal());
	remove(slot);
	player->eatDelay();
	mAudioManager->PlaySFX("eat.wav", 0, 1);
}

void Inventory::drink(int slot)
{
	for (int i = 0; i < mInventory[slot]->getPotionDefinition()->getSkillData().size(); i++)
	{
		player->skills->boostSkill(mInventory[slot]->getPotionDefinition()->getSkillData()[i].add,
			mInventory[slot]->getPotionDefinition()->getSkillData()[i].modifier,
			mInventory[slot]->getPotionDefinition()->getSkillData()[i].skillId,
			mInventory[slot]->getPotionDefinition()->getType());
	}
	
	if (mInventory[slot]->getPotionDefinition()->getReplaceId() != -1)
	{
		player->inventory->replace(Item(mInventory[slot]->getPotionDefinition()->getReplaceId(), 1), slot);
	}
	else
		player->inventory->remove(slot);

	player->drinkDelay();
	mAudioManager->PlaySFX("drink.wav", 0, 1);
}

void Inventory::replace(Item item, int slot)
{
	remove(slot);
	mInventory[slot] = new Item(item.getId(), item.getAmount());
	mInventory[slot]->Pos(mInventoryPos[slot]);
}

void Inventory::clear()
{
	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
		{
			delete mInventory[i];
			mInventory[i] = nullptr;
		}
	}
}

Item* Inventory::getSlot(int slot)
{
	if (slot >= 0 && slot < 20)
		if (mInventory[slot] != nullptr)
			return mInventory[slot];

	return nullptr;
}

int Inventory::getFreeSlots()
{
	int total = 0;
	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] == nullptr)
			total++;
	}
	return total;
}

bool Inventory::hasItem(int id)
{
	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
		{
			if (mInventory[i]->getId() == id)
				return true;
		}
	}
	return false;
}

bool Inventory::hasItem(int id, int amount)
{
	int total = 0;

	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
		{
			if (mInventory[i]->getId() == id)
				total += mInventory[i]->getAmount();
		}
	}

	return total >= amount;
}

bool Inventory::hasItems(std::vector<Item> items)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (!(hasItem(items[i].getId(), items[i].getAmount())))
			return false;
	}
	return true;
}

int Inventory::hasAmount(int id)
{
	int total = 0;

	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
		{
			if (mInventory[i]->getId() == id)
				total += mInventory[i]->getAmount();
		}
	}

	return total;
}

void Inventory::removeItem(int id)
{
	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
		{
			if (mInventory[i]->getId() == id)
			{
				remove(i);
				return;
			}
		}
	}
}

void Inventory::removeItem(int id, int amount)
{
	int i = 0;

	do
	{
	
		if (mInventory[i] != nullptr)
		{
			if (mInventory[i]->getId() == id)
			{
				if (mInventory[i]->getAmount() >= amount)
				{
					remove(i, amount);
					amount = 0;
				}
				else
				{
					amount -= mInventory[i]->getAmount();
					remove(i);
				}
			}
		}

		if (i == 19)
			return;
		else if (amount < 0)
			amount = 0;
		
		i++;
	} while (amount);
}

void Inventory::swap(int i)
{
	if (mInventory[i] != nullptr)
	{
		Item *temp = mInventory[i];
		mInventory[i] = mInventory[mSelectedSlot];
		mInventory[mSelectedSlot] = temp;
		mInventory[mSelectedSlot]->Pos(mInventoryPos[mSelectedSlot]);
	}
	else
	{
		mInventory[i] = mInventory[mSelectedSlot];
		mInventory[mSelectedSlot] = nullptr;
	}

	mInventory[i]->Pos(mInventoryPos[i]);
	mSelectedSlot = -1;
}

void Inventory::save()
{
	std::ofstream outFile("save.txt", std::ios::app);

	outFile << "Inventory" << std::endl;

	for (int i = 0; i < 20; i++)
	{
		if (mInventory[i] != nullptr)
			outFile << i << " " << *mInventory[i];
	}

	outFile << std::endl;

	outFile.close();
}

void Inventory::load()
{
	clear();

	std::ifstream infile("save.txt");

	int i;
	Item temp;
	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (line == "Inventory")
		{
			while (infile >> i >> temp)
			{
				mInventory[i] = new Item(temp.getId(), temp.getAmount());
				mInventory[i]->Pos(mInventoryPos[i]);
			}
		}
	}

	infile.close();
}