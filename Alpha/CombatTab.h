#ifndef COMBATTAB_H
#define COMBATTAB_H

#include "Texture.h"
#include "InputManager.h"

class Player;

class CombatTab
{
public:
	CombatTab(Player*);
	~CombatTab();

	void Update();
	void Render();

private:
	Player* mPlayer;
	int mCurrentStyle;

	InputManager *mInputManager;

	Texture* mTabText;

	Texture* mCombatButton[4];
	Texture* mSelectedButton;

	Texture* mButtonText[4];

	void clear();
	void MeleeSetup();
	void RangedSetup();
	void MagicSetup();
};

#endif