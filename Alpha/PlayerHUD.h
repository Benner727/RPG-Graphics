#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include "Player.h"
#include "CombatTab.h"
#include "InputManager.h"
#include "Timer.h"
#include "Texture.h"

class PlayerHUD : public GameEntity
{
public:
	PlayerHUD(Player*);

	~PlayerHUD();

	void Update();
	void Render();

private:
	enum TAB { combat, skill, inventory, equipment, prayer, magic };

	InputManager* mInputManager;

	Player* mPlayer;
	CombatTab* mCombatTab;

	Texture* mBackground;
	Texture* mNameText;

	Texture* mHPIcon;
	Texture* mHPBase;
	Texture* mHPOverlay;

	Texture* mPrayIcon;
	Texture* mPrayBase;
	Texture* mPrayOverlay;

	Texture* mTabOutline;

	Vector2 mTabPos;
	int mTabSelected;

	void SetBars();
	void RenderBars();
};

#endif