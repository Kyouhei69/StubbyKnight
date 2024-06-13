#pragma once

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst,SDL_RendererFlip flip);
	
};