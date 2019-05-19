#include "Cooking.h"

#include <random>
#include <ctime>

#include "Skills.h"
#include "Inventory.h"

std::default_random_engine randGen((unsigned)time(NULL));
std::uniform_int_distribution<int> chance(0, 99);


const std::vector<int> rawFood = { 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 208, 210 };
const std::vector<int> cookReq = { 1, 1, 5, 1, 10, 15, 18, 20, 25, 30, 40, 43, 45, 62, 80, 90, 1, 1 };
const std::vector<int> cookExp = { 30, 40, 50, 30, 60, 70, 75, 80, 90, 100, 120, 130, 140, 150, 210, 215, 30, 40 };
const std::vector<int> cookedFood = { 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 212, 214 };

Cooking::Cooking(Player *p)
{
	player = p;
}


Cooking::~Cooking()
{
	player = nullptr;
}

void Cooking::Update()
{
	static int mStartTicks = SDL_GetTicks();

	if (SDL_GetTicks() >= mStartTicks + 600)
	{
		for (int i = 0; i < 20; i++)
		{
			if (cook(i))
			{
				mStartTicks = SDL_GetTicks();
				break;
			}
		}
	}
}

bool Cooking::cook(int slot)
{
	if (player->inventory->getSlot(slot) == nullptr)
		return false;

	for (int i = 0; i < rawFood.size(); i++)
	{
		if (player->inventory->getSlot(slot)->getId() == rawFood[i])
		{
			if (player->skills->getEffect(cooking) >= cookReq[i])
			{
				int rate = (int)std::round((((double)player->skills->getEffect(cooking) * 50.0) - ((double)cookReq[i] * 15.0)) / (double)cookReq[i] / 3.0 * 4.0);
				int roll = chance(randGen);

				if (rate >= roll)
				{

					player->inventory->remove(slot);
					player->inventory->add(Item(cookedFood[i], 1));
					player->skills->addExperience(cookExp[i], cooking);
					return true;
				}
				else
				{
					player->inventory->remove(slot);
					player->inventory->add(Item(216, 1));
					return true;
				}
			}
		}
	}

	return false;
}