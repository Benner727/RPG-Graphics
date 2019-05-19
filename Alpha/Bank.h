#ifndef BANK_H
#define BANK_H

#include "Item.h"
#include "Timer.h"
#include "InputManager.h"

class Player;

class Bank
{
public:
	Bank(Player*);
	~Bank();

	void Update();
	void Render();
private:
	Player *mPlayer;

	Timer* mTimer;
	InputManager* mInputManager;

	std::vector<Item*> mBank;
	int mSelectedSlot;

	Texture* mTabText;
	Texture* mBackground;

	Texture* mItemText;
	Vector2 mTextPos;

	Texture* mRightClick[4];
	Texture* mAltBackground;
	bool mRightClicked;
	bool inventory;

	Texture* mUnnoteText;
	Texture* mNoteText;
	Texture* mTextButton;
	bool mNote;

	Texture* mEscapeButton;
	bool leave;

	void withdraw(int);
	void withdraw(int, int);

	void swap(int, int);

public:
	void deposit(int);
	void deposit(int, int);
	void deposit(Item);

	bool LeaveBank() { if (leave) { leave = false; return true; } else return false; }

	void save();
	void load();
};

#endif