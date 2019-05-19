#include "Equipment.h"

#include "Player.h"
#include "Inventory.h"
#include "Skills.h"

#include <fstream>
#include <sstream>

Equipment::Equipment(Player *p)
{
	player = p;

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mTabText = new Texture("Equipment", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	mBackground = new Texture("EquipmentBackground.png");
	mBackground->Pos(Vector2(610, 424));

	mEquipmentPos[0] = Vector2(608, 297); mEquipmentPos[1] = Vector2(543, 360);
	mEquipmentPos[2] = Vector2(608, 360); mEquipmentPos[3] = Vector2(543, 425);
	mEquipmentPos[4] = Vector2(608, 425); mEquipmentPos[5] = Vector2(673, 425);
	mEquipmentPos[6] = Vector2(608, 488); mEquipmentPos[7] = Vector2(543, 548);
	mEquipmentPos[8] = Vector2(608, 543); mEquipmentPos[9] = Vector2(673, 548);
	mEquipmentPos[10] = Vector2(673, 360);

	for (int i = 0; i < 11; i++)
		mEquipment[i] = nullptr;
	for (int i = 0; i < 8; i++)
		mBonus[i] = 0;

	mItemText = nullptr;
}


Equipment::~Equipment()
{
	player = nullptr;

	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	delete mBackground;
	mBackground = nullptr;

	clear();

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Equipment::Update()
{
	if (mInputManager->MouseButtonReleased(InputManager::left))
	{
		for (int i = 0; i < 11; i++)
		{
			if (mEquipment[i] != nullptr)
			{
				if (mEquipment[i]->Intersects(mInputManager->MousePos()))
				{
					unequip(i);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 11; i++)
		{
			if (mInputManager->MousePos().Between(Vector2(mEquipmentPos[i].x - 32.0f, mEquipmentPos[i].y - 32.0f), 64.0f, 64.0f))
			{
				if (mEquipment[i] != nullptr && mItemText == nullptr)
				{
					mItemText = new Texture(mEquipment[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = mEquipmentPos[i];
					mItemText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mItemText != nullptr))
	{
		delete mItemText;
		mItemText = nullptr;
	}
}

void Equipment::Render()
{
	mTabText->Render();
	mBackground->Render();

	for (int i = 0; i < 11; i++)
	{
		if (mEquipment[i] != nullptr)
			mEquipment[i]->Render();
	}

	if (mItemText != nullptr)
		mItemText->Render();
}

void Equipment::calculateBonus()
{
	for (int i = 0; i < 8; i++)
		mBonus[i] = 0;

	for (int i = 0; i < 10; i++)
	{
		if (mEquipment[i] != nullptr)
		{
			mBonus[0] += mEquipment[i]->getItemBonusDefinition()->getMeleeAtt();
			mBonus[1] += mEquipment[i]->getItemBonusDefinition()->getRangeAtt();
			mBonus[2] += mEquipment[i]->getItemBonusDefinition()->getMagicAtt();
			mBonus[3] += mEquipment[i]->getItemBonusDefinition()->getMeleeDef();
			mBonus[4] += mEquipment[i]->getItemBonusDefinition()->getRangeDef();
			mBonus[5] += mEquipment[i]->getItemBonusDefinition()->getMagicDef();
			mBonus[6] += mEquipment[i]->getItemBonusDefinition()->getStrength();
			mBonus[7] += mEquipment[i]->getItemBonusDefinition()->getPrayer();
		}
	}
}

void Equipment::unequip(int slot)
{
	if (slot < 0 || slot > 10)
		return;
	else if (mEquipment[slot] == nullptr)
		return;
	else if (player->inventory->getFreeSlots())
	{
		player->inventory->add(*mEquipment[slot]);
		delete mEquipment[slot];
		mEquipment[slot] = nullptr;
		calculateBonus();
	}

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}

	mAudioManager->PlaySFX("equip.wav", 0, 1);

	player->setCombatStance(player->getCombatStance());
}

bool Equipment::hasAmmo()
{
	if (mEquipment[3] != nullptr)
	{
		if (mEquipment[3]->getRangedDefinition()->getType())
			return true;
		else if (mEquipment[10] != nullptr)
		{
			for (int i = 0; i < mEquipment[3]->getRangedDefinition()->getAmmo().size(); i++)
				if (mEquipment[10]->getId() == mEquipment[3]->getRangedDefinition()->getAmmo()[i])
					return true;
		}
		return false;
	}
	else
		return false;
}

void Equipment::useAmmo()
{
	if (hasAmmo())
	{
		bool keep = (rand() % 3);

		if (mEquipment[3]->getRangedDefinition()->getType())
		{
			if (keep)
			{
				if (mEquipment[9] != nullptr)
				{
					if (mEquipment[9]->getId() == 777 || mEquipment[9]->getId() == 779) //Ava's
						return;
				}
				player->inventory->add(Item(mEquipment[3]->getId(), 1));
				mEquipment[3]->remove();
				if (!mEquipment[3]->getAmount()) mEquipment[3] = nullptr;
			}
			else
			{
				mEquipment[3]->remove();
				if (!mEquipment[3]->getAmount()) mEquipment[3] = nullptr;
			}
		}
		else
		{
			if (mEquipment[10]->getId() == 1064) //Bolt racks
			{
				mEquipment[10]->remove();
				if (!mEquipment[10]->getAmount()) mEquipment[3] = nullptr;
				return;
			}

			if (keep)
			{
				if (mEquipment[9] != nullptr)
				{
					if (mEquipment[9]->getId() == 777 || mEquipment[9]->getId() == 779) //Ava's
						return;
				}
				player->inventory->add(Item(mEquipment[10]->getId(), 1));
				mEquipment[10]->remove();
				if (!mEquipment[10]->getAmount()) mEquipment[10] = nullptr;
			}
			else
			{
				mEquipment[10]->remove();
				if (!mEquipment[10]->getAmount()) mEquipment[10] = nullptr;
			}
		}
	}
}

bool Equipment::canEquip(Item *item)
{
	if (item != nullptr)
		if (item->getEquipmentDefinition() == nullptr)
			return false;
		else if (item->getEquipmentDefinition()->getSlot() < 0 && item->getEquipmentDefinition()->getSlot() > 10)
			return false;

	for (int i = 0; i < item->getEquipmentDefinition()->getReq().size(); i++)
		if (player->skills->getLevel(item->getEquipmentDefinition()->getReq()[i].skillId) < item->getEquipmentDefinition()->getReq()[i].skillReq)
			return false;

	if (item->getEquipmentDefinition()->getSlot() == 3)
		if (item->getWeaponDefinition()->is2h())
			if (mEquipment[5] != nullptr && mEquipment[3] != nullptr)
				if (player->inventory->getFreeSlots() < 1)
					return false;

	return true;
}

void Equipment::equip(int slot)
{
	if (player->inventory->getSlot(slot) == nullptr)
		return;

	Item _item = *player->inventory->getSlot(slot);

	if (!canEquip(&_item))
		return;

	player->inventory->remove(slot);
	mAudioManager->PlaySFX("equip.wav", 0, 1);

	if (mEquipment[_item.getEquipmentDefinition()->getSlot()] != nullptr)
	{
		if (_item.getEquipmentDefinition()->getSlot() == 10)
		{
			if (mEquipment[10]->getId() == _item.getId())
			{
				mEquipment[10]->add(_item.getAmount());
				return;
			}
		}

		if (_item.getEquipmentDefinition()->getSlot() == 3)
		{
			if (_item.getRangedDefinition() != nullptr)
			{
				if (_item.getRangedDefinition()->getType())
				{
					if (mEquipment[3]->getId() == _item.getId())
					{
						mEquipment[3]->add(_item.getAmount());
						return;
					}
				}
			}
		}

		player->inventory->add(*mEquipment[_item.getEquipmentDefinition()->getSlot()]);
	}

	mEquipment[_item.getEquipmentDefinition()->getSlot()] = new Item(_item.getId(), _item.getAmount());
	mEquipment[_item.getEquipmentDefinition()->getSlot()]->Pos(mEquipmentPos[_item.getEquipmentDefinition()->getSlot()]);

	if (_item.getEquipmentDefinition()->getSlot() == 3)
	{
		player->setCombatStance(player->getCombatStance());
		if (_item.getWeaponDefinition()->is2h() && mEquipment[5] != nullptr)
			unequip(5);
	}
	else if (_item.getEquipmentDefinition()->getSlot() == 5 && mEquipment[3] != nullptr)
	{
		if (mEquipment[3]->getWeaponDefinition()->is2h())
			unequip(3);
	}

	calculateBonus();	
}

void Equipment::clear()
{
	for (int i = 0; i < 11; i++)
	{
		if (mEquipment[i] != nullptr)
		{
			delete mEquipment[i];
			mEquipment[i] = nullptr;
		}
	}
	calculateBonus();
}

void Equipment::clearSlot(int slot)
{
	if (slot < 0 || slot > 11)
		return;

	delete mEquipment[slot];
	mEquipment[slot] = nullptr;

	calculateBonus();
}

Item* Equipment::getItem(int slot)
{
	if (mEquipment[slot] != nullptr)
		return mEquipment[slot];
	else
		return nullptr;
}

int Equipment::getBonus(int slot)
{
	return mBonus[slot];
}

void Equipment::save()
{
	std::ofstream outFile("save.txt", std::ios::app);

	outFile << "Equipment" << std::endl;

	for (int i = 0; i < 11; i++)
	{
		if (mEquipment[i] != nullptr)
			outFile << *mEquipment[i];
	}

	outFile << std::endl;

	outFile.close();
}

void Equipment::load()
{
	std::ifstream infile("save.txt");

	Item temp;
	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (line == "Equipment")
		{
			while (infile >> temp)
			{
				Item _item(temp.getId(), temp.getAmount());
				mEquipment[_item.getEquipmentDefinition()->getSlot()] = new Item(_item.getId(), _item.getAmount());
				mEquipment[_item.getEquipmentDefinition()->getSlot()]->Pos(mEquipmentPos[_item.getEquipmentDefinition()->getSlot()]);
			}
		}
	}

	player->setCombatStance(player->getCombatStance());

	calculateBonus();

	infile.close();
}