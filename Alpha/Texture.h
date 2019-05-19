#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:
	SDL_Texture* mTex;

	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

public:
	Texture();
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontpath, int size, SDL_Color);
	~Texture();

	virtual void Render();

	bool Intersects(Vector2);
};

#endif