#include "Magic.h"
#include "Player.h"
#include "Skills.h"
#include "Inventory.h"
#include "Equipment.h"

SpellBook* Magic::mSpellBook[20] =
{
	new SpellBook("Wind Bolt",{ Item(539, 1), Item(540, 1) }, 1, 2, 6),
	new SpellBook("Frost Bolt",{ Item(539, 1), Item(541, 1), Item(540, 1) }, 5, 4, 8),
	new SpellBook("Earth Bolt",{ Item(539, 1), Item(542, 2), Item(540, 1) }, 9, 6, 10),
	new SpellBook("Fire Bolt",{ Item(539, 1), Item(543, 3), Item(540, 1) }, 13, 8, 12),
	new SpellBook("Air Strike",{ Item(539, 2), Item(545, 1) }, 17, 9, 14),
	new SpellBook("Water Strike",{ Item(539, 2), Item(541, 2), Item(545, 1) }, 21, 10, 17),
	new SpellBook("Terra Strike",{ Item(539, 2), Item(542, 3), Item(545, 1) }, 29, 12, 20),
	new SpellBook("Flame Strike",{ Item(539, 3), Item(543, 4), Item(545, 1) }, 35, 14, 22),
	new SpellBook("Howling Blast",{ Item(539, 3), Item(547, 1) }, 41, 16, 26),
	new SpellBook("Ice Blast",{ Item(539, 3), Item(541, 3), Item(547, 1) }, 47, 18, 28),
	new SpellBook("Magic Dart",{ Item(540, 4), Item(547, 1) }, 50, 15, 30),
	new SpellBook("Rock Blast",{ Item(539, 3), Item(542, 4), Item(547, 1) }, 53, 20, 32),
	new SpellBook("Alchemy",{ Item(546, 1), Item(543, 5) }, 55, 0, 65),
	new SpellBook("Pyro Blast",{ Item(539, 4), Item(543, 6), Item(547, 1) }, 59, 22, 35),
	new SpellBook("Conversion",{ Item(546, 2), Item(541, 2), Item(542, 4) }, 60, 0, 36),
	new SpellBook("Smite",{ Item(548, 2), Item(544, 4) }, 61, 30, 61),
	new SpellBook("Cloud Burst",{ Item(548, 1), Item(539, 5) }, 62, 24, 36),
	new SpellBook("Storm Burst",{ Item(548, 1), Item(541, 7), Item(539, 5) }, 65, 26, 38),
	new SpellBook("Seismic Burst",{ Item(548, 1), Item(542, 7), Item(539, 5) }, 70, 28, 40),
	new SpellBook("Lava Burst",{ Item(548, 1), Item(543, 7), Item(539, 5) }, 75, 30, 43)
};

Magic::Magic(Player* _player)
{
	mPlayer = _player;

	mInputManager = InputManager::Instance();

	mTabText = new Texture("Spell Book", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	mSpellIcon[0] = new Texture("Magic/WindBolt.png");
	mSpellIcon[1] = new Texture("Magic/FrostBolt.png");
	mSpellIcon[2] = new Texture("Magic/EarthBolt.png");
	mSpellIcon[3] = new Texture("Magic/FireBolt.png");
	mSpellIcon[4] = new Texture("Magic/AirStrike.png");
	mSpellIcon[5] = new Texture("Magic/WaterStrike.png");
	mSpellIcon[6] = new Texture("Magic/TerraStrike.png");
	mSpellIcon[7] = new Texture("Magic/FlameStrike.png");
	mSpellIcon[8] = new Texture("Magic/HowlingBlast.png");
	mSpellIcon[9] = new Texture("Magic/IceBlast.png");
	mSpellIcon[10] = new Texture("Magic/MagicDart.png");
	mSpellIcon[11] = new Texture("Magic/RockBlast.png");
	mSpellIcon[12] = new Texture("Magic/Alchemy.png");
	mSpellIcon[13] = new Texture("Magic/PyroBlast.png");
	mSpellIcon[14] = new Texture("Magic/Conversion.png");
	mSpellIcon[15] = new Texture("Magic/Smite.png");
	mSpellIcon[16] = new Texture("Magic/CloudBurst.png");
	mSpellIcon[17] = new Texture("Magic/StormBurst.png");
	mSpellIcon[18] = new Texture("Magic/SeismicBurst.png");
	mSpellIcon[19] = new Texture("Magic/LavaBurst.png");

	int y = -24;
	for (int i = 0; i < 20; i++)
	{
		if (!(i % 4))
			y += 64;

		mSpellPos[i] = Vector2(509 + 64 * (i % 4), 251 + y);
		mSpellIcon[i]->Pos(mSpellPos[i]);
		mSpellIcon[i]->Scale(Vector2(3.0f, 3.0f));
	}

	mOutline = new Texture("RedOutline.png");
	mOutline->Scale(Vector2(3.0f, 3.0f));

	mSpellText = nullptr;
}

Magic::~Magic()
{
	mPlayer = nullptr;

	mInputManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	for (int i = 0; i < 20; i++)
	{
		delete mSpellBook[i];
		mSpellBook[i] = nullptr;

		delete mSpellIcon[i];
		mSpellIcon[i] = nullptr;
	}

	if (mSpellText != nullptr)
	{
		delete mSpellText;
		mSpellText = nullptr;
	}

	delete mOutline;
}

void Magic::Update()
{
	if (mInputManager->MouseButtonReleased(InputManager::left))
	{
		for (int i = 0; i < 20; i++)
		{
			if (mSpellIcon[i]->Intersects(mInputManager->MousePos()))
				setCurrentSpell(i);
		}
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			if (mInputManager->MousePos().Between(Vector2(mSpellPos[i].x - 32.0f, mSpellPos[i].y - 32.0f), 64.0f, 64.0f))
			{
				if (mSpellText == nullptr)
				{
					mSpellText = new Texture(mSpellBook[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = mSpellPos[i];
					mSpellText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mSpellText != nullptr))
	{
		delete mSpellText;
		mSpellText = nullptr;
	}
}

void Magic::Render()
{
	mTabText->Render();

	if (mPlayer->getAutoCast())
		mOutline->Render();

	for (int i = 0; i < 20; i++)
		mSpellIcon[i]->Render();

	if (mSpellText != nullptr)
		mSpellText->Render();
}

bool Magic::hasRunes()
{
	if (mSpellBook[currentSpell]->getName() == "Smite")
		if (mPlayer->equipment->getItem(3) == nullptr)
			return false;
		else if (mPlayer->equipment->getItem(3)->getId() != 569) //God Staff
			return false;
		else if (mSpellBook[currentSpell]->getName() == "Magic Dart")
			if (mPlayer->equipment->getItem(3) == nullptr)
				return false;
			else if (mPlayer->equipment->getItem(3)->getId() != 571) //Slayer's Staff
				return false;

	std::vector<Item> runes = mSpellBook[currentSpell]->getRunes();

	if (mPlayer->equipment->getItem(3) != nullptr)
	{
		switch (mPlayer->equipment->getItem(3)->getId())
		{
		case 561: //Air staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 539) runes.erase(runes.begin() + i);
			break;
		case 563: //Water staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 541) runes.erase(runes.begin() + i);
			break;
		case 565: //Earth staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 542) runes.erase(runes.begin() + i);
			break;
		case 567: //Fire staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 543) runes.erase(runes.begin() + i);
			break;
		default:
			break;
		}
	}

	return mPlayer->inventory->hasItems(runes);
}

void Magic::useRunes()
{
	std::vector<Item> runes = mSpellBook[currentSpell]->getRunes();

	if (mPlayer->equipment->getItem(3) != nullptr)
	{
		switch (mPlayer->equipment->getItem(3)->getId())
		{
		case 561: //Air staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 539) runes.erase(runes.begin() + i);
			break;
		case 563: //Water staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 541) runes.erase(runes.begin() + i);
			break;
		case 565: //Earth staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 542) runes.erase(runes.begin() + i);
			break;
		case 567: //Fire staff
			for (int i = 0; i < runes.size(); i++) if (runes[i].getId() == 543) runes.erase(runes.begin() + i);
			break;
		default:
			break;
		}
	}

	return mPlayer->inventory->remove(runes);
}

void Magic::setCurrentSpell(int spell)
{
	if (spell < 0 || spell > 20)
		return;
	else if (mPlayer->skills->getLevel(magic) < mSpellBook[spell]->getRequirement())
		return;
	else if (spell == 12) //Alchemy
	{
		//Add code later?
	}
	else if (spell == 14) //Conversion
	{
		currentSpell = spell;
		mPlayer->setAutoCast(false);
		if (hasRunes())
		{
			for (int i = 0; i < 20; i++)
			{
				if (mPlayer->inventory->getSlot(i) != nullptr)
				{
					if (mPlayer->inventory->getSlot(i)->getId() == 549) //Bones
						mPlayer->inventory->replace(Item(517, 1), i);
					else if (mPlayer->inventory->getSlot(i)->getId() == 551) //Big Bones
						mPlayer->inventory->replace(Item(517, 1), i);
					else if (mPlayer->inventory->getSlot(i)->getId() == 553) //Dragon Bones
						mPlayer->inventory->replace(Item(517, 1), i);
					else if (mPlayer->inventory->getSlot(i)->getId() == 555) //Lava Dragon Bones
						mPlayer->inventory->replace(Item(517, 1), i);
				}
			}
			mPlayer->skills->addExperience(mSpellBook[spell]->getBaseExp(), magic);
			useRunes();
		}
	}
	else if (currentSpell == spell)
	{
		if (mPlayer->getAutoCast())
			mPlayer->toggleAutoCast();
		else if (hasRunes())
			mPlayer->toggleAutoCast();
	}
	else
	{
		currentSpell = spell;
		if (hasRunes())
			mPlayer->setAutoCast(true);
		else
			mPlayer->setAutoCast(false);
	}
	mOutline->Pos(mSpellPos[currentSpell]);
	mPlayer->setCombatStance(mPlayer->getCombatStance());
}

void Magic::castSpell()
{
	useRunes();
	//if (!hasRunes())
	//player->setAutoCast(false);
}