#ifndef NPC_H
#define NPC_H

#include "Texture.h"
#include "DefinitionLoader.h"

class Npc : public GameEntity
{
public:
	Npc(int);
	~Npc();

private:
	int id,
		hitpoints,
		delay;

	NpcDefinition* npcDefinition;

	DefinitionLoader *mDefinitionLoader;

	Texture mTexture;

public:
	int getId() const { return id; }
	int getHitpoints() const { return hitpoints; }
	int getDelay() const { return delay; }

	NpcDefinition& getNpcDefinition() const { return *npcDefinition; }

	void subHitpoints(int i) { hitpoints -= i; if (hitpoints < 1) hitpoints = 0; }
	void addHitpoints(int i) { hitpoints += i; if (hitpoints > npcDefinition->getHitpoints()) hitpoints = npcDefinition->getHitpoints(); }
	void tickDelay() { delay--; if (delay == -1) delay = npcDefinition->getAttackSpeed(); }

	bool Intersects(Vector2);
	void Render();
};

#endif