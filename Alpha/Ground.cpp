#include "Ground.h"

#include <ctime>
#include "Player.h"
#include "Inventory.h"
#include "Prayer.h"

Ground::Ground(Player *player) : gen((unsigned)time(NULL)), roll(0, 99)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();

	mDefinitionLoader = DefinitionLoader::Instance();

	for (int i = 0; i < 15; i++)
		mGround[i] = nullptr;

	int x = 0, y = -64;
	for (int i = 0; i < 15; i++)
	{
		if (!(i % 5))
		{
			x = 0;
			y += 64;
		}

		mGroundPos[i] = Vector2(60 + x, 424 + y);
		x += 74;
	}
}

Ground::~Ground()
{
	mPlayer = nullptr;

	mInputManager = nullptr;

	mDefinitionLoader = nullptr;

	for (int i = 0; i < 15; i++)
	{
		if (mGround[i] != nullptr)
		{
			delete mGround[i];
			mGround[i] = nullptr;
		}
	}

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Ground::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		for (int i = 0; i < 15; i++)
		{
			if (mGround[i] != nullptr)
			{
				if (mGround[i]->Intersects(mInputManager->MousePos()))
				{
					if (mInputManager->KeyDown(SDL_SCANCODE_LSHIFT))
					{
						delete mGround[i];
						mGround[i] = nullptr;
					}
					else
						PickUp(i);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			if (mInputManager->MousePos().Between(Vector2(mGroundPos[i].x - 32.0f, mGroundPos[i].y - 32.0f), 64.0f, 64.0f))
			{
				if (mGround[i] != nullptr && mItemText == nullptr)
				{
					mItemText = new Texture(mGround[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = mGroundPos[i];
					mItemText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mItemText != nullptr) || mInputManager->MouseButtonPressed(InputManager::left))
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Ground::Render()
{
	for (int i = 0; i < 15; i++)
	{
		if (mGround[i] != nullptr)
			mGround[i]->Render();
	}

	if (mItemText != nullptr)
		mItemText->Render();
}

void Ground::AddLoot(int id)
{
	std::vector<Item> loot = GetDrop(id);

	for (int i = 0; i < loot.size(); i++)
	{
		if (mPlayer->prayer->boneCrusher(&loot[i]))
			loot.erase(loot.begin() + i);
	}

	AddLoot(loot);
}

bool Ground::CanAdd(Item item)
{
	for (int i = 0; i < 15; i++)
	{
		if (mGround[i] == nullptr)
			return true;
		else if (mGround[i]->getItemDefinition()->isStackable() && mGround[i]->getId() == item.getId())
			return true;
	}
	return false;
}

void Ground::AddItem(Item item)
{
	if (CanAdd(item))
	{
		for (int i = 0; i < 15; i++)
		{
			if (mGround[i] != nullptr)
			{
				if (mGround[i]->getId() == item.getId())
				{
					if (mGround[i]->getItemDefinition()->isStackable())
					{
						mGround[i]->add(item.getAmount());
						return;
					}
				}
			}
		}
		for (int i = 0; i < 15; i++)
		{
			if (mGround[i] == nullptr)
			{
				mGround[i] = new Item(item.getId(), item.getAmount());
				mGround[i]->Pos(mGroundPos[i]);
				return;
			}
		}
	}
}

void Ground::AddLoot(std::vector<Item> loot)
{
	for (int i = 0; i < loot.size(); i++)
		AddItem(loot[i]);
}

void Ground::PickUp(int slot)
{
	if (mGround[slot] != nullptr)
	{
		if (mPlayer->inventory->canAdd(*mGround[slot]))
		{
			mPlayer->inventory->add(*mGround[slot]);
			delete mGround[slot];
			mGround[slot] = nullptr;
		}
	}
}

std::vector<Item> Ground::GetDrop(int id)
{
	std::vector<Item> drop, temp;
	int dropRoll = roll(gen);

	for (int i = 0; i < mDefinitionLoader->GetLootDefinition(id)->getLootTable().size(); i++)
	{
		if (mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getChance() == 100)
		{
			drop.push_back(Item(mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getIndex(),
				rand() % (mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMax() - mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMin() + 1)
				+ mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMin()));
		}
		else if (mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getChance() > dropRoll)
		{
			temp.push_back(Item(mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getIndex(), 
				rand() % (mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMax() - mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMin() + 1)
				+ mDefinitionLoader->GetLootDefinition(id)->getLootTable()[i].getMin()));
		}
	}

	if (temp.size())
		drop.push_back(temp[rand() % temp.size()]);

	for (int i = 0; i < drop.size(); i++)
	{
		if (!drop[i].getItemDefinition()->isStackable() && drop[i].getAmount() > 1)
		{
			while (drop[i].getAmount() > 1)
			{
				drop.push_back(Item(drop[i].getId(), 1));
				drop[i].remove();
			}
		}
	}

	return drop;
}