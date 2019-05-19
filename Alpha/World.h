#ifndef WORLD_H
#define WORLD_H

#include "Woodcutting.h"
#include "Mining.h"
#include "Fishing.h"
#include "Runecrafting.h"

struct Flax
{
	Flax(Vector2 vec)
	{
		mTex = new Texture("/Items/Flax.png");
		mTex->Scale(Vector2(2.0f, 2.0f));
		mTex->Pos(vec);

		picked = false;
		mTimer = 0;
	}

	~Flax()
	{
		delete mTex;
		mTex = nullptr;
	}

	Texture *mTex;
	bool picked;
	int mTimer;
};

class World
{
public:
	World(Player*);
	~World();

	void Update();
	void Render();

private:
	enum LOCATION { world, woodcutting, mining, fishing, runecrafting };
	LOCATION mCurrentLocation;

	Player* mPlayer;

	InputManager *mInputManager;

	Texture *mBackground;

	Texture *mWoodcuttingIcon;
	Texture *mMiningIcon;
	Texture *mFishingIcon;
	Texture* mRunecraftingIcon;

	Woodcutting *mWoodcutting;
	Mining *mMining;
	Fishing *mFishing;
	Runecrafting *mRunecrafting;

	Flax *mFlax[12];
	
	Texture* mEscapeButton;
	bool exitWorld;
public:
	bool LeaveWorld() { if (exitWorld) { exitWorld = false; return true; } else return false; }
};

#endif