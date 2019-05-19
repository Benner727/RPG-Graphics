#ifndef PRAYERBOOK_H
#define PRAYERBOOK_H

#include "Aura.h"
#include "Texture.h"
#include "InputManager.h"

class Player;

class PrayerBook
{
public:
	PrayerBook(Player*);
	~PrayerBook();

	void Update();
	void Render();

private:
	Player *player;

	InputManager* mInputManager;

	Texture* mTabText;

	Aura *aura[20];
	Vector2 mPrayerPos[20];
	Texture *mPrayerIcon[20];
	Texture* mOutline[20];

	Texture* mPrayerText;
	Vector2 mTextPos;

	bool activated[20];

	bool canToggle(int);

public:
	void toggle(int);
	void toggleAll() { for (int i = 0; i < 20; i++) activated[i] = false; }

	bool getActivated(int);
	double getPrayerDrain();
};

#endif