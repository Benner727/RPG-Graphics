#include "Slayer.h"
#include "Player.h"
#include "Skills.h"
#include "Inventory.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<SlayerTask*> Slayer::turael = {
	new SlayerTask("Banshees", 15,{ 5 }),
	new SlayerTask("Bats", 1,{ 41, 42 }),
	new SlayerTask("Birds", 1,{ 38, 78 }),
	new SlayerTask("Bears", 1,{ 43 }),
	new SlayerTask("Cave bugs", 7,{ 2, 3 }),
	new SlayerTask("Cave slime", 10,{ 6 }),
	new SlayerTask("Cows", 1,{ 39 }),
	new SlayerTask("Crawling hands", 5,{ 0, 1 }),
	new SlayerTask("Desert lizards", 22,{ 8 }),
	new SlayerTask("Dogs", 1,{ 79, 80 }),
	new SlayerTask("Dwarves", 1,{ 49, 50 }),
	new SlayerTask("Ghosts", 1,{ 46 }),
	new SlayerTask("Goblins", 1,{ 44 }),
	new SlayerTask("Icefiends", 1,{ 53 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Minotaurs", 1,{ 92 }),
	new SlayerTask("Monkeys", 1,{ 84, 85, 86 }),
	new SlayerTask("Rats", 1,{ 40 }),
	new SlayerTask("Scorpions", 1,{ 51 }),
	new SlayerTask("Skeletons", 1,{ 47 }),
	new SlayerTask("Spiders", 1,{ 87, 88 }),
	new SlayerTask("Wolves", 1,{ 52 }),
	new SlayerTask("Zombies", 1,{ 48 })
};

std::vector<SlayerTask*> Slayer::mazchna = {
	new SlayerTask("Banshees", 15,{ 5 }),
	new SlayerTask("Bats", 1,{ 41, 42 }),
	new SlayerTask("Bears", 1,{ 43 }),
	new SlayerTask("Catablepons", 1,{ 89 }),
	new SlayerTask("Cave bugs", 7,{ 2, 3 }),
	new SlayerTask("Cave crawlers", 10,{ 4 }),
	new SlayerTask("Cave slimes", 17,{ 6 }),
	new SlayerTask("Cockatrice", 25,{ 9 }),
	new SlayerTask("Crawling hands", 5,{ 0, 1 }),
	new SlayerTask("Desert lizards", 22,{ 8 }),
	new SlayerTask("Dogs", 1,{ 79, 80 }),
	new SlayerTask("Earth warriors", 1,{ 90 }),
	new SlayerTask("Flesh crawlers", 1,{ 91 }),
	new SlayerTask("Ghosts", 1,{ 46 }),
	new SlayerTask("Ghouls", 1,{ 93 }),
	new SlayerTask("Hill giants", 1,{ 58 }),
	new SlayerTask("Hobgoblins", 1,{ 45 }),
	new SlayerTask("Ice warriors", 1,{ 54 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Killerwatts", 37,{ 14 }),
	new SlayerTask("Pyrefiends", 30,{ 10 }),
	new SlayerTask("Rockslugs", 20,{ 7 }),
	new SlayerTask("Scoprions", 1,{ 51 }),
	new SlayerTask("Shades", 1,{ 94 }),
	new SlayerTask("Skeletons", 1,{ 47 }),
	new SlayerTask("Vampires", 15,{ 56 }),
	new SlayerTask("Wall beasts", 35,{ 13 }),
	new SlayerTask("Wolves", 1,{ 52 }),
	new SlayerTask("Zombies", 1,{ 48 })
};

std::vector<SlayerTask*> Slayer::vannaka = {
	new SlayerTask("Abyssal demons", 85,{ 26 }),
	new SlayerTask("Aberrant spectres", 60,{ 35 }),
	new SlayerTask("Ankous", 1,{ 95 }),
	new SlayerTask("Banshees", 15,{ 5 }),
	new SlayerTask("Basilisks", 40,{ 16 }),
	new SlayerTask("Blue dragons", 1,{ 71 }),
	new SlayerTask("Bloodvelds", 50,{ 21 }),
	new SlayerTask("Bronze dragons", 1,{ 74 }),
	new SlayerTask("Cave bugs", 7,{ 2, 3 }),
	new SlayerTask("Cave crawlers", 10,{ 4 }),
	new SlayerTask("Cave slimes", 17,{ 6 }),
	new SlayerTask("Cockatrices", 25,{ 9 }),
	new SlayerTask("Crawling hands", 5,{ 0, 1 }),
	new SlayerTask("Crocodiles", 1,{ 96 }),
	new SlayerTask("Dagannoths", 1,{ 103 }),
	new SlayerTask("Desert lizards", 22,{ 8 }),
	new SlayerTask("Dust devils", 65,{ 28 }),
	new SlayerTask("Earth warriors", 1,{ 90 }),
	new SlayerTask("Fever spiders", 42,{ 18 }),
	new SlayerTask("Fire giants", 1,{ 62 }),
	new SlayerTask("Gargoyles", 75,{ 32 }),
	new SlayerTask("Ghouls", 1,{ 93 }),
	new SlayerTask("Green dragons", 1,{ 70 }),
	new SlayerTask("Harpie bug swarms", 33,{ 12 }),
	new SlayerTask("Hellhounds", 1,{ 98 }),
	new SlayerTask("Hill giants", 1,{ 58 }),
	new SlayerTask("Hobgoblins", 1,{ 45 }),
	new SlayerTask("Ice giants", 1,{ 55 }),
	new SlayerTask("Ice warrior", 1,{ 54 }),
	new SlayerTask("Infernal mages", 45,{ 19 }),
	new SlayerTask("Jellies", 52,{ 22 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Killerwatts", 37,{ 14 }),
	new SlayerTask("Kurasks", 70,{ 30 }),
	new SlayerTask("Lesser demons", 1,{ 63 }),
	new SlayerTask("Mogres", 32,{ 11 }),
	new SlayerTask("Molanisks", 39,{ 15 }),
	new SlayerTask("Moss giants", 1,{ 59 }),
	new SlayerTask("Nechryaels", 80,{ 33 }),
	new SlayerTask("Ogres", 15,{ 60 }),
	new SlayerTask("Pyrefiends", 30,{ 10 }),
	new SlayerTask("Rockslugs", 20,{ 7 }),
	new SlayerTask("Shadow warriors", 1,{ 99 }),
	new SlayerTask("Spiritual creatures", 63,{ 28, 29, 34 }),
	new SlayerTask("Terror dogs", 40,{ 17 }),
	new SlayerTask("Trolls", 1,{ 101 }),
	new SlayerTask("Turoths", 55,{ 23 }),
	new SlayerTask("Vampires", 1,{ 56 }),
	new SlayerTask("Wall beasts", 35,{ 13 }),
	new SlayerTask("Werewolf", 1,{ 57 })
};

std::vector<SlayerTask*> Slayer::chaeldar = {
	new SlayerTask("Abyssal demons", 85,{ 26 }),
	new SlayerTask("Aberrant spectres", 60,{ 35 }),
	new SlayerTask("Aviansies", 1,{ 102 }),
	new SlayerTask("Banshees", 15,{ 5 }),
	new SlayerTask("Basilisks", 40,{ 16 }),
	new SlayerTask("Black dragons", 1,{ 73 }),
	new SlayerTask("Bloodvelds", 50,{ 21 }),
	new SlayerTask("Blue dragons", 1,{ 71 }),
	new SlayerTask("Cave crawlers", 10,{ 4 }),
	new SlayerTask("Cave horrors", 58,{ 25 }),
	new SlayerTask("Cave slimes", 17,{ 6 }),
	new SlayerTask("Cockatrices", 25,{ 9 }),
	new SlayerTask("Dagannoths", 1,{ 103 }),
	new SlayerTask("Fever spiders", 42,{ 18 }),
	new SlayerTask("Gargoyles", 75,{ 32 }),
	new SlayerTask("Dust devils", 65,{ 28 }),
	new SlayerTask("Earth warriors", 1,{ 90 }),
	new SlayerTask("Fire giants", 1,{ 62 }),
	new SlayerTask("Harpie bug swarms", 33,{ 12 }),
	new SlayerTask("Infernal mages", 45,{ 19 }),
	new SlayerTask("Jellies", 52,{ 22 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Kurasks", 70,{ 30 }),
	new SlayerTask("Lesser demons", 1,{ 63 }),
	new SlayerTask("Rockslugs", 20,{ 7 }),
	new SlayerTask("Trolls", 1,{ 101 }),
	new SlayerTask("Turoths", 55,{ 23 }),
	new SlayerTask("Wall beasts", 35,{ 13 }),
	new SlayerTask("Desert lizards", 22,{ 8 }),
	new SlayerTask("Hellhounds", 1,{ 98 }),
	new SlayerTask("Bronze dragons", 1,{ 74 }),
	new SlayerTask("Mutated zygomites", 57,{ 24 }),
	new SlayerTask("Molanisks", 39,{ 15 }),
	new SlayerTask("Mogres", 32,{ 11 }),
	new SlayerTask("Nechryaels", 80,{ 33 }),
	new SlayerTask("Iron dragons", 1,{ 75 }),
	new SlayerTask("Pyrefiends", 20,{ 10 }),
	new SlayerTask("Spiritual creatures", 63,{ 27, 29, 34 }),
	new SlayerTask("Shadow warriors", 1,{ 99 }),
	new SlayerTask("Skeletal wyverns", 72,{ 31 }),
	new SlayerTask("Steel dragons", 1,{ 76 })
};

std::vector<SlayerTask*> Slayer::nieve = {
	new SlayerTask("Aberrant spectres", 60,{ 26 }),
	new SlayerTask("Abyssal demons", 85,{ 35 }),
	new SlayerTask("Ankous", 1,{ 95 }),
	new SlayerTask("Aviansies", 1,{ 102 }),
	new SlayerTask("Black demons", 1,{ 65 }),
	new SlayerTask("Black dragons", 1,{ 73 }),
	new SlayerTask("Bloodvelds", 50,{ 21 }),
	new SlayerTask("Blue dragons", 1,{ 71 }),
	new SlayerTask("Cave horrors", 58,{ 25 }),
	new SlayerTask("Dagannoths", 1,{ 103 }),
	new SlayerTask("Dark beasts", 90,{ 36 }),
	new SlayerTask("Dust devils", 65,{ 28 }),
	new SlayerTask("Fire giants", 1,{ 62 }),
	new SlayerTask("Gargoyles", 75,{ 32 }),
	new SlayerTask("Greater demons", 1,{ 64 }),
	new SlayerTask("Hellhounds", 1,{ 98 }),
	new SlayerTask("Iron dragons", 1,{ 75 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Kurasks", 70,{ 30 }),
	new SlayerTask("Mithril dragons", 1,{ 77 }),
	new SlayerTask("Mutated zygomites", 57,{ 24 }),
	new SlayerTask("Nechryaels", 80,{ 33 }),
	new SlayerTask("Red dragons", 1,{ 72 }),
	new SlayerTask("Skeletal wyverns", 72,{ 72 }),
	new SlayerTask("Smoke devils", 93,{ 37 }),
	new SlayerTask("Spiritual creatures", 63,{ 27, 29, 34 }),
	new SlayerTask("Steel dragons", 1,{ 76 }),
	new SlayerTask("Trolls", 1,{ 101 }),
	new SlayerTask("Turoths", 55,{ 23 }),
	new SlayerTask("TzHaars", 1,{ 66, 67, 68, 69 })
};

std::vector<SlayerTask*> Slayer::duradel = {
	new SlayerTask("Aberrant spectres", 60,{ 26 }),
	new SlayerTask("Abyssal demons", 85,{ 35 }),
	new SlayerTask("Ankous", 1,{ 95 }),
	new SlayerTask("Aviansies", 1,{ 102 }),
	new SlayerTask("Black demons", 1,{ 65 }),
	new SlayerTask("Black dragons", 1,{ 73 }),
	new SlayerTask("Bloodvelds", 50,{ 21 }),
	new SlayerTask("Blue dragons", 1,{ 71 }),
	new SlayerTask("Cave horrors", 58,{ 25 }),
	new SlayerTask("Dagannoths", 1,{ 103 }),
	new SlayerTask("Dark beasts", 90,{ 36 }),
	new SlayerTask("Dust devils", 65,{ 28 }),
	new SlayerTask("Fire giants", 1,{ 62 }),
	new SlayerTask("Gargoyles", 75,{ 32 }),
	new SlayerTask("Greater demons", 1,{ 64 }),
	new SlayerTask("Hellhounds", 1,{ 98 }),
	new SlayerTask("Iron dragons", 1,{ 75 }),
	new SlayerTask("Kalphites", 1,{ 81, 82, 83 }),
	new SlayerTask("Kurasks", 70,{ 30 }),
	new SlayerTask("Mithril dragons", 1,{ 77 }),
	new SlayerTask("Mutated zygomites", 57,{ 24 }),
	new SlayerTask("Nechryaels", 80,{ 33 }),
	new SlayerTask("Red dragons", 1,{ 72 }),
	new SlayerTask("Skeletal wyverns", 72,{}),
	new SlayerTask("Smoke devils", 93,{ 37 }),
	new SlayerTask("Spiritual creatures", 63,{ 27, 29, 34 }),
	new SlayerTask("Steel dragons", 1,{ 76 }),
	new SlayerTask("Trolls", 1,{ 101 }),
	new SlayerTask("TzHaars", 1,{ 66, 67, 68, 69 }),
	new SlayerTask("Waterfiends", 1,{ 104 })
};


Slayer::Slayer(Player* _player)
{
	player = _player;
	
	mInputManager = InputManager::Instance();

	mSlayerMasters[0] = new Texture("Turael", "alagard.ttf", 16, { 255, 255, 255 });
	mSlayerMasters[1] = new Texture("Mazchna", "alagard.ttf", 16, { 255, 255, 255 });
	mSlayerMasters[2] = new Texture("Vannaka", "alagard.ttf", 16, { 255, 255, 255 });
	mSlayerMasters[3] = new Texture("Chaeldar", "alagard.ttf", 16, { 255, 255, 255 });
	mSlayerMasters[4] = new Texture("Nieve", "alagard.ttf", 16, { 255, 255, 255 });
	mSlayerMasters[5] = new Texture("Duradel", "alagard.ttf", 16, { 255, 255, 255 });

	for (int i = 0; i < 6; i++)
		mSlayerMasters[i]->Pos(Vector2(125, 80 + 16 * i));

	mBackground = new Texture("BlankBackground.png");
	mBackground->Pos(Vector2(125.0f, 120.0f));
	mBackground->Scale(Vector2(4.0f, 6.75f));

	mTask = nullptr;
	task = "";

	currentTask = nullptr;
	currentSlot = -1;
	currentMaster = -1;
	amount = 0;
	tasksCompleted = 0;
	slayerPoints = 0;
	taskPoints = 0;
}


Slayer::~Slayer()
{
	player = nullptr;

	mInputManager = nullptr;

	currentTask = nullptr;
	delete currentTask;

	for (int i = 0; i < 6; i++)
	{

		delete mSlayerMasters[i];
		mSlayerMasters[i] = nullptr;
	}

	delete mBackground;
	mBackground = nullptr;

	delete mTask;
	mTask = nullptr;
}


void Slayer::Update()
{
	if (mInputManager->MouseButtonPressed(InputManager::left))
	{
		for (int i = 0; i < 6; i++)
		{
			if (mSlayerMasters[i]->Intersects(mInputManager->MousePos()))
				getNewSlayerTask(i);
		}
	}
}

void Slayer::Render()
{
	mBackground->Render();
	for (int i = 0; i < 6; i++)
		mSlayerMasters[i]->Render();
}

void Slayer::completeTask()
{
	switch (currentMaster)
	{
	case 0:
		tasksCompleted++;
		taskPoints = 0;
		break;
	case 1:
		tasksCompleted++;

		if (tasksCompleted % 50 == 0)
			taskPoints = 15;
		else if (tasksCompleted % 10 == 0)
			taskPoints = 5;
		else
			taskPoints = 2;
		break;
	case 2:
		tasksCompleted++;

		if (tasksCompleted % 50 == 0)
			taskPoints = 60;
		else if (tasksCompleted % 10 == 0)
			taskPoints = 20;
		else
			taskPoints = 4;
		break;
	case 3:
		tasksCompleted++;

		if (tasksCompleted % 50 == 0)
			taskPoints = 150;
		else if (tasksCompleted % 10 == 0)
			taskPoints = 50;
		else
			taskPoints = 10;
		break;
	case 4:
		tasksCompleted++;

		if (tasksCompleted % 50 == 0)
			taskPoints = 180; if (tasksCompleted % 10 == 0)
			taskPoints = 60;
			else
				taskPoints = 12;
		break;
	case 5:
		tasksCompleted++;

		if (tasksCompleted % 50 == 0)
			taskPoints = 225;
		else if (tasksCompleted % 10 == 0)
			taskPoints = 75;
		else
			taskPoints = 15;
		break;
	default:
		taskPoints = 0;
		break;
	}

	slayerPoints += taskPoints;

	currentTask = nullptr;
	currentSlot = -1;
	currentMaster = -1;
	amount = 0;
}

bool Slayer::hasTask()
{
	return currentTask != nullptr;
}

void Slayer::getCurrentSlayerTask()
{
	std::string _task;

	if (hasTask())
		_task = "Your assigned to kill " + currentTask->getName() + "; only " + std::to_string(amount) + " to go.";
	else
		_task = "You currently have no slayer task.";

	if (task != _task)
	{
		task = _task;

		if (mTask != nullptr)
			delete mTask;

		mTask = new Texture(task, "alagard.ttf", 17, { 225, 0, 0 });
		mTask->Pos(Vector2(205.0f, 115.0f));
	}
	mTask->Render();
}

bool Slayer::isTask(int id)
{
	if (hasTask())
	{
		for (int i = 0; i < currentTask->getId().size(); i++)
			if (id == currentTask->getId()[i])
				return true;
	}
	return false;
}

void Slayer::getNewSlayerTask(int id)
{
	if (currentTask != nullptr)
	{
		if (currentMaster <= id)
			return;
		else
			tasksCompleted = 0;
	}

	do
	{
		switch (id)
		{
		case 0:
			currentSlot = rand() % turael.size();
			currentTask = turael[currentSlot];
			amount = rand() % 36 + 15;
			currentMaster = id;
			break;
		case 1:
			currentSlot = rand() % mazchna.size();
			currentTask = mazchna[currentSlot];
			amount = rand() % 36 + 15;
			currentMaster = id;
			break;
		case 2:
			currentSlot = rand() % vannaka.size();
			currentTask = vannaka[currentSlot];
			amount = rand() % 46 + 40;
			currentMaster = id;
			break;
		case 3:
			currentSlot = rand() % chaeldar.size();
			currentTask = chaeldar[currentSlot];
			amount = rand() % 51 + 80;
			currentMaster = id;
			break;
		case 4:
			currentSlot = rand() % nieve.size();
			currentTask = nieve[currentSlot];
			amount = rand() % 66 + 120;
			currentMaster = id;
			break;
		case 5:
			currentSlot = rand() % duradel.size();
			currentTask = duradel[currentSlot];
			amount = rand() % 121 + 130;
			currentMaster = id;
			break;
		default:
			return;
			break;
		}
	} while (currentTask->getLevel() > player->skills->getLevel(slayer));
}

void Slayer::checkKill(Npc* npc)
{
	if (isTask(npc->getId()))
	{
		player->skills->addExperience(npc->getNpcDefinition().getHitpoints(), slayer);
		amount--;

		if (!amount)
			completeTask();
	}
}

void Slayer::save()
{
	std::ofstream outFile("save.txt", std::ios::app);

	outFile << "Slayer" << std::endl;

	outFile << currentSlot << " " << currentMaster << " " << amount << " " << tasksCompleted << " " << slayerPoints << std::endl << std::endl;

	outFile.close();
}

void Slayer::load()
{
	std::ifstream infile("save.txt");

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		if (line == "Slayer")
			infile >> currentSlot >> currentMaster >> amount >> tasksCompleted >> slayerPoints;
	}

	infile.close();

	switch (currentMaster)
	{
	case 0:
		currentTask = turael[currentSlot];
		break;
	case 1:
		currentTask = mazchna[currentSlot];
		break;
	case 2:
		currentTask = vannaka[currentSlot];
		break;
	case 3:
		currentTask = chaeldar[currentSlot];
		break;
	case 4:
		currentTask = nieve[currentSlot];
		break;
	case 5:
		currentTask = duradel[currentSlot];
		break;
	default:
		return;
		break;
	}
}