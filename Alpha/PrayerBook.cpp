#include "PrayerBook.h"
#include "Player.h"
#include "Skills.h"
#include "Equipment.h"


PrayerBook::PrayerBook(Player* _player)
{
	player = _player;

	mInputManager = InputManager::Instance();

	for (int i = 0; i < 20; i++)
		activated[i] = false;

	mTabText = new Texture("Prayer Book", "alagard.ttf", 24, { 50, 50, 50 });
	mTabText->Pos(Vector2(610, 240));

	aura[0] = new Aura("Thick Skin", 1, 12.0, DEFENSE);
	aura[1] = new Aura("Burst of Strength", 4, 12.0, STRENGTH);
	aura[2] = new Aura("Clarity of Thought", 7, 12.0, ATTACK);
	aura[3] = new Aura("Sharp Eye", 8, 12.0, MAGE_RANGE);
	aura[4] = new Aura("Mystic Will", 9, 12.0, MAGE_RANGE);
	aura[5] = new Aura("Rock Skin", 10, 8.0, DEFENSE);
	aura[6] = new Aura("Superhuman Strength", 13, 8.0, STRENGTH);
	aura[7] = new Aura("Improved Reflexes", 16, 8.0, ATTACK);
	aura[8] = new Aura("Hawk Eye", 26, 6.0, MAGE_RANGE);
	aura[9] = new Aura("Mystic Lore", 27, 6.0, MAGE_RANGE);
	aura[10] = new Aura("Steel Skin", 28, 6.0, DEFENSE);
	aura[11] = new Aura("Ultimate Strength", 31, 6.0, STRENGTH);
	aura[12] = new Aura("Incredible Reflexes", 34, 6.0, ATTACK);
	aura[13] = new Aura("Protect from Magic", 37, 4.0, OVER_HEAD);
	aura[14] = new Aura("Protect from Range", 40, 4.0, OVER_HEAD);
	aura[15] = new Aura("Protect from Melee", 43, 4.0, OVER_HEAD);
	aura[16] = new Aura("Eagle Eye", 44, 6.0, MAGE_RANGE);
	aura[17] = new Aura("Mystic Might", 45, 6.0, MAGE_RANGE);
	aura[18] = new Aura("Chivalry", 60, 3.0, COMBAT);
	aura[19] = new Aura("Piety", 70, 3.0, COMBAT);

	mPrayerIcon[0] = new Texture("Prayer/ThickSkin.png");
	mPrayerIcon[1] = new Texture("Prayer/BurstOfStrength.png");
	mPrayerIcon[2] = new Texture("Prayer/ClarityOfThought.png");
	mPrayerIcon[3] = new Texture("Prayer/SharpEye.png");
	mPrayerIcon[4] = new Texture("Prayer/MysticWill.png");
	mPrayerIcon[5] = new Texture("Prayer/RockSkin.png");
	mPrayerIcon[6] = new Texture("Prayer/SuperhumanStrength.png");
	mPrayerIcon[7] = new Texture("Prayer/ImprovedReflexes.png");
	mPrayerIcon[8] = new Texture("Prayer/HawkEye.png");
	mPrayerIcon[9] = new Texture("Prayer/MysticLore.png");
	mPrayerIcon[10] = new Texture("Prayer/SteelSkin.png");
	mPrayerIcon[11] = new Texture("Prayer/UltimateStrength.png");
	mPrayerIcon[12] = new Texture("Prayer/IncredibleReflexes.png");
	mPrayerIcon[13] = new Texture("Prayer/ProtectFromMagic.png");
	mPrayerIcon[14] = new Texture("Prayer/ProtectFromRange.png");
	mPrayerIcon[15] = new Texture("Prayer/ProtectFromMelee.png");
	mPrayerIcon[16] = new Texture("Prayer/EagleEye.png");
	mPrayerIcon[17] = new Texture("Prayer/MysticMight.png");
	mPrayerIcon[18] = new Texture("Prayer/Chivalry.png");
	mPrayerIcon[19] = new Texture("Prayer/Piety.png");

	int y = -24;
	for (int i = 0; i < 20; i++)
	{
		if (!(i % 4))
			y += 64;

		mPrayerPos[i] = Vector2(509 + 64 * (i % 4), 251 + y);
		mPrayerIcon[i]->Pos(mPrayerPos[i]);
		mPrayerIcon[i]->Scale(Vector2(3.0f, 3.0f));

		mOutline[i] = new Texture("RedOutline.png");
		mOutline[i]->Pos(mPrayerPos[i]);
		mOutline[i]->Scale(Vector2(3.0f, 3.0f));
	}

	mPrayerText = nullptr;
}


PrayerBook::~PrayerBook()
{
	player = nullptr;

	mInputManager = nullptr;

	delete mTabText;
	mTabText = nullptr;

	for (int i = 0; i < 20; i++)
	{
		delete aura[i];
		aura[i] = nullptr;

		delete mPrayerIcon[i];
		mPrayerIcon[i] = nullptr;

		delete mOutline[i];
		mOutline[i] = nullptr;
	}

	if (mPrayerText != nullptr)
	{
		delete mPrayerText;
		mPrayerText = nullptr;
	}
}

void PrayerBook::Update()
{
	if (mInputManager->MouseButtonReleased(InputManager::left))
	{
		for (int i = 0; i < 20; i++)
		{
			if (mPrayerIcon[i]->Intersects(mInputManager->MousePos()))
				toggle(i);
		}
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			if (mInputManager->MousePos().Between(Vector2(mPrayerPos[i].x - 32.0f, mPrayerPos[i].y - 32.0f), 64.0f, 64.0f))
			{
				if (mPrayerText == nullptr)
				{
					mPrayerText = new Texture(aura[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = mPrayerPos[i];
					mPrayerText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mPrayerText != nullptr))
	{
		delete mPrayerText;
		mPrayerText = nullptr;
	}
}

void PrayerBook::Render()
{
	mTabText->Render();

	for (int i = 0; i < 20; i++)
	{
		if (activated[i])
			mOutline[i]->Render();
		mPrayerIcon[i]->Render();
	}

	if (mPrayerText != nullptr)
		mPrayerText->Render();
}

bool PrayerBook::canToggle(int slot)
{
	if (!player->skills->getEffect(prayer))
		return false;
	else if (slot < 0 || slot > 20)
		return false;

	if (aura[slot]->getLevel() <= player->skills->getLevel(prayer))
		return true;
	else
		return false;
}

void PrayerBook::toggle(int slot)
{
	if (canToggle(slot))
	{
		if (!activated[slot])
		{
			if (aura[slot]->getAuraType() == COMBAT)
			{
				for (int i = 0; i < 20; i++)
				{
					if (aura[i]->getAuraType() != OVER_HEAD)
						activated[i] = false;
				}
			}
			else if (aura[slot]->getAuraType() != OVER_HEAD)
			{
				for (int i = 0; i < 20; i++)
				{
					if (aura[i]->getAuraType() == aura[slot]->getAuraType() || aura[i]->getAuraType() == COMBAT)
						activated[i] = false;
				}
			}
			else
				for (int i = 0; i < 20; i++)
					if (aura[i]->getAuraType() == OVER_HEAD)
						activated[i] = false;
		}
		activated[slot] = !activated[slot];
	}
}

bool PrayerBook::getActivated(int slot)
{
	if (slot < 0 || slot > 20)
		return false;
	else
		return activated[slot];
}

double PrayerBook::getPrayerDrain()
{
	double prayerDrain = 0;

	for (int i = 0; i < 20; i++)
		if (activated[i])
			prayerDrain += 1 / aura[i]->getDrainRate();

	if (prayerDrain)
		prayerDrain *= 1.0 - ((double)player->equipment->getBonus(7) / 61.0);

	return prayerDrain;
}