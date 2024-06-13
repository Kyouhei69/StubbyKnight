#pragma once
#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	
	static void AddTile(int srcX, int srcY, int xpos, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	float count = 0;
	bool isRunning;
	SDL_Window* window;
	

};

#endif //Game_hpp