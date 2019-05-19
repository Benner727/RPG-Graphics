#ifndef SLAYER_H
#define SLAYER_H

#include "SlayerTask.h"
#include "Npc.h"
#include "Texture.h"
#include "InputManager.h"

class Player;

class Slayer
{
public:
	Slayer(Player*);
	~Slayer();

	void Update();
	void Render();
private:
	static std::vector<SlayerTask*> turael;
	static std::vector<SlayerTask*> mazchna;
	static std::vector<SlayerTask*> vannaka;
	static std::vector<SlayerTask*> chaeldar;
	static std::vector<SlayerTask*> nieve;
	static std::vector<SlayerTask*> duradel;

	Player* player;

	InputManager *mInputManager;

	Texture *mBackground;
	Texture *mSlayerMasters[6];
	Texture *mTask;
	std::string task;

	SlayerTask* currentTask;
	int amount, currentMaster, currentSlot,
		tasksCompleted,
		slayerPoints,
		taskPoints;

	void completeTask();
public:
	bool hasTask();
	void getCurrentSlayerTask();
	int getCurrentSlayerTaskId() { if (hasTask()) return currentTask->getId()[0]; }

	void getNewSlayerTask(int);

	bool isTask(int);
	void checkKill(Npc*);

	//void slayerShop();

	void save();
	void load();
};

#endif