#include "Crafting.h"
#include "Player.h"

Crafting::Crafting(Player* p)
{
	player = p;

	mInputManager = InputManager::Instance();

	mBackground = new Texture("AltBackground.png");

	mSelected = -1;
}


Crafting::~Crafting()
{
	player = nullptr;

	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	Clear();
}

void Crafting::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mOptions.size())
		{
			for (int i = 0; i < mOptions.size(); i++)
			{
				if (mOptions[i]->Intersects(mInputManager->MousePos()))
				{
					if (mSelected == 0)
					{
						craftLeather(i + 1);
					}
					else if (mSelected == 1)
					{
						craftHardLeather(i + 1);
					}
					else if (mSelected == 2)
					{
						craftDhide(i + 1);
					}
				}
			}
			mSelected = -1;
			Clear();
		}
	}
}

void Crafting::Render()
{
	if (mOptions.size())
	{
		mBackground->Render();
		for (int i = 0; i < mOptions.size(); i++)
			mOptions[i]->Render();
	}
}

void Crafting::Clear()
{
	for (auto it = mOptions.begin(); it != mOptions.end();)
		it = mOptions.erase(it);
	mOptions.clear();
}


void Crafting::pickFlax()
{
	player->inventory->add(Item(28, 1));
}

bool Crafting::spinFlax(int slot)
{
	if (player->inventory->getSlot(slot) != nullptr)
	{
		if (player->inventory->getSlot(slot)->getId() == 28)
		{
			player->inventory->replace(Item(30, 1), slot);
			player->skills->addExperience(15, crafting);
			return true;
		}
	}

	return false;
}

void Crafting::tan(int input)
{

	switch (input)
	{
	case 0://soft leather
		while (player->inventory->hasAmount(516) >= 1 && player->inventory->hasItem(448))
		{
			player->inventory->removeItem(516, 1);
			player->inventory->removeItem(448);
			player->inventory->add(Item(450, 1));
		}
		break;
	case 1://hard leather
		while (player->inventory->hasAmount(516) >= 3 && player->inventory->hasItem(448))
		{
			player->inventory->removeItem(516, 3);
			player->inventory->removeItem(448);
			player->inventory->add(Item(452, 1));
		}
		break;
	case 2://green dragonleather
		while (player->inventory->hasAmount(516) >= 20 && player->inventory->hasItem(474))
		{
			player->inventory->removeItem(516, 20);
			player->inventory->removeItem(474);
			player->inventory->add(Item(482, 1));
		}
		break;
	case 3://blue dragonleather
		while (player->inventory->hasAmount(516) >= 20 && player->inventory->hasItem(476))
		{
			player->inventory->removeItem(516, 20);
			player->inventory->removeItem(476);
			player->inventory->add(Item(484, 1));
		}
		break;
	case 4://red dragonleather
		while (player->inventory->hasAmount(516) >= 20 && player->inventory->hasItem(478))
		{
			player->inventory->removeItem(516, 20);
			player->inventory->removeItem(478);
			player->inventory->add(Item(486, 1));
		}
		break;
	case 5://black dragonleather
		while (player->inventory->hasAmount(516) >= 20 && player->inventory->hasItem(480))
		{
			player->inventory->removeItem(516, 20);
			player->inventory->removeItem(480);
			player->inventory->add(Item(488, 1));
		}
		break;
	}
}

void Crafting::craft(int _slotOne, int _slotTwo)
{
	slotOne = _slotOne;
	slotTwo = _slotTwo;

	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	if (player->inventory->getSlot(slotOne)->getId() == 514 && player->inventory->hasItem(515)) //Needle && Thread
	{
		if (player->inventory->getSlot(slotTwo)->getId() == 450) //Leather
		{
			mOptions.push_back(new Texture("Gloves", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Boots", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Cowl", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Vambs", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Body", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Chaps", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Coif", "Romulus.ttf", 16, { 255, 255, 255 }));

			mOptions[0]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 80));
			mOptions[1]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 64));
			mOptions[2]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 48));
			mOptions[3]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 32));
			mOptions[4]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));
			mOptions[5]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y));
			mOptions[6]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y + 16));

			mBackground->Scale(Vector2(3.5f, 9.0f));
			mBackground->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 32));

			mSelected = 0;
		}
		else if (player->inventory->getSlot(slotTwo)->getId() == 452) //Hard Leather
		{
			mOptions.push_back(new Texture("Body", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Chaps", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Body", "Romulus.ttf", 16, { 255, 255, 255 }));

			mOptions[0]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 32));
			mOptions[1]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));
			mOptions[2]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y));

			mBackground->Scale(Vector2(3.5f, 4.0f));
			mBackground->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));

			mSelected = 1;
		}
		else if ((player->inventory->getSlot(slotTwo)->getId() == 482) //Green Dhide
			|| (player->inventory->getSlot(slotTwo)->getId() == 484) //Blue Dhide
			|| (player->inventory->getSlot(slotTwo)->getId() == 486) //Red Dhide
			|| (player->inventory->getSlot(slotTwo)->getId() == 488)) //Black Dhide
		{
			mOptions.push_back(new Texture("Vambs", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Chaps", "Romulus.ttf", 16, { 255, 255, 255 }));
			mOptions.push_back(new Texture("Body", "Romulus.ttf", 16, { 255, 255, 255 }));

			mOptions[0]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 32));
			mOptions[1]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));
			mOptions[2]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y));

			mBackground->Scale(Vector2(3.5f, 4.0f));
			mBackground->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));

			mSelected = 2;
		}
	}
	else if (player->inventory->getSlot(slotOne)->getId() == 258) //Gems
	{
		craftJewellery();
	}
}

void Crafting::craftLeather(int input)
{
	if (player->inventory->getSlot(slotTwo)->getId() == 450)
	{
		switch (input)
		{
		case 1: //Leather gloves
			if (player->skills->getEffect(crafting) >= 1)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(454, 1));
				player->skills->addExperience(14, crafting);
			}
			else
				return;
			break;
		case 2: //Leather boots
			if (player->skills->getEffect(crafting) >= 7)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(456, 1));
				player->skills->addExperience(17, crafting);
			}
			else
				return;
			break;
		case 3: //Leather cowl
			if (player->skills->getEffect(crafting) >= 9)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(458, 1));
				player->skills->addExperience(19, crafting);
			}
			else
				return;
			break;
		case 4: //Leather vambraces
			if (player->skills->getEffect(crafting) >= 11)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(460, 1));
				player->skills->addExperience(22, crafting);
			}
			else
				return;
			break;
		case 5: //Leather body
			if (player->skills->getEffect(crafting) >= 14)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(462, 1));
				player->skills->addExperience(25, crafting);
			}
			else
				return;
			break;
		case 6: //Leather chaps
			if (player->skills->getEffect(crafting) >= 18)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(464, 1));
				player->skills->addExperience(27, crafting);
			}
			else
				return;
			break;
		case 7: //Coif
			if (player->skills->getEffect(crafting) >= 38)
			{
				player->inventory->removeItem(450);
				player->inventory->add(Item(468, 1));
				player->skills->addExperience(37, crafting);
			}
			else
				return;
		default:
			return;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);
		return;
	}
}

void Crafting::craftHardLeather(int input)
{

	if (player->inventory->getSlot(slotTwo)->getId() == 452)
	{
		switch (input)
		{
		case 1:
			if (player->skills->getEffect(crafting) >= 28)
			{
				player->inventory->removeItem(452);
				player->inventory->add(Item(466, 1));
				player->skills->addExperience(28, crafting);
			}
			else
				return;
			break;
		case 2:
			if (player->skills->getEffect(crafting) >= 41)
			{
				player->inventory->removeItem(452);
				player->inventory->add(Item(472, 1));
				player->skills->addExperience(40, crafting);
			}
			else
				return;
			break;
		case 3:
			if (player->skills->getEffect(crafting) >= 44)
			{
				player->inventory->removeItem(452);
				player->inventory->add(Item(470, 1));
				player->skills->addExperience(42, crafting);
			}
			else
				return;
			break;
		default:
			break;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);
		return;
	}
}

void Crafting::craftDhide(int input)
{
	if (player->inventory->getSlot(slotTwo)->getId() == 482)
	{
		switch (input)
		{
		case 1:
			if (player->skills->getEffect(crafting) >= 57)
			{
				player->inventory->removeItem(482);
				player->inventory->add(Item(490, 1));
				player->skills->addExperience(62, crafting);
			}
			else
				return;
			break;
		case 2:
			if (player->skills->getEffect(crafting) >= 60)
			{
				if (player->inventory->hasAmount(482) >= 2)
				{
					player->inventory->removeItem(482, 2);
					player->inventory->add(Item(492, 1));
					player->skills->addExperience(124, crafting);
				}
			}
			else
				return;
			break;
		case 3:
			if (player->skills->getEffect(crafting) >= 63)
			{
				if (player->inventory->hasAmount(482) >= 3)
				{
					player->inventory->removeItem(482, 3);
					player->inventory->add(Item(494, 1));
					player->skills->addExperience(186, crafting);
				}
			}
			else
				return;
			break;
		default:
			return;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);
		return;
	}
	else if (player->inventory->getSlot(slotTwo)->getId() == 484)
	{
		switch (input)
		{
		case 1:
			if (player->skills->getEffect(crafting) >= 66)
			{
				player->inventory->removeItem(484);
				player->inventory->add(Item(496, 1));
				player->skills->addExperience(70, crafting);
			}
			else
				return;
			break;
		case 2:
			if (player->skills->getEffect(crafting) >= 68)
			{
				if (player->inventory->hasAmount(484) >= 2)
				{
					player->inventory->removeItem(484, 2);
					player->inventory->add(Item(498, 1));
					player->skills->addExperience(140, crafting);
				}
			}
			else
				return;
			break;
		case 3:
			if (player->skills->getEffect(crafting) >= 71)
			{
				if (player->inventory->hasAmount(484) >= 3)
				{
					player->inventory->removeItem(484, 3);
					player->inventory->add(Item(500, 1));
					player->skills->addExperience(210, crafting);
				}
			}
			else
				return;
			break;
		default:
			return;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);
		return;
	}
	else if (player->inventory->getSlot(slotTwo)->getId() == 486)
	{
		switch (input)
		{
		case 1:
			if (player->skills->getEffect(crafting) >= 73)
			{
				player->inventory->removeItem(486);
				player->inventory->add(Item(502, 1));
				player->skills->addExperience(78, crafting);
			}
			else
				return;
			break;
		case 2:
			if (player->skills->getEffect(crafting) >= 75)
			{
				if (player->inventory->hasAmount(486) >= 2)
				{
					player->inventory->removeItem(486, 2);
					player->inventory->add(Item(504, 1));
					player->skills->addExperience(156, crafting);
				}
			}
			else
				return;
			break;
		case 3:
			if (player->skills->getEffect(crafting) >= 77)
			{
				if (player->inventory->hasAmount(486) >= 3)
				{
					player->inventory->removeItem(486, 3);
					player->inventory->add(Item(506, 1));
					player->skills->addExperience(234, crafting);
				}
			}
			else
				return;
			break;
		default:
			return;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);
		return;
	}
	else if (player->inventory->getSlot(slotTwo)->getId() == 488)
	{
		switch (input)
		{
		case 1:
			if (player->skills->getEffect(crafting) >= 73)
			{
				player->inventory->removeItem(488);
				player->inventory->add(Item(508, 1));
				player->skills->addExperience(86, crafting);
			}
			else
				return;
			break;
		case 2:
			if (player->skills->getEffect(crafting) >= 75)
			{
				if (player->inventory->hasAmount(488) >= 2)
				{
					player->inventory->removeItem(488, 2);
					player->inventory->add(Item(510, 1));
					player->skills->addExperience(156, crafting);
				}
			}
			else
				return;
			break;
		case 3:
			if (player->skills->getEffect(crafting) >= 77)
			{
				if (player->inventory->hasAmount(488) >= 3)
				{
					player->inventory->removeItem(488, 3);
					player->inventory->add(Item(512, 1));
					player->skills->addExperience(258, crafting);
				}
			}
			else
				return;
			break;
		default:
			return;
		}

		if (rand() % 2)
			player->inventory->removeItem(515, 1);

		return;
	}
	else
		return;
}

void Crafting::craftJewellery()
{
	if (player->inventory->getSlot(slotOne)->getId() == 258)
	{
		switch (player->inventory->getSlot(slotTwo)->getId())
		{
		case 842:
			if (player->skills->getEffect(crafting) >= 8)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(856, 1), slotTwo);
				player->skills->addExperience(40, crafting);
				return;
			}
			else
				return;
			break;
		case 844:
			if (player->skills->getEffect(crafting) >= 24)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(858, 1), slotTwo);
				player->skills->addExperience(115, crafting);
				return;
			}
			else
				return;
			break;
		case 846:
			if (player->skills->getEffect(crafting) >= 31)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(860, 1), slotTwo);
				player->skills->addExperience(138, crafting);
				return;
			}
			else
				return;
			break;
		case 848:
			if (player->skills->getEffect(crafting) >= 50)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(862, 1), slotTwo);
				player->skills->addExperience(170, crafting);
				return;
			}
			else
				return;
			break;
		case 850:
			if (player->skills->getEffect(crafting) >= 70)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(864, 1), slotTwo);
				player->skills->addExperience(208, crafting);
				return;
			}
			else
				return;
			break;
		case 852:
			if (player->skills->getEffect(crafting) >= 80)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(866, 1), slotTwo);
				player->skills->addExperience(258, crafting);
				return;
			}
			else
				return;
			break;
		case 854:
			if (player->skills->getEffect(crafting) >= 90)
			{
				player->inventory->remove(slotOne);
				player->inventory->replace(Item(868, 1), slotTwo);
				player->skills->addExperience(333, crafting);
				return;
			}
			else
				return;
			break;
		}
	}
}