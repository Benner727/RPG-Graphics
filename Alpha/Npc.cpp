#include "Npc.h"


Npc::Npc(int _id)
{
	id = _id;

	mDefinitionLoader = DefinitionLoader::Instance();
	npcDefinition = mDefinitionLoader->GetNpcDefinition(id);

	mTexture = Texture("Monsters/" + npcDefinition->getTexture());
	mTexture.Scale(Vector2(1.5f, 1.5f));

	hitpoints = npcDefinition->getHitpoints();
	delay = 1;
}


Npc::~Npc()
{
	mDefinitionLoader = nullptr;

	npcDefinition = nullptr;
}

bool Npc::Intersects(Vector2 vec)
{
	return mTexture.Intersects(vec);
}

void Npc::Render()
{
	mTexture.Pos(Pos());
	mTexture.Render();
}