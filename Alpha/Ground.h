#ifndef GROUND_H
#define GROUND_H

class Player;

#include "Item.h"
#include "InputManager.h"
#include <random>

class Ground
{
public:
	Ground(Player*);
	~Ground();

	void Update();
	void Render();

	void AddLoot(int);
private:
	std::default_random_engine gen;
	std::uniform_int_distribution<int> roll;

	Player* mPlayer;

	InputManager* mInputManager;

	DefinitionLoader* mDefinitionLoader;

	Vector2 mGroundPos[15];

	Item* mGround[15];
	int mSelectedSlot;

	Texture* mItemText;
	Vector2 mTextPos;

	bool CanAdd(Item);
	void AddItem(Item);
	void AddLoot(std::vector<Item>);
	void PickUp(int);

	std::vector<Item> GetDrop(int);
};

#endif