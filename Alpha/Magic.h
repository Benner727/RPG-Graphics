#include "SpellBook.h"

#include "Texture.h"
#include "InputManager.h"

#ifndef MAGIC_H
#define MAGIC_H

class Player;

class Magic
{
public:
	Magic(Player*);
	~Magic();

	void Update();
	void Render();
private:
	Player* mPlayer;

	InputManager* mInputManager;

	Texture* mTabText;

	Vector2 mSpellPos[20];
	static SpellBook *mSpellBook[20];
	Texture *mSpellIcon[20];

	int currentSpell;
	Texture *mOutline;

	Texture* mSpellText;
	Vector2 mTextPos;

	void useRunes();

public:
	bool hasRunes();

	void setCurrentSpell(int);

	SpellBook* getCurrentSpell() { return mSpellBook[currentSpell]; }

	void castSpell();
};

#endif