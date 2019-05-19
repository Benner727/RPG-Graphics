#include "Bank.h"

#include "Player.h"
#include "Inventory.h"

#include <fstream>
#include <sstream>

Bank::Bank(Player *player)
{
	mPlayer = player;

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mSelectedSlot = -1;
	mItemText = nullptr;

	mTabText = new Texture("Bank", "alagard.ttf", 72, { 25, 25, 25 });
	mTabText->Pos(Vector2(205, 35));

	mBackground = new Texture("BankBackground.png");
	mBackground->Scale(Vector2(3.25f, 2.9f));
	mBackground->Pos(Vector2(207, 300));

	mRightClick[0] = new Texture("  10   ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[1] = new Texture("  100  ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[2] = new Texture("  1000 ", "Romulus.ttf", 16, { 255, 255, 255 });
	mRightClick[3] = new Texture("  All  ", "Romulus.ttf", 16, { 255, 255, 255 });
	
	mAltBackground = new Texture("AltBackground.png");
	mAltBackground->Scale(Vector2(3.0f, 4.0f));

	bool mRightClicked = false;

	mUnnoteText = new Texture("Normal", "Romulus.ttf", 16, { 255, 255, 255 });
	mUnnoteText->Pos(Vector2(379.0f, 19.0f));
	mNoteText = new Texture("Noted", "Romulus.ttf", 16, { 255, 255, 255 });
	mNoteText->Pos(Vector2(379.0f, 54.0f));
	mTextButton = new Texture("BankOption.png");
	mTextButton->Pos(Vector2(379.0f, 35.0f));
	mTextButton->Scale(Vector2(4.1f, 4.1f));
	mNote = false;

	mEscapeButton = new Texture("X_Button.png");
	mEscapeButton->Pos(Vector2(32, 32));

	leave = false;

	deposit(Item(516, 30)); //Coins
}

Bank::~Bank()
{
	mPlayer = nullptr;

	mTimer = nullptr;
	mInputManager = nullptr;

	delete mTabText;
	delete mBackground;

	for (auto it = mBank.begin(); it != mBank.end(); ++it)
		delete *it;
	mBank.clear();

	for (int i = 0; i < 4; i++)
	{
		delete mRightClick[i];
		mRightClick[i] = nullptr;
	}

	delete mAltBackground;
	mAltBackground = nullptr;

	if (mItemText != nullptr)
	{
		delete mItemText;
		mItemText = nullptr;
	}

	delete mUnnoteText;
	delete mNoteText;
	delete mTextButton;

	delete mEscapeButton;
	mEscapeButton = nullptr;
}

void Bank::Update()
{
	static Vector2 prevPos;

	static unsigned int mStartTicks = 0;
	static unsigned int mElapsedTicks = 0;

	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		if (mRightClicked)
		{
			if (mSelectedSlot > -1 && mSelectedSlot < mBank.size())
			{
				for (int i = 0; i < 4; i++)
				{
					if (mRightClick[i]->Intersects(mInputManager->MousePos()))
					{
						switch (i)
						{
						case 0:
							withdraw(mSelectedSlot, 10);
							break;
						case 1:
							withdraw(mSelectedSlot, 100);
							break;
						case 2:
							withdraw(mSelectedSlot, 1000);
							break;
						case 3:
							withdraw(mSelectedSlot, mBank[mSelectedSlot]->getAmount());
							break;
						}
						break;
					}
				}
			}

			mSelectedSlot = -1;
			mRightClicked = false;
		}
		else if (mBank.size())
		{
			for (int i = 0; i < mBank.size(); i++)
			{
				if (mBank[i]->Intersects(mInputManager->MousePos()))
				{
					mStartTicks = SDL_GetTicks();
					mSelectedSlot = i;
					prevPos = mBank[i]->Pos();
				}
			}
		}

		if (mUnnoteText->Intersects(mInputManager->MousePos()))
		{
			mTextButton->Rotation(0);
			mNote = false;
		}
		else if (mNoteText->Intersects(mInputManager->MousePos()))
		{
			mTextButton->Rotation(180);
			mNote = true;
		}
	}
	else if (mInputManager->MouseButtonPressed(InputManager::right))
	{
		if (mBank.size())
		{
			for (int i = 0; i < mBank.size(); i++)
			{
				if (mBank[i]->Intersects(mInputManager->MousePos()))
				{
					mSelectedSlot = i;
					mRightClicked = true;

					for (int i = 0; i < 4; i++)
						mRightClick[i]->Pos(Vector2(mBank[mSelectedSlot]->Pos().x + 24, ((mBank[mSelectedSlot]->Pos().y - 16) + 12 * i)));

					mAltBackground->Pos(Vector2(mBank[mSelectedSlot]->Pos().x + 24, ((mBank[mSelectedSlot]->Pos().y - 16) + 12 * 1.5)));
				}
			}
		}
	}
	else if (mInputManager->MouseButtonDown(InputManager::left))
	{
		mElapsedTicks = SDL_GetTicks() - mStartTicks;

		if (mElapsedTicks > 100 && mSelectedSlot != -1)
			mBank[mSelectedSlot]->Pos(mInputManager->MousePos());
	}
	else if (mInputManager->MouseButtonReleased(InputManager::left))
	{
		if (mSelectedSlot != -1)
		{
			if (mElapsedTicks <= 100)
			{
				withdraw(mSelectedSlot);
			}
			else
			{
				if (mBank.size())
				{
					for (int i = 0; i < mBank.size(); i++)
					{
						if (mBank[i]->Intersects(mBank[mSelectedSlot]->Pos()) && mSelectedSlot != i)
						{
							swap(mSelectedSlot, i);
							mSelectedSlot = -1;
							return;
						}
					}
				}
				mBank[mSelectedSlot]->Pos(prevPos);
			}
		}
		mSelectedSlot = -1;
	}
	else
	{
		if (mBank.size() && !mRightClicked)
		{
			for (int i = 0; i < mBank.size(); i++)
			{
				if (mBank[i]->Intersects(mInputManager->MousePos()))
				{
					mItemText = new Texture(mBank[i]->getName(), "Romulus.ttf", 22, { 255, 140, 0 });
					mTextPos = mBank[i]->Pos();
					mItemText->Pos(mTextPos);
				}
			}
		}
	}

	if ((!mInputManager->MousePos().Between(Vector2(mTextPos.x - 32.0f, mTextPos.y - 32.0f), 64.0f, 64.0f) && mItemText != nullptr) || mInputManager->MouseButtonPressed(InputManager::left) || mRightClicked)
	{
		delete mItemText;
		mItemText = nullptr;
	}

	if (mInputManager->MouseButtonPressed(InputManager::left) && mEscapeButton->Intersects(mInputManager->MousePos()))
		leave = true;
}

void Bank::Render()
{
	mBackground->Render();
	mTabText->Render();

	if (mBank.size())
	{
		for (int i = 0; i < mBank.size(); i++)
			mBank[i]->Render();
	}

	if (mItemText != nullptr)
		mItemText->Render();

	if (mRightClicked)
	{
		mAltBackground->Render();

		for (int i = 0; i < 4; i++)
			mRightClick[i]->Render();
	}

	mTextButton->Render();
	mUnnoteText->Render();
	mNoteText->Render();

	mEscapeButton->Render();
}

void Bank::deposit(Item item)
{
	item.unNote();

	for (int i = 0; i < mBank.size(); i++)
	{
		if (mBank[i]->getId() == item.getId())
		{
			mBank[i]->add(item.getAmount());
			return;
		}
	}
	mBank.push_back(new Item(item.getId(), item.getAmount()));
	
	if (mBank.size())
	{
		int x = 0, y = 0;
		for (int i = 0; i < mBank.size(); i++)
		{
			mBank[i]->Pos(Vector2(48 + x, 128 + y));

			if (!((i + 1) % 5))
			{
				x = 0;
				y += 64;
			}
			else
				x += 80;
		}
	}
}

void Bank::deposit(int slot)
{
	if (mPlayer->inventory->getSlot(slot) != nullptr)
	{
		deposit(*mPlayer->inventory->getSlot(slot));
		mPlayer->inventory->remove(slot);
	}
}

void Bank::deposit(int slot, int amount)
{
	if (mPlayer->inventory->getSlot(slot) != nullptr)
	{
		Item item = *mPlayer->inventory->getSlot(slot);

		if (amount > mPlayer->inventory->hasAmount(item.getId()))
		{
			amount = mPlayer->inventory->hasAmount(item.getId());
			deposit(Item(item.getId(), mPlayer->inventory->hasAmount(item.getId())));
			mPlayer->inventory->removeItem(item.getId(), amount);
		}
		else if (amount > 0)
		{
			deposit(Item(item.getId(), amount));
			mPlayer->inventory->removeItem(item.getId(), amount);
		}
	}
}

void Bank::withdraw(int slot)
{
	if (mBank.size())
	{
		if (slot > -1 && slot < mBank.size())
		{
			if (mPlayer->inventory->canAdd(*mBank[slot]))
			{
				Item temp = Item(mBank[slot]->getId(), 1);
				if (mNote)
					temp.note();

				mPlayer->inventory->add(temp);

				mBank[slot]->remove();
				if (mBank[slot]->getAmount() < 1)
				{
					mBank.erase(mBank.begin() + slot);

					if (mBank.size())
					{
						int x = 0, y = 0;
						for (int i = 0; i < mBank.size(); i++)
						{
							mBank[i]->Pos(Vector2(48 + x, 128 + y));

							if (!((i + 1) % 5))
							{
								x = 0;
								y += 64;
							}
							else
								x += 80;
						}
					}
				}
			}
		}
	}
}

void Bank::withdraw(int slot, int amount)
{
	if (amount < 1)
		return;

	if (mBank.size())
	{
		if (slot > -1 && slot < mBank.size())
		{
			Item temp = Item(mBank[slot]->getId(), 1);
			if (mNote)
				temp.note();

			if (!temp.getItemDefinition()->isStackable())
			{
				while (mPlayer->inventory->canAdd(temp) && amount)
				{
					if (mBank[slot]->getAmount())
					{
						mPlayer->inventory->add(Item(temp.getId(), 1));
						amount--;
						mBank[slot]->remove();
					}
					else
						break;
				}
			}
			else
			{
				if (mPlayer->inventory->canAdd(temp))
				{
					if (mBank[slot]->getAmount() > amount)
					{
						mPlayer->inventory->add(Item(temp.getId(), amount));
						mBank[slot]->remove(amount);
					}
					else
					{
						mPlayer->inventory->add(Item(temp.getId(), mBank[slot]->getAmount()));
						mBank[slot]->remove(mBank[slot]->getAmount());
					}
				}
			}

			if (mBank[slot]->getAmount() < 1)
			{
				mBank.erase(mBank.begin() + slot);

				if (mBank.size())
				{
					int x = 0, y = 0;
					for (int i = 0; i < mBank.size(); i++)
					{
						mBank[i]->Pos(Vector2(48 + x, 128 + y));

						if (!((i + 1) % 5))
						{
							x = 0;
							y += 64;
						}
						else
							x += 80;
					}
				}
			}
		}
	}
}

void Bank::swap(int first_slot, int second_slot)
{
	if (first_slot < 0 || first_slot >(mBank.size() - 1))
		return;
	else if (second_slot < 0 || second_slot >(mBank.size() - 1))
		return;

	iter_swap(mBank.begin() + first_slot, mBank.begin() + second_slot);

	if (mBank.size())
	{
		int x = 0, y = 0;
		for (int i = 0; i < mBank.size(); i++)
		{
			mBank[i]->Pos(Vector2(48 + x, 128 + y));

			if (!((i + 1) % 5))
			{
				x = 0;
				y += 64;
			}
			else
				x += 80;
		}
	}
}

void Bank::save()
{
	std::ofstream outFile("save.txt", std::ios::app);

	outFile << "Bank" << std::endl;

	for (int i = 0; i < mBank.size(); i++)
	{
		outFile << *mBank[i];
	}

	outFile << std::endl;

	outFile.close();
}

void Bank::load()
{
	for (auto it = mBank.begin(); it != mBank.end(); ++it)
		delete *it;
	mBank.clear();

	std::ifstream infile("save.txt");

	int i;
	Item temp;
	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (line == "Bank")
		{
			while (infile >> temp)
			{
				mBank.push_back(new Item(temp.getId(), temp.getAmount()));
				if (mBank.back()->getItemDefinition()->isNote()) mBank.back()->unNote();
			}
		}
	}

	if (mBank.size())
	{
		int x = 0, y = 0;
		for (int i = 0; i < mBank.size(); i++)
		{
			mBank[i]->Pos(Vector2(48 + x, 128 + y));

			if (!((i + 1) % 5))
			{
				x = 0;
				y += 64;
			}
			else
				x += 80;
		}
	}

	infile.close();
}