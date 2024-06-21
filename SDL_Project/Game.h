#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


class AssetManager;
class ColliderComponent;
class Camera;

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

	
	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	//static std::vector<ColliderComponent*> colliders;
	static bool isRunning;

	//player variable
	//static bool left_down;
	static bool isShooting;

	static SDL_Rect camera;
	static AssetManager* assets;
	static Camera* cam;

	enum groupLabels :std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles,
		groupVisuals
	};

	static int GameTime;
	static bool CountGameTime;
	static int TotalGameTime;
	static int InitialTime;

private:
	float count = 0;
	
	SDL_Window* window;
	

};

