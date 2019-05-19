#include "Herblore.h"

#include "Inventory.h"
#include "Skills.h"
#include "Player.h"

int requirement[] = { 1, 12, 22, 36, 38, 45, 55, 63, 66, 72, 76, 78, 81 };
int primary[] = { 595, 597,  599, 601, 599, 603, 605, 607, 609, 611, 613, 615, 617 };
int secondary[] = { 575, 577, 579, 581, 583, 575, 577, 585, 579, 587, 589, 591, 593 };
int product[] = { 623, 631, 639, 647, 655, 663, 671, 679, 687, 695, 703, 711, 719 };
int experience[] = { 28, 55, 83, 90, 95, 109, 136, 155, 163, 177, 186, 190, 200 };

Herblore::Herblore(Player *p)
{
	player = p;
}


Herblore::~Herblore()
{
	player = nullptr;
}


void Herblore::brew(int slotOne, int slotTwo)
{
	if (player->inventory->getSlot(slotOne) == nullptr || player->inventory->getSlot(slotTwo) == nullptr)
		return;

	int potionId = -1;

	for (int i = 0; i < 13; i++)
	{
		if (player->inventory->getSlot(slotOne)->getId() == primary[i])
			if (player->inventory->getSlot(slotTwo)->getId() == secondary[i])
				potionId = i;
	}

	if ((potionId < 0 || potionId > 13) || !player->inventory->hasItem(573))
		return;
	else if (potionId == 13) //Super combat
	{
		if (player->skills->getEffect(herblore) >= 90)
		{
			if (player->inventory->hasItem(665) && player->inventory->hasItem(673) && player->inventory->hasItem(689))
			{
				player->inventory->removeItem(573); //Vial
				player->inventory->removeItem(665); //Super attack
				player->inventory->removeItem(673); //Super strength
				player->inventory->removeItem(689); //Super defense
				player->inventory->add(Item(729, 1)); //Super combat
				player->skills->addExperience(150, herblore);
			}
		}
	}
	else
	{
		if (player->skills->getEffect(herblore) >= requirement[potionId])
		{
			if (player->inventory->hasItem(primary[potionId]) && player->inventory->hasItem(secondary[potionId]))
			{
				player->inventory->removeItem(573); //Vial
				player->inventory->removeItem(primary[potionId]);
				player->inventory->removeItem(secondary[potionId]);
				player->inventory->add(Item(product[potionId], 1));
				player->skills->addExperience(experience[potionId], herblore);
			}
		}
	}
}

bool Herblore::decant(int slotOne, int slotTwo)
{
	int oneDose[] = { 619, 627, 635, 643, 651, 659, 667, 675, 683, 691, 699, 707, 715, 723 },
		twoDose[] = { 621, 629, 637, 645, 653, 661, 669, 677, 685, 693, 701, 709, 717, 725 },
		threeDose[] = { 623, 631, 639, 647, 655, 663, 671, 679, 687, 695, 703, 711, 719, 727 },
		fourDose[] = { 625, 633, 641, 649, 657, 665, 673, 681, 689, 697, 705, 713, 721, 729 };

	if (player->inventory->getSlot(slotOne) == nullptr || player->inventory->getSlot(slotTwo) == nullptr)
		return false;

	for (int i = 0; i < sizeof(oneDose) / sizeof(oneDose[0]); i++)
	{
		if (player->inventory->getSlot(slotOne)->getId() == oneDose[i])
		{
			if (player->inventory->getSlot(slotTwo)->getId() == oneDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(twoDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == twoDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(threeDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == threeDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else
				return false;
		}
	}

	for (int i = 0; i < sizeof(twoDose) / sizeof(twoDose[0]); i++)
	{
		if (player->inventory->getSlot(slotOne)->getId() == twoDose[i])
		{
			if (player->inventory->getSlot(slotTwo)->getId() == oneDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(threeDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == twoDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == threeDose[i])
			{
				player->inventory->replace(Item(oneDose[i], 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else
				return false;
		}
	}

	for (int i = 0; i < sizeof(threeDose) / sizeof(threeDose[0]); i++)
	{
		if (player->inventory->getSlot(slotOne)->getId() == threeDose[i])
		{
			if (player->inventory->getSlot(slotTwo)->getId() == oneDose[i])
			{
				player->inventory->replace(Item(573, 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == twoDose[i])
			{
				player->inventory->replace(Item(oneDose[i], 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else if (player->inventory->getSlot(slotTwo)->getId() == threeDose[i])
			{
				player->inventory->replace(Item(twoDose[i], 1), slotOne);
				player->inventory->replace(Item(fourDose[i], 1), slotTwo);
				return true;
			}
			else
				return false;
		}
	}
}