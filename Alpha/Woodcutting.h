#ifndef WOODCUTTING_H
#define WOODCUTTING_H

#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"

struct Tree
{
public:
	Tree(int id, Vector2 vec)
	{
		mIndex = id;
		mFallen = false;
		mTimer = 0;

		switch (id)
		{
		case 0: //Normal
			mTex = new Texture("Entities/Tree.png");
			mTex->Pos(vec);
			break;
		case 1: //Oak
			mTex = new Texture("Entities/OakTree.png");
			mTex->Pos(vec);
			break;
		case 2: //Willow
			mTex = new Texture("Entities/WillowTree.png");
			mTex->Pos(vec);
			break;
		case 3: //Maple
			mTex = new Texture("Entities/MapleTree.png");
			mTex->Pos(vec);
			break;
		case 4: //Yew
			mTex = new Texture("Entities/YewTree.png");
			mTex->Pos(vec);
			break;
		case 5: //Magic
			mTex = new Texture("Entities/MagicTree.png");
			mTex->Pos(vec);
			break;
		}
		mTex->Scale(Vector2(4.0f, 4.0f));
	}

	~Tree()
	{
		delete mTex;
		mTex = nullptr;
	}

	int mIndex;
	Texture *mTex;
	bool mFallen;
	int mTimer;
};

class Woodcutting
{
public:
	Woodcutting(Player*);
	~Woodcutting();

	void Update();
	void Render();

private:
	Player *mPlayer;

	InputManager *mInputManager;
	AudioManager *mAudioManager;

	Texture *mBackground;

	Texture *mChopText;

	Texture* mEscapeButton;
	bool exitWoodcutting;

	Tree *mTrees[22];

	void TreeUpdate();

	int mCurrentTree;
	bool mChopping;
	void chop();

public:
	bool LeaveWoodcutting() { if (exitWoodcutting) { exitWoodcutting = mChopping = false; return true; } else return false; }
};

#endif