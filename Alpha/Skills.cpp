#include "Skills.h"
#include "Player.h"
#include "PrayerBook.h"
#include "Magic.h"

#include <iostream>
#include <fstream>
#include <sstream>


const int EXP_FOR_LEVEL[] = { 0, 83, 174, 276, 388, 512, 650, 801, 969, 1154, 1358,
1584, 1833, 2107, 2411, 2746, 3115, 3523, 3973, 4470, 5018, 5624, 6291, 7028, 7842,
8740, 9730, 10824, 12031, 13363, 14833, 16456, 18247, 20224, 22406, 24815, 27473, 30408,
33648, 37224, 41171, 45529, 50339, 55649, 61512, 67983, 75127, 83014, 91721, 101333,
111945, 123660, 136594, 150872, 166636, 184040, 203254, 224466, 247886, 273742, 302288,
333804, 368599, 407015, 449428, 496254, 547953, 605032, 668051, 737627, 814445, 899257,
992895, 1096278, 1210421, 1336443, 1475581, 1629200, 1798808, 1986068, 2192818, 2421087,
2673114, 2951373, 3258594, 3597792, 3972294, 4385776, 4842295, 5346332, 5902831,
6517253, 7195629, 7944614, 8771558, 9684577, 10692629, 11805606, 13034431, 14391160 };

Skills::Skills(Player *p)
{
	player = p;

	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	skills[hitpoints].experience = 1154;
	skills[hitpoints].effectiveLevel = 10;
	skills[hitpoints].level = 10;
	for (int i = 1; i < 17; i++)
	{
		skills[i].experience = 0;
		skills[i].level = 1;
		skills[i].effectiveLevel = 1;
	}

	mTabText = new Texture("Skills", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	mCurrentSkill = 0;
}

Skills::~Skills()
{
	player = nullptr;

	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	for (int i = 0; i < 17; i++)
	{
		delete mSkillText[i];
		mSkillText[i] = nullptr;
	}

	for (int i = 0; i < mExpText.size(); i++)
	{
		delete mExpText[i];
		mExpText[i] = nullptr;
	}

	mExpText.clear();
}

void Skills::Update()
{
	std::string name[] = { "Hitpoints", "Attack", "Strength", "Defense", "Ranged", "Prayer", "Magic", "Woodcut",
		"Fletching", "Fishing", "Cooking", "Mining", "Smithing", "Herblore", "Crafting", "Runecraft", "Slayer" };

	for (int i = 0; i < 17; i++)
	{
		delete mSkillText[i];
		mSkillText[i] = new Texture(name[i] + ":  " + std::to_string(skills[i].effectiveLevel) + " / " + std::to_string(skills[i].level), "Romulus.ttf", 16, { 69, 79, 79 });

		if (i < 9)
			mSkillText[i]->Pos(Vector2(540, 285 + (i * 35)));
		else
			mSkillText[i]->Pos(Vector2(680, 285 + ((i - 9) * 35)));
	}

	for (int i = 0; i < 17; i++)
	{
		if (mInputManager->MousePos().Between(Vector2(mSkillText[i]->Pos().x - 52.0f, mSkillText[i]->Pos().y - 8.0f), 104.0f, 16.0f))
		{
			mCurrentSkill = i;
			SetExperience(i);
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mSkillText[mCurrentSkill]->Pos().x - 52.0f, mSkillText[mCurrentSkill]->Pos().y - 8.0f), 104.0f, 16.0f) && mExpText.size()))
	{
		for (int i = 0; i < mExpText.size(); i++)
		{
			delete mExpText[i];
			mExpText[i] = nullptr;
		}

		mExpText.clear();
	}
}

void Skills::Render()
{
	mTabText->Render();

	for (int i = 0; i < 17; i++)
		mSkillText[i]->Render();

	if (mExpText.size())
	{
		for (int i = 0; i < mExpText.size(); i++)
			mExpText[i]->Render();
	}
}

void Skills::SetExperience(int skill)
{
	for (int i = 0; i < mExpText.size(); i++)
	{
		delete mExpText[i];
		mExpText[i] = nullptr;
	}

	mExpText.clear();

	std::string str = std::to_string(skills[skill].experience);
	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mExpText.push_back(new Texture(str.substr(i, 1), "Romulus.ttf", 16, { 250, 250, 250 }));

		if (skill < 9)
			mExpText[i]->Pos(Vector2(565 - 8.0f * (lastIndex - i), 300 + (skill * 35)));
		else
			mExpText[i]->Pos(Vector2(708 - 8.0f * (lastIndex - i), 300 + ((skill - 9) * 35)));
	}
}

int Skills::getExpForLevel(int skill)
{
	if (getLevel(skill) == 99)
		return getExperience(skill);

	return EXP_FOR_LEVEL[getLevel(skill)] - getExperience(skill);
}

void Skills::heal(int amount)
{
	if (skills[hitpoints].effectiveLevel > skills[hitpoints].level)
		return;
	else skills[hitpoints].effectiveLevel += amount;

	if (skills[hitpoints].effectiveLevel > skills[hitpoints].level)
		skills[hitpoints].effectiveLevel = skills[hitpoints].level;
}

void Skills::subHitpoints(int amount)
{
	skills[hitpoints].effectiveLevel -= amount;
	if (skills[hitpoints].effectiveLevel < 1)
		skills[hitpoints].effectiveLevel = 0;

	if (!skills[hitpoints].effectiveLevel && !player->getInCombat())
		player->respawn();
}

void Skills::drainSkill(int amount, int skill)
{
	skills[skill].effectiveLevel -= amount;

	if (skills[skill].effectiveLevel < 1 && skill == prayer)
	{
		skills[skill].effectiveLevel = 0;
		player->prayerBook->toggleAll();
	}
	else if (skills[skill].effectiveLevel < 1)
		skills[skill].effectiveLevel = 1;
}

void Skills::boostSkill(int add, double modifier, int skill, int type)
{
	if (type && skills[skill].effectiveLevel >= skills[skill].level)
		return;
	else if (type && skills[skill].effectiveLevel < skills[skill].level)
	{
		skills[skill].effectiveLevel += skills[skill].level * modifier + add;

		if (skills[skill].effectiveLevel >= skills[skill].level)
			skills[skill].effectiveLevel = skills[skill].level;
		return;
	}
	else
		skills[skill].effectiveLevel += skills[skill].level * modifier + add;

	if (skills[skill].effectiveLevel > (skills[skill].level + skills[skill].level * modifier + add) && (modifier || add))
		skills[skill].effectiveLevel = (skills[skill].level + skills[skill].level * modifier + add);

	if (skills[skill].effectiveLevel < 0)
		skills[skill].effectiveLevel = 0;
}

void Skills::update()
{
	static double prayerDrain = 0;
	static int interval = 0;
	interval++;

	prayerDrain += player->prayerBook->getPrayerDrain();

	if (prayerDrain > 1.0)
	{
		drainSkill((int)prayerDrain, prayer);
		prayerDrain -= (int)prayerDrain;
	}

	if (interval == 100)
	{
		for (int i = 0; i < 7; i++)
		{
			if (i != prayer)
			{
				if (skills[i].effectiveLevel < skills[i].level)
					skills[i].effectiveLevel++;
				else if (skills[i].effectiveLevel > skills[i].level)
					skills[i].effectiveLevel--;
			}
		}
		interval = 0;
	}
}

void Skills::restore(int skill)
{
	skills[skill].effectiveLevel = skills[skill].level;
}

void Skills::addExperience(int exp, int skill)
{
	double ratio = (double)skills[skill].effectiveLevel / skills[skill].level;
	int oLevel = skills[skill].level;

	//BONUS EXPERIENCE
	exp *= 3;

	skills[skill].experience += exp;

	for (int i = 0; i < 100; i++)
	{
		if (skills[skill].experience < EXP_FOR_LEVEL[i])
		{
			skills[skill].level = i;

			if (skills[skill].effectiveLevel < skills[skill].level)
				skills[skill].effectiveLevel = (skills[skill].level * ratio);

			break;
		}
	}

	if (skills[skill].level > 99) skills[skill].level = 99;

	if (skills[skill].effectiveLevel < skills[skill].level)
		skills[skill].effectiveLevel = (skills[skill].level * ratio);

	if (skills[skill].level > oLevel)
		mAudioManager->PlaySFX("Level_Up.wav", 0, 1);
}

void Skills::addCombatExperience(int dmg)
{
	switch (player->getCombatStance())
	{
	case 0:
		addExperience(dmg, hitpoints);
		addExperience(dmg * 4, attack);
		break;
	case 1:
		addExperience(dmg, hitpoints);
		addExperience(dmg * 4, strength);
		break;
	case 2:
		addExperience(dmg, hitpoints);
		addExperience(dmg * 4, defense);
		break;
	case 3:
		addExperience(dmg, hitpoints);
		addExperience(dmg, attack);
		addExperience(dmg, strength);
		addExperience(dmg, defense);
		break;
	case 4:
		addExperience(dmg, hitpoints);
		addExperience(dmg * 4, ranged);
		break;
	case 5:
		addExperience(dmg, hitpoints);
		addExperience(dmg * 2, ranged);
		addExperience(dmg * 2, defense);
		break;
	case 6:
		addExperience(dmg, hitpoints);
		addExperience((dmg * 2) + player->magic->getCurrentSpell()->getBaseExp(), magic);
		break;
	}
}

void Skills::reset()
{
	for (int i = 0; i < 17; i++)
		skills[i].effectiveLevel = skills[i].level;
}

void Skills::save()
{
	std::ofstream outFile("save.txt", std::ios::app);

	outFile << "Skills" << std::endl;

	for (int i = 0; i < 17; i++)
		outFile << skills[i].effectiveLevel << " " << skills[i].level << " " << skills[i].experience << " " << std::endl;

	outFile << std::endl;

	outFile.close();
}

void Skills::load()
{
	std::ifstream infile("save.txt");
	int cur, max, exp,
		i = 0;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (line == "Skills")
		{
			while (infile >> cur >> max >> exp)
			{
				skills[i].effectiveLevel = cur;
				skills[i].level = max;
				skills[i].experience = exp;
				i++;
			}
		}

	}

	infile.close();
}