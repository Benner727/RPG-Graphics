#include "Fletching.h"
#include "Player.h"

Fletching::Fletching(Player *p)
{
	player = p;

	mInputManager = InputManager::Instance();
	
	mBackground = new Texture("AltBackground.png");

	mSelected = -1;
}

Fletching::~Fletching()
{
	player = nullptr;

	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	Clear();
}

void Fletching::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mOptions.size())
		{
			for (int i = 0; i < mOptions.size(); i++)
			{
				if (mOptions[i]->Intersects(mInputManager->MousePos()))
				{
					if (mSelected == 1)
					{
						knifeOnLog(i);
						mSelected = -1;
					}
					break;
				}
			}
			Clear();
		}
	}
}

void Fletching::Render()
{
	if (mOptions.size())
	{
		mBackground->Render();
		for (int i = 0; i < mOptions.size(); i++)
			mOptions[i]->Render();
	}
}

void Fletching::Clear()
{
	for (auto it = mOptions.begin(); it != mOptions.end();)
		it = mOptions.erase(it);
	mOptions.clear();
}

void Fletching::fletch(int _slotOne, int _slotTwo)
{
	slotOne = _slotOne;
	slotTwo = _slotTwo;

	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;


	if (player->inventory->getSlot(slotOne)->getId() == 129) //Use knife on logs
	{
		int	logs[6] = { 0, 2, 4, 6, 8, 10 };
		for (int i = 0; i < 6; i++)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == logs[i])
				break;

			if (i == 5) return;
		}

		mOptions.push_back(new Texture("Shafts", "Romulus.ttf", 16, { 255, 255, 255 }));
		mOptions.push_back(new Texture("Bow", "Romulus.ttf", 16, { 255, 255, 255 }));
		mOptions.push_back(new Texture("Stock", "Romulus.ttf", 16, { 255, 255, 255 }));

		mOptions[0]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 32));
		mOptions[1]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));
		mOptions[2]->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y));
		
		mBackground->Scale(Vector2(3.5f, 4.0f));
		mBackground->Pos(Vector2(player->inventory->getSlot(slotTwo)->Pos().x + 16, player->inventory->getSlot(slotTwo)->Pos().y - 16));

		mSelected = 1;
	}
	else if (player->inventory->getSlot(slotOne)->getId() == 30) //String shortbow or crossbow
	{
		stringShortbow(slotOne, slotTwo);
	}
	else if (player->inventory->getSlot(slotOne)->getId() == 57 || player->inventory->getSlot(slotOne)->getId() == 58) //Fletch arrows / bolts
	{
		fletchArrow(slotOne, slotTwo);
	}
	else //Make crossbow unstrung
	{
		makeCrossbow(slotOne, slotTwo);
	}
}


void Fletching::knifeOnLog(int input)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	int	id = player->inventory->getSlot(slotTwo)->getId();

	//Fletch arrow shafts
	if (input == 0)
	{
		switch (id)
		{
		case 0:
			if (player->skills->getEffect(fletching) >= 1)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 15));
				player->skills->addExperience(5, fletching);
			}
			break;
		case 2:
			if (player->skills->getEffect(fletching) >= 15)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 30));
				player->skills->addExperience(10, fletching);
			}
			break;
		case 4:
			if (player->skills->getEffect(fletching) >= 30)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 45));
				player->skills->addExperience(15, fletching);
			}
			break;
		case 6:
			if (player->skills->getEffect(fletching) >= 45)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 60));
				player->skills->addExperience(20, fletching);
			}
			break;
		case 8:
			if (player->skills->getEffect(fletching) >= 60)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 75));
				player->skills->addExperience(25, fletching);
			}
			break;
		case 10:
			if (player->skills->getEffect(fletching) >= 75)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(56, 90));
				player->skills->addExperience(30, fletching);
			}
			break;
		default:
			return;
			break;
		}
		return;
	}
	else if (input == 1) //Fletch unstrung shortbow
	{
		switch (id)
		{
		case 0:
			if (player->skills->getEffect(fletching) >= 5)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(32, 1));
				player->skills->addExperience(5, fletching);
			}
			break;
		case 2:
			if (player->skills->getEffect(fletching) >= 20)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(34, 1));
				player->skills->addExperience(17, fletching);
			}
			break;
		case 4:
			if (player->skills->getEffect(fletching) >= 35)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(36, 1));
				player->skills->addExperience(34, fletching);
			}
			break;
		case 6:
			if (player->skills->getEffect(fletching) >= 50)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(38, 1));
				player->skills->addExperience(50, fletching);
			}
			break;
		case 8:
			if (player->skills->getEffect(fletching) >= 65)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(40, 1));
				player->skills->addExperience(68, fletching);
				return;
			}
			break;
		case 10:
			if (player->skills->getEffect(fletching) >= 80)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(42, 1));
				player->skills->addExperience(84, fletching);
			}
			break;
		default:
			return;
			break;
		}
		return;
	}
	else if (input == 2) //Fletch crossbow stock
	{
		switch (id)
		{
		case 0:
			if (player->skills->getEffect(fletching) >= 9)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(71, 1));
				player->skills->addExperience(6, fletching);
			}
			break;
		case 2:
			if (player->skills->getEffect(fletching) >= 24)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(73, 1));
				player->skills->addExperience(27, fletching);
			}
			break;
		case 4:
			if (player->skills->getEffect(fletching) >= 39)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(75, 1));
				player->skills->addExperience(32, fletching);
			}
			break;
		case 6:
			if (player->skills->getEffect(fletching) >= 54)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(77, 1));
				player->skills->addExperience(41, fletching);
			}
			break;
		case 8:
			if (player->skills->getEffect(fletching) >= 69)
			{
				player->inventory->removeItem(id);
				player->inventory->add(Item(79, 1));
				player->skills->addExperience(50, fletching);
			}
			break;
		default:
			return;
			break;
		}
		return;
	}
}

void Fletching::stringShortbow(int slotOne, int slotTwo)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	int id = player->inventory->getSlot(slotTwo)->getId();

	switch (id)
	{
	case 32:
		if (player->skills->getEffect(fletching) >= 5)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(44, 1));
			player->skills->addExperience(5, fletching);
		}
		break;
	case 34:
		if (player->skills->getEffect(fletching) >= 20)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(46, 1));
			player->skills->addExperience(17, fletching);
		}
		break;
	case 36:
		if (player->skills->getEffect(fletching) >= 35)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(48, 1));
			player->skills->addExperience(34, fletching);
		}
		break;
	case 38:
		if (player->skills->getEffect(fletching) >= 50)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(50, 1));
			player->skills->addExperience(50, fletching);
		}
		break;
	case 40:
		if (player->skills->getEffect(fletching) >= 65)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(52, 1));
			player->skills->addExperience(68, fletching);
		}
		break;
	case 42:
		if (player->skills->getEffect(fletching) >= 80)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(54, 1));
		}
		break;
	}
}

void Fletching::stringCrossbow(int slotOne, int slotTwo, int amount)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	int id = player->inventory->getSlot(slotTwo)->getId();

	switch (id)
	{
	case 93:
		if (player->skills->getEffect(fletching) >= 9)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(105, 1));
			player->skills->addExperience(6, fletching);
		}
		break;
	case 95:
		if (player->skills->getEffect(fletching) >= 39)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(107, 1));
			player->skills->addExperience(22, fletching);
		}
		break;
	case 97:
		if (player->skills->getEffect(fletching) >= 46)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(109, 1));
			player->skills->addExperience(24, fletching);
		}
		break;
	case 99:
		if (player->skills->getEffect(fletching) >= 54)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(111, 1));
			player->skills->addExperience(32, fletching);
		}
		break;
	case 101:
		if (player->skills->getEffect(fletching) >= 61)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(113, 1));
			player->skills->addExperience(41, fletching);
		}
		break;
	case 103:
		if (player->skills->getEffect(fletching) >= 69)
		{
			player->inventory->removeItem(30);
			player->inventory->removeItem(id);
			player->inventory->add(Item(115, 1));
			player->skills->addExperience(50, fletching);
		}
		break;
	}
}

void Fletching::fletchBolt(int slotOne, int slotTwo, int amount)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	switch (player->inventory->getSlot(slotTwo)->getId())
	{
	case 117:
		if (player->skills->getEffect(fletching) >= 9)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(123, 15));
					player->skills->addExperience(5, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(123, amount));
				player->skills->addExperience(amount * 0.333, fletching);
			}
		}
		break;
	case 118:
		if (player->skills->getEffect(fletching) >= 39)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(124, 15));
					player->skills->addExperience(15, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(124, amount));
				player->skills->addExperience(amount, fletching);
			}
		}
		break;
	case 119:
		if (player->skills->getEffect(fletching) >= 46)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(125, 15));
					player->skills->addExperience(35, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(125, amount));
				player->skills->addExperience(amount * 2.333, fletching);
			}
		}
		break;
	case 120:
		if (player->skills->getEffect(fletching) >= 54)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(126, 15));
					player->skills->addExperience(50, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(126, amount));
				player->skills->addExperience(amount * 3.333, fletching);
			}
		}
		break;
	case 121:
		if (player->skills->getEffect(fletching) >= 61)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(127, 15));
					player->skills->addExperience(70, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(127, amount));
				player->skills->addExperience(amount * 4.666, fletching);
			}
		}
		break;
	case 122:
		if (player->skills->getEffect(fletching) >= 69)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(128, 15));
					player->skills->addExperience(100, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(128, amount));
				player->skills->addExperience(amount * 6.666, fletching);
			}
		}
		break;
	}
}

void Fletching::fletchArrow(int slotOne, int slotTwo)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	int amount = 1;

	if (player->inventory->getSlot(slotTwo)->getId() == 56)
	{
		if (player->skills->getEffect(fletching) >= 1)
		{
			if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
			{
				if (player->inventory->getFreeSlots())
				{
					player->inventory->remove(slotOne, 15);
					player->inventory->remove(slotTwo, 15);
					player->inventory->add(Item(58, 15));
					player->skills->addExperience(15, fletching);
				}
			}
			else
			{
				int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
				player->inventory->remove(slotOne, amount);
				player->inventory->remove(slotTwo, amount);
				player->inventory->add(Item(58, amount));
				player->skills->addExperience(amount, fletching);
			}
		}
	}
	else
	{
		switch (player->inventory->getSlot(slotTwo)->getId())
		{
		case 59:
			if (player->skills->getEffect(fletching) >= 1)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(65, 15));
						player->skills->addExperience(20, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(65, amount));
					player->skills->addExperience(amount * 1.333, fletching);
				}
			}
			break;
		case 60:
			if (player->skills->getEffect(fletching) >= 15)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(66, 15));
						player->skills->addExperience(38, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(66, amount));
					player->skills->addExperience(amount * 2.533, fletching);
				}
			}
			break;
		case 61:
			if (player->skills->getEffect(fletching) >= 30)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(67, 15));
						player->skills->addExperience(75, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(67, amount));
					player->skills->addExperience(amount * 5, fletching);
				}
			}
			break;
		case 62:
			if (player->skills->getEffect(fletching) >= 45)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(68, 15));
						player->skills->addExperience(113, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(68, amount));
					player->skills->addExperience(amount * 7.533, fletching);
				}
			}
			break;
		case 63:
			if (player->skills->getEffect(fletching) >= 60)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(69, 15));
						player->skills->addExperience(150, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(69, amount));
					player->skills->addExperience(amount * 10, fletching);
				}
			}
			break;
		case 64:
			if (player->skills->getEffect(fletching) >= 75)
			{
				if (player->inventory->getSlot(slotOne)->getAmount() > 15 && player->inventory->getSlot(slotTwo)->getAmount() > 15)
				{
					if (player->inventory->getFreeSlots())
					{
						player->inventory->remove(slotOne, 15);
						player->inventory->remove(slotTwo, 15);
						player->inventory->add(Item(70, 15));
						player->skills->addExperience(188, fletching);
					}
				}
				else
				{
					int amount = player->inventory->getSlot(slotOne)->getAmount() < player->inventory->getSlot(slotTwo)->getAmount() ? player->inventory->getSlot(slotOne)->getAmount() : player->inventory->getSlot(slotTwo)->getAmount();
					player->inventory->remove(slotOne, amount);
					player->inventory->remove(slotTwo, amount);
					player->inventory->add(Item(70, amount));
					player->skills->addExperience(amount * 12.533, fletching);
				}
			}
			break;
		default:
			fletchBolt(slotOne, slotTwo, amount);
		}
	}
}

void Fletching::makeCrossbow(int slotOne, int slotTwo)
{
	if (player->inventory->getSlot(slotOne) == NULL)
		return;
	else if (player->inventory->getSlot(slotTwo) == NULL)
		return;

	switch (player->inventory->getSlot(slotOne)->getId())
	{
	case 71:
		if (player->skills->getEffect(fletching) >= 9)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 81)
			{
				player->inventory->replace(Item(93, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(12, fletching);
				return;
			}
		}
		if (player->skills->getEffect(fletching) >= 39)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 83)
			{
				player->inventory->replace(Item(95, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(44, fletching);
				return;
			}
		}
		break;
	case 73:
		if (player->skills->getEffect(fletching) >= 46)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 85)
			{
				player->inventory->replace(Item(97, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(54, fletching);
				return;
			}
		}
		break;
	case 75:
		if (player->skills->getEffect(fletching) >= 54)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 87)
			{
				player->inventory->replace(Item(99, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(64, fletching);
				return;
			}
		}
		break;
	case 77:
		if (player->skills->getEffect(fletching) >= 61)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 89)
			{
				player->inventory->replace(Item(101, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(82, fletching);
				return;
			}
		}
		break;
	case 79:
		if (player->skills->getEffect(fletching) >= 69)
		{
			if (player->inventory->getSlot(slotTwo)->getId() == 91)
			{
				player->inventory->replace(Item(103, 1), slotOne);
				player->inventory->remove(slotTwo);
				player->skills->addExperience(100, fletching);
				return;
			}
		}
		break;
	default:
		break;
	}
}