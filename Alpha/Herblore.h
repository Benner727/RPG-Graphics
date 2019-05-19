#ifndef HERBLORE_H
#define HERBLORE_H

class Player;

class Herblore
{
public:
	Herblore(Player*);

	~Herblore();

private:
	Player *player;

public:
	void brew(int, int);
	bool decant(int, int);
};

#endif