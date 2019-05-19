#include "Smithing.h"

#include "Skills.h"

std::vector<std::pair<int, int>> bar = { { 252, 13 },{ 254, 25 },{ 256, 38 },{ 260, 50 },{ 262, 63 },{ 264, 75 } };
std::vector<std::pair<int, int>> dagger = { { 268, 1 },{ 298, 15 },{ 328, 30 },{ 358, 50 },{ 388, 70 },{ 418, 85 } };
std::vector<std::pair<int, int>> hatchet = { { 12, 1 },{ 14, 16 },{ 16, 31 },{ 20, 51 },{ 22, 71 },{ 24, 86 } };
std::vector<std::pair<int, int>> mace = { { 270, 2 },{ 300, 17 },{ 330, 32 },{ 360, 52 },{ 390, 72 },{ 420, 87 } };
std::vector<std::pair<int, int>> medHelm = { { 272, 2 },{ 302, 18 },{ 332, 33 },{ 362, 53 },{ 392, 73 },{ 422, 88 } };
std::vector<std::pair<int, int>> bolt = { { 117, 3 },{ 118, 18 },{ 119, 33 },{ 120, 53 },{ 121, 73 },{ 122, 88 } };
std::vector<std::pair<int, int>> sword = { { 274, 4 },{ 304, 19 },{ 334, 34 },{ 364, 54 },{ 394, 74 },{ 424, 89 } };
std::vector<std::pair<int, int>> arrowtip = { { 59, 5 },{ 60, 20 },{ 61, 35 },{ 62, 55 },{ 63, 75 },{ 64, 90 } };
std::vector<std::pair<int, int>> scimitar = { { 276, 5 },{ 306, 20 },{ 336, 35 },{ 366, 55 },{ 396, 75 },{ 426, 90 } };
std::vector<std::pair<int, int>> cbowLimb = { { 81, 6 },{ 83, 23 },{ 85, 36 },{ 87, 56 },{ 89, 76 },{ 91, 91 } };
std::vector<std::pair<int, int>> longsword = { { 278, 6 },{ 308, 21 },{ 338, 36 },{ 368, 56 },{ 398, 76 },{ 428, 91 } };
std::vector<std::pair<int, int>> fullHelm = { { 280, 7 },{ 310, 22 },{ 340, 37 },{ 370, 57 },{ 400, 77 },{ 430, 92 } };
std::vector<std::pair<int, int>> knife = { { 835, 7 },{ 836, 22 },{ 837, 37 },{ 838, 57 },{ 839, 77 },{ 840, 92 } };
std::vector<std::pair<int, int>> sqShield = { { 282, 8 },{ 312, 23 },{ 342, 38 },{ 372, 58 },{ 402, 78 },{ 432, 93 } };
std::vector<std::pair<int, int>> warhammer = { { 284, 9 },{ 314, 24 },{ 344, 39 },{ 374, 59 },{ 404, 79 },{ 434, 94 } };
std::vector<std::pair<int, int>> battleaxe = { { 286, 10 },{ 316, 25 },{ 346, 40 },{ 376, 60 },{ 406, 80 },{ 436, 95 } };
std::vector<std::pair<int, int>> chainbody = { { 288, 11 },{ 318, 26 },{ 348, 41 },{ 378, 61 },{ 408, 81 },{ 438, 96 } };
std::vector<std::pair<int, int>> kiteshield = { { 290, 12 },{ 320, 27 },{ 350, 42 },{ 380, 62 },{ 410, 82 },{ 440, 97 } };
std::vector<std::pair<int, int>> twohand = { { 292, 14 },{ 322, 29 },{ 352, 44 },{ 382, 64 },{ 412, 84 },{ 442, 99 } };
std::vector<std::pair<int, int>> plateleg = { { 294, 16 },{ 324, 31 },{ 354, 46 },{ 384, 66 },{ 414, 86 },{ 444, 99 } };
std::vector<std::pair<int, int>> platebody = { { 296, 18 },{ 326, 33 },{ 356, 48 },{ 386, 68 },{ 416, 88 },{ 446, 99 } };

Smithing::Smithing(Player *p)
{
	player = p;

	mInputManager = InputManager::Instance();

	mBars[0] = new Texture("Items/BronzeBar.png");
	mBars[1] = new Texture("Items/IronBar.png");
	mBars[2] = new Texture("Items/SteelBar.png");
	mBars[3] = new Texture("Items/GoldBar.png");
	mBars[4] = new Texture("Items/MithrilBar.png");
	mBars[5] = new Texture("Items/AdamantBar.png");
	mBars[6] = new Texture("Items/RuneBar.png");

	mBarBackground = new Texture("BlankBackground.png");
	mBarBackground->Pos(Vector2(211.0f, 100.0f));
	mBarBackground->Scale(Vector2(14.5f, 2.5f));

	for (int i = 0; i < 7; i++)
	{
		mBars[i]->Pos(Vector2(115 + (32 * i), 100));
		mBars[i]->Scale(Vector2(2.0f, 2.0f));
	}

	mOptions[0] = new Texture("Dagger", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[1] = new Texture("Hatchet", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[2] = new Texture("Mace", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[3] = new Texture("Med Helm", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[4] = new Texture("Bolts", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[5] = new Texture("Sword", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[6] = new Texture("Arrowtips", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[7] = new Texture("Scimitar", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[8] = new Texture("C'bow Limb", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[9] = new Texture("Longsword", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[10] = new Texture("Full Helm", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[11] = new Texture("Knives", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[12] = new Texture("Sq Shield", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[13] = new Texture("Warhammer", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[14] = new Texture("Battleaxe", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[15] = new Texture("Chainbody", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[16] = new Texture("Kiteshield", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[17] = new Texture("2h Sword", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[18] = new Texture("Platelegs", "Romulus.ttf", 16, { 255, 255, 255 });
	mOptions[19] = new Texture("Platebody", "Romulus.ttf", 16, { 255, 255, 255 });

	for (int i = 0; i < 20; i++)
	{
		mOptions[i]->Pos(Vector2(211, 140 + (18 * i)));
	}

	mOptionsBackground = new Texture("BlankBackground.png");
	mOptionsBackground->Pos(Vector2(211.0f, 311.0f));
	mOptionsBackground->Scale(Vector2(4.75f, 22.6f));

	mOutline = new Texture("Outline.png");
	mOutline->Pos(Vector2(131, 100));
	mOutline->Scale(Vector2(2.0f, 2.0f));

	mSelected = 0;
	mSmelting = false;
	mSmithing = false;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	exitSmithing = false;
}

Smithing::~Smithing()
{
	player = nullptr;

	mInputManager = nullptr;

	for (int i = 0; i < 7; i++)
	{
		delete mBars[i];
		mBars[i] = nullptr;
	}

	delete mBarBackground;
	mBarBackground = nullptr;

	for (int i = 0; i < 20; i++)
	{
		delete mOptions[i];
		mOptions[i] = nullptr;
	}

	delete mOptionsBackground;
	mOptionsBackground = nullptr;

	delete mOutline;
	mOutline = nullptr;

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void Smithing::Update()
{
	static int mStartTicks = SDL_GetTicks();

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mEscapeButton->Intersects(mInputManager->MousePos()))
			exitSmithing = true;

		for (int i = 0; i < 7; i++)
		{
			if (mBars[i]->Intersects(mInputManager->MousePos()))
			{
				mSelected = i;
				
				if (!mSmithing)
				{
					mSmelting = true;
					mStartTicks = SDL_GetTicks();
				}
				else
				{
					if (mSelected > 3)
						mSelected -= 1;

					mOutline->Pos(Vector2(131 + (32 * mSelected), 100));
				}
				break;
			}
		}

		if (mSmithing)
		{
			for (int i = 0; i < 20; i++)
			{
				if (mOptions[i]->Intersects(mInputManager->MousePos()))
				{
					smith(i, mSelected);
					break;
				}
			}
		}
	}

	if ((SDL_GetTicks() >= mStartTicks + 600) && mSmelting)
	{
		smelt(mSelected);
		mStartTicks = SDL_GetTicks();
	}
}

void Smithing::Render()
{
	if (mSmithing)
		mBarBackground->Scale(Vector2(12.5f, 2.5f));
	else
		mBarBackground->Scale(Vector2(14.5f, 2.5f));
	mBarBackground->Render();
	
	for (int i = 0; i < 7; i++)
	{
		if (mSmithing)
		{
			if (i < 3)
			{
				mBars[i]->Pos(Vector2(131 + (32 * i), 100));
				mBars[i]->Render();
			}
			else if (i > 3)
			{
				mBars[i]->Pos(Vector2(131 + (32 * (i - 1)), 100));
				mBars[i]->Render();
			}
		}
		else
		{
			mBars[i]->Pos(Vector2(115 + (32 * i), 100));
			mBars[i]->Render();
		}
	}

	if (mSmithing)
	{
		mOutline->Render();
		mOptionsBackground->Render();
		for (int i = 0; i < 20; i++)
			mOptions[i]->Render();
	}

	mEscapeButton->Render();
}


void Smithing::smelt(std::vector<Item> items, int newId, int exp)
{
	if (player->inventory->hasItems(items))
	{
		for (int i = 0; i < items.size(); i++)
			player->inventory->removeItem(items[i].getId(), items[i].getAmount());

		player->inventory->add(Item(newId, 1));
		player->skills->addExperience(exp, smithing);
		if (newId == 258) player->skills->addExperience(30, crafting); //Gold bar
	}
	else
		mSmelting = false;
}

void Smithing::smelt(int id)
{
	switch (id)
	{
	case 0: //bronze bar (copper + tin)
		if (player->skills->getEffect(smithing) >= 1)
			smelt({ { 220, 1 },{ 222, 1 } }, 252, 7);
		else
			mSmelting = false;
		break;
	case 1: //iron bar (iron)
		if (player->skills->getEffect(smithing) >= 15)
		{
			if (player->inventory->hasItem(224, 1))
			{
				player->inventory->removeItem(224, 1);

				if (rand() % 2)
				{
					player->inventory->add(Item(254, 1));
					player->skills->addExperience(13, smithing);
				}
			}
			else
				mSmelting = false;
		}
		else
			mSmelting = false;
		break;
	case 2: //steel bar (iron + 1 coal)
		if (player->skills->getEffect(smithing) >= 30)
			smelt({ { 224, 1 },{ 226, 1 } }, 256, 18);
		else
			mSmelting = false;
		break;
	case 3: //gold bar (gold)
		if (player->skills->getEffect(smithing) >= 40)
			smelt({ { 228, 1 } }, 258, 23);
		else
			mSmelting = false;
		break;
	case 4: //mithril bar (mithril + 2 coal)
		if (player->skills->getEffect(smithing) >= 50)
			smelt({ { 230, 1 },{ 226, 2 } }, 260, 30);
		else
			mSmelting = false;
		break;
	case 5: //adamant bar (adamant + 3 coal)
		if (player->skills->getEffect(smithing) >= 70)
			smelt({ { 232, 1 },{ 226, 3 } }, 262, 38);
		else
			mSmelting = false;
		break;
	case 6: //rune bar (rune + 4 coal)
		if (player->skills->getEffect(smithing) >= 85)
			smelt({ { 234, 1 },{ 226, 4 } }, 264, 50);
		else
			mSmelting = false;
		break;
	default:
		mSmelting = false;
	}
}

void Smithing::smith(int id, int tier)
{
	if (!player->inventory->hasItem(266))
		return;

	switch (id)
	{
	case 0:
		if (player->skills->getEffect(smithing) >= dagger[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(dagger[tier].first, 1));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 1:
		if (player->skills->getEffect(smithing) >= hatchet[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(hatchet[tier].first, 1));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 2:
		if (player->skills->getEffect(smithing) >= mace[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(mace[tier].first, 1));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 3:
		if (player->skills->getEffect(smithing) >= medHelm[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(medHelm[tier].first, 1));
				player->skills->addExperience(bar[tier].second, smithing);

				std::cout << "You smith a med helm!" << std::endl;
			}
		}
		break;
	case 4:
		if (player->skills->getEffect(smithing) >= bolt[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(bolt[tier].first, 10));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 5:
		if (player->skills->getEffect(smithing) >= sword[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(sword[tier].first, 1));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 6:
		if (player->skills->getEffect(smithing) >= arrowtip[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(arrowtip[tier].first, 15));
				player->skills->addExperience(bar[tier].second, smithing);
			}
		}
		break;
	case 7:
		if (player->skills->getEffect(smithing) >= scimitar[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 2))
			{
				player->inventory->removeItem(bar[tier].first, 2);
				player->inventory->add(Item(scimitar[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 2, smithing);
			}
		}
		break;
	case 8:
		if (player->skills->getEffect(smithing) >= cbowLimb[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 2);
				player->inventory->add(Item(cbowLimb[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 2, smithing);
			}
		}
		break;
	case 9:
		if (player->skills->getEffect(smithing) >= longsword[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 2))
			{
				player->inventory->removeItem(bar[tier].first, 2);
				player->inventory->add(Item(longsword[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 2, smithing);
			}
		}
		break;
	case 10:
		if (player->skills->getEffect(smithing) >= fullHelm[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 2))
			{
				player->inventory->removeItem(bar[tier].first, 2);
				player->inventory->add(Item(fullHelm[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 2, smithing);
			}
		}
		break;
	case 11:
		if (player->skills->getEffect(smithing) >= knife[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 1))
			{
				player->inventory->removeItem(bar[tier].first, 1);
				player->inventory->add(Item(knife[tier].first, 5));
				player->skills->addExperience(bar[tier].second * 1, smithing);
			}
		}
		break;
	case 12:
		if (player->skills->getEffect(smithing) >= sqShield[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 2))
			{
				player->inventory->removeItem(bar[tier].first, 2);
				player->inventory->add(Item(sqShield[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 2, smithing);
			}
		}
		break;
	case 13:
		if (player->skills->getEffect(smithing) >= warhammer[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(warhammer[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 14:
		if (player->skills->getEffect(smithing) >= battleaxe[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(battleaxe[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 15:
		if (player->skills->getEffect(smithing) >= chainbody[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(chainbody[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 16:
		if (player->skills->getEffect(smithing) >= kiteshield[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(kiteshield[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 17:
		if (player->skills->getEffect(smithing) >= twohand[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(twohand[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 18:
		if (player->skills->getEffect(smithing) >= plateleg[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 3))
			{
				player->inventory->removeItem(bar[tier].first, 3);
				player->inventory->add(Item(plateleg[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 3, smithing);
			}
		}
		break;
	case 19:
		if (player->skills->getEffect(smithing) >= platebody[tier].second)
		{
			if (player->inventory->hasItem(bar[tier].first, 5))
			{
				player->inventory->removeItem(bar[tier].first, 5);
				player->inventory->add(Item(platebody[tier].first, 1));
				player->skills->addExperience(bar[tier].second * 5, smithing);
			}
		}
		break;
	}
}