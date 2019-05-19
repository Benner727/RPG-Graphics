#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "Combat.h"
#include "Market.h"
#include "World.h"
#include "Workshop.h"

class WorldMap
{
public:
	WorldMap(Player*);

	~WorldMap();

	void Update();
	void Render();
private:
	enum MENU { city, dungeon, monster, battle, bank, market, world, workshop, slayer };

	AudioManager* mAudioManager;
	InputManager* mInputManager;

	DefinitionLoader *mDefinitionLoader;

	Player* mPlayer;

	Texture* mBackground;

	Texture* mCities[6];
	Texture* mLabels[6];

	std::vector<Texture*> mList;
	std::vector<int> mDungeons;

	int mCitySelected;
	int mSelected;

	Combat* mCombat;
	Market* mMarket;
	World* mWorld;
	Workshop* mWorkshop;

	Texture* mBankIcon;
	Texture* mMarketIcon;
	Texture* mWorldIcon;
	Texture* mWorkshopIcon;
	Texture* mSlayerIcon;
	Texture* mSaveIcon;

	MENU mCurrentState;

	void CreateDungeonMenu(int);
	void CreateMonsterMenu(int);
	void RenderMenu();
	void ClearMenu();
};

#endif