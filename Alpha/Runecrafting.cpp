#include "Runecrafting.h"

#include "Skills.h"
#include "Inventory.h"

Runecrafting::Runecrafting(Player* player)
{
	mPlayer = player;

	mInputManager = InputManager::Instance();

	mBackground = new Texture("AbyssBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	exitRunecrafting = false;

	mAltars[0] = new Texture("Entities/AirAltar.png");
	mAltars[1] = new Texture("Entities/MindAltar.png");
	mAltars[2] = new Texture("Entities/WaterAltar.png");
	mAltars[3] = new Texture("Entities/EarthAltar.png");
	mAltars[4] = new Texture("Entities/FireAltar.png");
	mAltars[5] = new Texture("Entities/CosmicAltar.png");
	mAltars[6] = new Texture("Entities/ChaosAltar.png");
	mAltars[7] = new Texture("Entities/NatureAltar.png");
	mAltars[8] = new Texture("Entities/DeathAltar.png");
	mAltars[9] = new Texture("Entities/BloodAltar.png");

	mAltars[0]->Pos(Vector2(200.0f, 120.0f));
	mAltars[1]->Pos(Vector2(130.0f, 180.0f));
	mAltars[2]->Pos(Vector2(260.0f, 180.0f));
	mAltars[3]->Pos(Vector2(90.0f, 250.0f));
	mAltars[4]->Pos(Vector2(310.0f, 250.0f));
	mAltars[5]->Pos(Vector2(310.0f, 320.0f));
	mAltars[6]->Pos(Vector2(90.0f, 320.0f));
	mAltars[7]->Pos(Vector2(130.0f, 390.0f));
	mAltars[8]->Pos(Vector2(270.0f, 390.0f));
	mAltars[9]->Pos(Vector2(200.0f, 450.0f));

	for (int i = 0; i < 10; i++)
		mAltars[i]->Scale(Vector2(3.0f, 3.0f));
}

Runecrafting::~Runecrafting()
{
	mPlayer = nullptr;

	mInputManager = nullptr;

	delete mBackground;
	mBackground = nullptr;

	for (int i = 0; i < 10; i++)
	{
		delete mAltars[i];
		mAltars[i] = nullptr;
	}

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void Runecrafting::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
		{
			exitRunecrafting = true;
		}

		for (int i = 0; i < 10; i++)
		{
			if (mAltars[i]->Intersects(mInputManager->MousePos()))
				runecraft(i);
		}
	}
}

void Runecrafting::Render()
{
	mBackground->Render();
	mEscapeButton->Render();

	for (int i = 0; i < 10; i++)
		mAltars[i]->Render();
}

void Runecrafting::runecraft(int id)
{
	switch (id)
	{
	case 0: //air runes
		if (mPlayer->inventory->hasItem(519))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 99)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 10));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 88)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 9));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 77)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 8));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 66)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 7));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 55)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 6));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 44)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 5));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 33)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 4));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 22)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 3));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 11)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount * 2));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 1)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(539, amount));
				mPlayer->skills->addExperience(5 * amount, runecrafting);
			}
		}
		break;
	case 1: //mind runes
		if (mPlayer->inventory->hasItem(521))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 98)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 8));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 84)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 7));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 70)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 6));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 56)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 5));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 42)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 4));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 28)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 3));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}

			else if (mPlayer->skills->getEffect(runecrafting) >= 14)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount * 2));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 2)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(540, amount));
				mPlayer->skills->addExperience(6 * amount, runecrafting);
			}
		}
		break;
	case 2: //water runes
		if (mPlayer->inventory->hasItem(523))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 95)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount * 6));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 76)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount * 5));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 57)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount * 4));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 38)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount * 3));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 19)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount * 2));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 5)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(541, amount));
				mPlayer->skills->addExperience(7 * amount, runecrafting);
			}
		}
		break;
	case 3: //earth runes
		if (mPlayer->inventory->hasItem(525))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 78)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(542, amount * 4));
				mPlayer->skills->addExperience(8 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 52)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(542, amount * 3));
				mPlayer->skills->addExperience(8 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 26)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(542, amount * 2));
				mPlayer->skills->addExperience(8 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 9)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(542, amount));
				mPlayer->skills->addExperience(8 * amount, runecrafting);
			}
		}
		break;
	case 4: //Fire runes
		if (mPlayer->inventory->hasItem(527))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 70)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(543, amount * 3));
				mPlayer->skills->addExperience(9 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 35)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(543, amount * 2));
				mPlayer->skills->addExperience(9 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 14)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(543, amount));
				mPlayer->skills->addExperience(9 * amount, runecrafting);
			}
		}
		break;
	case 5: //Cosmic runes
		if (mPlayer->inventory->hasItem(529))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 59)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(544, amount * 2));
				mPlayer->skills->addExperience(10 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 27)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(544, amount));
				mPlayer->skills->addExperience(10 * amount, runecrafting);
			}
		}
		break;
	case 6: //Chaos runes
		if (mPlayer->inventory->hasItem(531))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 74)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(545, amount * 2));
				mPlayer->skills->addExperience(11 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 35)
			{
				int amount = mPlayer->inventory->hasAmount(517);
				mPlayer->inventory->removeItem(517, amount);
				mPlayer->inventory->add(Item(545, amount));
				mPlayer->skills->addExperience(11 * amount, runecrafting);
			}
		}
		break;
	case 7: //Nature runes
		if (mPlayer->inventory->hasItem(533))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 91)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(546, amount * 2));
				mPlayer->skills->addExperience(12 * amount, runecrafting);
			}
			else if (mPlayer->skills->getEffect(runecrafting) >= 44)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(546, amount));
				mPlayer->skills->addExperience(12 * amount, runecrafting);
			}
		}
		break;
	case 8: //Death runes
		if (mPlayer->inventory->hasItem(535))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 65)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(547, amount));
				mPlayer->skills->addExperience(15 * amount, runecrafting);
			}
		}
		break;
	case 9: //Blood runes
		if (mPlayer->inventory->hasItem(537))
		{
			if (mPlayer->skills->getEffect(runecrafting) >= 77)
			{
				int amount = mPlayer->inventory->hasAmount(218);
				mPlayer->inventory->removeItem(218, amount);
				mPlayer->inventory->add(Item(548, amount));
				mPlayer->skills->addExperience(30 * amount, runecrafting);
			}
		}
		break;
	}
}