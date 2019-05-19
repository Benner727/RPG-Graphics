#ifndef MINING_H
#define MINING_H

#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"

struct Ore
{
public:
	Ore(int id, Vector2 vec)
	{
		mIndex = id;
		mDepleted = false;
		mTimer = 0;

		switch (id)
		{
		case 0: //Essence
			mTex = new Texture("Entities/EssenceOre.png");
			mTex->Pos(vec);
			break;
		case 1: //Copper
			mTex = new Texture("Entities/CopperOre.png");
			mTex->Pos(vec);
			break;
		case 2: //Tin
			mTex = new Texture("Entities/TinOre.png");
			mTex->Pos(vec);
			break;
		case 3: //Iron
			mTex = new Texture("Entities/IronOre.png");
			mTex->Pos(vec);
			break;
		case 4: //Coal
			mTex = new Texture("Entities/CoalOre.png");
			mTex->Pos(vec);
			break;
		case 5: //Gold
			mTex = new Texture("Entities/GoldOre.png");
			mTex->Pos(vec);
			break;
		case 6: //Gem
			mTex = new Texture("Entities/GemOre.png");
			mTex->Pos(vec);
			break;
		case 7: //Mithril
			mTex = new Texture("Entities/MithrilOre.png");
			mTex->Pos(vec);
			break;
		case 8: //Adamant
			mTex = new Texture("Entities/AdamantOre.png");
			mTex->Pos(vec);
			break;
		case 9: //Rune
			mTex = new Texture("Entities/RuneOre.png");
			mTex->Pos(vec);
			break;
		}
		mTex->Scale(Vector2(4.5f, 4.5f));
	}

	~Ore()
	{
		delete mTex;
		mTex = nullptr;
	}

	int mIndex;
	Texture *mTex;
	bool mDepleted;
	int mTimer;
};

class Mining
{
public:
	Mining(Player*);
	~Mining();

	void Update();
	void Render();

private:
	Player *mPlayer;

	InputManager *mInputManager;
	AudioManager *mAudioManager;

	Texture *mBackground;

	Texture *mMineText;

	Texture* mEscapeButton;
	bool exitMining;

	Ore* mOres[10];

	void OreUpdate();

	int mCurrentOre;
	bool mMining;
	void mine();

public:
	bool LeaveMining() { if (exitMining) { exitMining = mMining = false; return true; } else return false; }
};

#endif