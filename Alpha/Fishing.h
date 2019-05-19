#ifndef FISHING_H
#define FISHING

#include "Player.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

struct Spot
{
	Spot(int id, Vector2 vec)
	{
		mIndex = id;
		mTex = new AnimatedTexture("Entities/FishingSpot.png", 0, 0, 16, 16, 4, 3.0f, AnimatedTexture::horizontal);;
		mTex->Pos(vec);
		mTex->Scale(Vector2(4.0f, 4.0f));

		switch (mIndex)
		{
		case 0: //Small Net / Bait
			mNameText = new Texture("Small Net / Bait", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		case 1: //Lure / Bait
			mNameText = new Texture("Lure / Bait", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		case 2: //Cage / Harpoon
			mNameText = new Texture("Cage / Harpoon", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		case 3: //Big Net / Harpoon
			mNameText = new Texture("Big Net / Harpoon", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		case 4: //Harpoon / Small Net
			mNameText = new Texture("Harpoon / Small Net", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		case 5: //Big Net
			mNameText = new Texture("Big Net", "alagard.ttf", 16, { 255, 255, 0 });
			break;
		}
	}

	~Spot()
	{
		delete mTex;
		mTex = nullptr;

		delete mNameText;
		mNameText = nullptr;
	}

	int mIndex;
	AnimatedTexture *mTex;
	Texture* mNameText;
};

class Fishing
{
public:
	Fishing(Player*);
	~Fishing();

	void Update();
	void Render();
private:
	Player *mPlayer;

	InputManager *mInputManager;
	AudioManager *mAudioManager;

	Texture *mBackground;

	Texture* mEscapeButton;
	bool exitFishing;

	Spot* mSpots[6];

	void SpotUpdate();

	int mCurrentSpot;
	bool mFishing;
	void fish();

	int GetOption();

public:
	bool LeaveFishing() { if (exitFishing) { exitFishing = mFishing = false; return true; } else return false; }
};

#endif