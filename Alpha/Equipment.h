#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

class Player;

class Equipment : public GameEntity
{
public:
	Equipment(Player*);
	~Equipment();

	void Update();
	void Render();
private:
	Player *player;
	
	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Texture* mTabText;
	Texture* mBackground;

	Vector2 mEquipmentPos[11];

	Item *mEquipment[11];
	int mBonus[8];

	Texture* mItemText;
	Vector2 mTextPos;

	void calculateBonus();

public:
	bool canEquip(Item*);

	void unequip(int);
	void equip(int);

	bool hasAmmo();
	void useAmmo();

	void clear();
	void clearSlot(int);

	Item* getItem(int);
	int getBonus(int);

	void save();
	void load();
};

#endif