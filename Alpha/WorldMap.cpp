#include "WorldMap.h"

#include "DungeonDefinition.h"
#include "Bank.h"
#include "Slayer.h"

WorldMap::WorldMap(Player *player)
{
	mPlayer = player;

	mAudioManager = AudioManager::Instance();
	mInputManager = InputManager::Instance();

	mDefinitionLoader = DefinitionLoader::Instance();

	mBackground = new Texture("MapBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 301));

	for (int i = 0; i < 6; i++)
	{
		mCities[i] = new Texture("CityIcon.png");
		mCities[i]->Scale(Vector2(2.0f, 2.0f));
	}

	mCities[0]->Pos(Vector2(275.0f, 522.0f)); //Lumbridge
	mCities[1]->Pos(Vector2(348.0f, 253.0f)); //Varrock
	mCities[2]->Pos(Vector2(223.0f, 351.0f)); //Falador
	mCities[3]->Pos(Vector2(143.0f, 254.0f)); //Seers' Village
	mCities[4]->Pos(Vector2(69.0f, 351.0f)); //Ardougne
	mCities[5]->Pos(Vector2(78.0f, 520.0f)); //Karamja

	std::string cityNames[] = { "Lumbridge", "Varrock", "Falador", "Seers' Village", "Ardougne", "Karamja" };
	for (int i = 0; i < 6; i++)
	{
		mLabels[i] = new Texture(cityNames[i], "alagard.ttf", 18, { 0, 0, 0 });
		mLabels[i]->Pos(mCities[i]->Pos());
	}

	mCitySelected = -1;
	mSelected = -1;

	mCombat = nullptr;
	mMarket = new Market(mPlayer);
	mWorld = new World(mPlayer);
	mWorkshop = new Workshop(mPlayer);

	mBankIcon = new Texture("BankIcon.png");
	mBankIcon->Pos(Vector2(380.0f, 35.0f));
	mBankIcon->Scale(Vector2(4.0f, 4.0f));
	
	mMarketIcon = new Texture("ShopIcon.png");
	mMarketIcon->Pos(Vector2(316.0f, 35.0f));
	mMarketIcon->Scale(Vector2(4.0f, 4.0f));

	mWorldIcon = new Texture("WorldIcon.png");
	mWorldIcon->Pos(Vector2(252.0f, 35.0f));
	mWorldIcon->Scale(Vector2(4.0f, 4.0f));

	mWorkshopIcon = new Texture("WorkshopIcon.png");
	mWorkshopIcon->Pos(Vector2(188.0f, 35.0f));
	mWorkshopIcon->Scale(Vector2(4.0f, 4.0f));

	mSlayerIcon = new Texture("SlayerIcon.png");
	mSlayerIcon->Pos(Vector2(124.0f, 35.0f));
	mSlayerIcon->Scale(Vector2(4.0f, 4.0f));

	mSaveIcon = new Texture("SaveIcon.png");
	mSaveIcon->Pos(Vector2(47.0f, 35.0f));
	mSaveIcon->Scale(Vector2(3.9f, 4.0f));

	mCurrentState = city;
}


WorldMap::~WorldMap()
{
	mPlayer->save();
	mPlayer = nullptr;

	mAudioManager = nullptr;
	mInputManager = nullptr;

	mDefinitionLoader = nullptr;

	delete mBackground;
	mBackground = nullptr;

	for (int i = 0; i < 6; i++)
	{
		delete mCities[i];
		mCities[i] = nullptr;

		delete mLabels[i];
		mLabels[i] = nullptr;
	}

	if (mCombat != nullptr)
	{
		delete mCombat;
		mCombat = nullptr;
	}

	delete mMarket;
	mMarket = nullptr;
	
	delete mWorld;
	mWorld = nullptr;

	delete mWorkshop;
	mWorkshop = nullptr;

	ClearMenu();

	delete mBankIcon;
	mBankIcon = nullptr;

	delete mMarketIcon;
	mMarketIcon = nullptr;

	delete mWorldIcon;
	mWorldIcon = nullptr;

	delete mWorkshopIcon;
	mWorkshopIcon = nullptr;

	delete mSlayerIcon;
	mSlayerIcon = nullptr;

	delete mSaveIcon;
	mSaveIcon = nullptr;
}

void WorldMap::Update()
{
	if (mCurrentState == city || mCurrentState == dungeon || mCurrentState == monster)
	{
		if (mBankIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = bank;
			mPlayer->setInBank(true);
		}
		else if (mMarketIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = market;
		}
		else if (mWorldIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = world;
		}
		else if (mWorkshopIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = workshop;
		}
		else if (mSlayerIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = slayer;
		}
		else if (mSaveIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mPlayer->save();
		}
	}

	switch (mCurrentState)
	{
	case city:
		mCitySelected = -1;

		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			for (int i = 0; i < 6; i++)
			{
				if (mCities[i]->Intersects(mInputManager->MousePos()))
				{
					mCitySelected = i;
					CreateDungeonMenu(i);
					mCurrentState = dungeon;
				}
			}

			if (mCurrentState != dungeon)
				mCurrentState = city;
		}
		break;
	case dungeon:
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			for (int i = 0; i < mList.size(); i++)
			{
				if (mList[i]->Intersects(mInputManager->MousePos()))
				{
					mSelected = i;
					CreateMonsterMenu(mDungeons[i]);
					mCurrentState = monster;
				}
			}

			if (mCurrentState != monster)
				mCurrentState = city;
		}
		break;
	case monster:
		if (mInputManager->MouseButtonPressed(InputManager::left))
		{
			for (int i = 0; i < mList.size(); i++)
			{
				if (mList[i]->Intersects(mInputManager->MousePos()))
				{
					mCombat = new Combat(mPlayer, mDefinitionLoader->GetDungeonDefinition(mDungeons[mSelected])->getNpcId()[i]);
					mCurrentState = battle;
				}
			}

			if (mCurrentState != battle)
				mCurrentState = city;
		}
		break;
	case battle:
		mCombat->Update();
		
		if (mCombat->ExitCombat())
		{
			delete mCombat;
			mCombat = nullptr;

			mCurrentState = city;
		}
		break;
	case bank:
		mPlayer->bank->Update();

		if (mPlayer->bank->LeaveBank())
		{
			mCurrentState = city;
			mPlayer->setInBank(false);
		}
		break;
	case market:
		mMarket->Update();

		if (mMarket->LeaveMarket())
			mCurrentState = city;
		break;
	case world:
		mWorld->Update();

		if (mWorld->LeaveWorld())
			mCurrentState = city;
		break;
	case workshop:
		mWorkshop->Update();

		if (mWorkshop->LeaveWorkshop())
			mCurrentState = city;
		break;
	case slayer:
		mPlayer->slayer->Update();

		if (!mSlayerIcon->Intersects(mInputManager->MousePos()) && mInputManager->MouseButtonPressed(InputManager::left))
		{
			mCurrentState = city;
		}
	}
}

void WorldMap::Render()
{
	mBackground->Render();

	for (int i = 0; i < 6; i++)
	{
		if (mCitySelected != i)
			mCities[i]->Render();
	}

	mBankIcon->Render();
	mMarketIcon->Render();
	mWorldIcon->Render();
	mWorkshopIcon->Render();
	mSlayerIcon->Render();
	mPlayer->slayer->getCurrentSlayerTask();
	mSaveIcon->Render();

	switch (mCurrentState)
	{
	case city:
		for (int i = 0; i < 6; i++)
		{
			if (mCities[i]->Intersects(mInputManager->MousePos()))
				mLabels[i]->Render();
		}
		break;
	case dungeon:
		RenderMenu();
		break;
	case monster:
		RenderMenu();
		break;
	case battle:
		mCombat->Render();
		break;
	case bank:
		mPlayer->bank->Render();
		break;
	case market:
		mMarket->Render();
		break;
	case world:
		mWorld->Render();
		break;
	case workshop:
		mWorkshop->Render();
		break;
	case slayer:
		mPlayer->slayer->Render();
		break;
	}
}


void WorldMap::CreateDungeonMenu(int id)
{
	ClearMenu();
	mDungeons.clear();

	switch (id)
	{
	case 0:
		mDungeons.push_back(2);
		mDungeons.push_back(4);
		mDungeons.push_back(11);
		mDungeons.push_back(17);
		break;
	case 1:
		mDungeons.push_back(16);
		mDungeons.push_back(23);
		mDungeons.push_back(15);
		mDungeons.push_back(1);
		mDungeons.push_back(24);
		break;
	case 2:
		mDungeons.push_back(22);
		mDungeons.push_back(10);
		mDungeons.push_back(12);
		mDungeons.push_back(18);
		break;
	case 3:
		mDungeons.push_back(19);
		mDungeons.push_back(21);
		mDungeons.push_back(9);
		mDungeons.push_back(0);
		break;
	case 4:
		mDungeons.push_back(14);
		mDungeons.push_back(13);
		mDungeons.push_back(8);
		mDungeons.push_back(5);
		break;
	case 5:
		mDungeons.push_back(6);
		mDungeons.push_back(3);
		mDungeons.push_back(7);
		mDungeons.push_back(20);
		break;
	}

	for (int i = 0; i < mDungeons.size(); i++)
	{
		mList.push_back(new Texture(mDefinitionLoader->GetDungeonDefinition(mDungeons[i])->getName(), "alagard.ttf", 15, { 0, 0, 0 }));
		mList[i]->Pos(Vector2(mCities[mCitySelected]->Pos().x, (mCities[mCitySelected]->Pos().y - 15) + 15 * i));
	}
}

void WorldMap::CreateMonsterMenu(int id)
{
	ClearMenu();

	int y = 15;
	if (mDefinitionLoader->GetDungeonDefinition(id)->getNpcId().size() > 8)
		y = 60;
	else if (mDefinitionLoader->GetDungeonDefinition(id)->getNpcId().size() > 4)
		y = 30;

	for (int i = 0; i < mDefinitionLoader->GetDungeonDefinition(id)->getNpcId().size(); i++)
	{
		mList.push_back(new Texture(mDefinitionLoader->GetNpcDefinition(mDefinitionLoader->GetDungeonDefinition(id)->getNpcId()[i])->getName(), "alagard.ttf", 15, { 0, 0, 0 }));
		mList[i]->Pos(Vector2(mCities[mCitySelected]->Pos().x, (mCities[mCitySelected]->Pos().y - y) + 15 * i));
	}
}

void WorldMap::RenderMenu()
{
	for (int i = 0; i < mList.size(); i++)
		mList[i]->Render();
}

void WorldMap::ClearMenu()
{
	for (int i = 0; i < mList.size(); i++)
		delete mList[i];

	mList.clear();
}