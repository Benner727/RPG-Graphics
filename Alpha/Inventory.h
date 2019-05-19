#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

class Player;

class Inventory : public GameEntity
{
public:
	Inventory(Player*);
	~Inventory();

	void Update();
	void Render();
private:
	Player* player;

	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Texture* mTabText;

	Vector2 mInventoryPos[20];

	Item* mInventory[20];
	int mSelectedSlot;

	Texture* mSelectedItem;
	int mPrevSelected;

	Texture* mRightClick[7];
	Texture* mAltBackground;
	bool mRightClicked;

	Texture* mItemText;
	Vector2 mTextPos;

public:
	void use();

	bool canAdd(Item);
	void add(Item);

	void remove(int);
	void remove(int, int);
	void remove(std::vector<Item>);

	void eat(int);
	void drink(int);

	void replace(Item, int);

	void clear();

	Item* getSlot(int);
	int getFreeSlots();

	bool hasItem(int);
	bool hasItem(int, int);
	bool hasItems(std::vector<Item>);

	int hasAmount(int);

	void removeItem(int);
	void removeItem(int, int);

	void swap(int);

	void save();
	void load();
};

#endif