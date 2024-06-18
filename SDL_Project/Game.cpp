#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <cstdlib> 


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

//std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

bool Game::isShooting = false;
//bool Game::left_down = false;


auto& player(manager.addEntity());


//auto& wall(manager.addEntity());

//const char* mapfile = "Assets/terrain_ss.png";






Game::Game()
{

}
Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fulllscreen)
{
	int flags = 0;
	if (fulllscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsytem initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 140, 140, 140, 255);
			std::cout << "Renderer created" << std::endl;
		}
		
		isRunning = true;
	}

	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("player", "Assets/EditSheet/player1.png");
	assets->AddTexture("projectile", "Assets/proj_fire.png");
	assets->AddTexture("pVisual", "Assets/EditSheet/Heart.png");

	map = new Map("terrain", 2, 32);
	
	map->LoadMap("Assets/map.map", 25, 20);
	

	player.addComponent<TransformComponent>(500,640,60,60,1);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D newPos = playerPos + Vector2D(-32,-10);

	for (int i = 0; i < 5; i++)
	{
		newPos = playerPos + Vector2D(16, 0);
		assets->CreateVisual(newPos, 16, 16, 1, "pVisual");
		std::cout << "Creating Visual" << i << newPos << std::endl;
	}
	

	for (int i = 0; i < 5; i++)
	{
		int ub = 800, lb = 500;
		Vector2D enemyPos = Vector2D(((rand() % (ub - lb + 1)) + lb), ((rand() % (ub - lb + 1)) + lb));
		std::cout << enemyPos << std::endl;
		assets->CreateEnemy(enemyPos, 60, 60, 1, "player");
	}

	
	//assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 1, "projectile");
	//assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 1, "projectile");
	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 1, "projectile");
	

	
	/*
	* else {
		isRunning = false;
	}
	*/
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& visuals(manager.getGroup(Game::groupVisuals));

void Game::handleEvents()
{
	//left_down = false;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}

	
}


Vector2D checkPlayerPos(500,640);

void Game::update()
{
	//SDL_Rect enemyCol = enemy.getComponent<ColliderComponent>().collider;
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	

	manager.refresh();
	manager.update();

	

	//CHECKING PLAYER COLLISION WITH WALL
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
		
	}

	//CHECKING PROJECTILE COLLISION WITH WALLS
	for (auto& p : projectiles)
	{
		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, p->getComponent<ColliderComponent>().collider))
			{
				std::cout << "Hit Wall!" << std::endl;
				p->destroy();
			}
		}
	}
	
	//CHECKING ENEMY COLLISION WITH PROJECTILES
	for (auto& e : enemies)
	{
		for (auto& p : projectiles)
		{
			if (Collision::AABB(e->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				std::cout << "Hit enemy" << std::endl;
				
				e->destroy();
				p->destroy();
				
				//assets->CreateEnemy((playerPos-Vector2D(60,60)), 60, 60, 1, "player");
			}
		}
	}

	// CHECKING ENEMY COLLISION WITH WALL
	for (auto& e : enemies)
	{
		Vector2D enemyPos = e->getComponent<TransformComponent>().position;
		for (auto& c : colliders)
		{

			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, e->getComponent<ColliderComponent>().collider))
			{
				//std::cout << "Enemy Hit Wall!" << std::endl;
				e->getComponent<TransformComponent>().position = enemyPos;
			}
		}
	}


	//testing enemy movement
	for (auto& e : enemies)
	{
		int ub = 1, lb = -2;
		
		e->getComponent<TransformComponent>().position.x += ((rand() % 3) - 1) * 3;
		e->getComponent<TransformComponent>().position.y += ((rand() % 3) - 1) * 3;
		//std::cout << (rand() % 3)-1 << std::endl;
	}

	
	//Moving pVisual with Player position
	if (checkPlayerPos.x != playerPos.x || checkPlayerPos.y != playerPos.y)
	{
		Vector2D diffPos = checkPlayerPos - playerPos;
		std::cout << "move vis" << diffPos << std::endl;
		for (auto& v : visuals)
		{
			Vector2D vPos = v->getComponent<TransformComponent>().position;
			v->getComponent<TransformComponent>().position = vPos - diffPos;
		}
		checkPlayerPos = playerPos;
	}
	
	
	

	camera.x = (player.getComponent<TransformComponent>().position.x + (player.getComponent<TransformComponent>().width/2)) - 400;
	camera.y = (player.getComponent<TransformComponent>().position.y + (player.getComponent<TransformComponent>().height / 2)) - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

	std::string pDirection = player.getComponent<TransformComponent>().direction;
	//std::cout << pDirection << std::endl;
	//std::cout << isShooting << std::endl;

	//Player projectile function
	if (isShooting == true )
	{
		if (pDirection == "Up")
		{
			/*
			for (int i = 0; i < 10; i++)
			{
				assets->CreateProjectile((playerPos - Vector2D(10, 0)), Vector2D(0, -1), 2000, 1, "projectile", "Left");
			}
			*/
			assets->CreateProjectile((playerPos - Vector2D(10, 0)), Vector2D(0, -1), 2000, 1, "projectile", "Left");
			isShooting = false;
		}
		if (pDirection == "Down")
		{
			assets->CreateProjectile((playerPos - Vector2D(10, 0)), Vector2D(0, 1), 2000, 1, "projectile", "Right");
			isShooting = false;
		}
		if (pDirection == "Left")
		{
			assets->CreateProjectile((playerPos - Vector2D(0, 20)), Vector2D(-1, 0), 2000, 1, "projectile", "Left");
			isShooting = false;
		}
		if(pDirection == "Right")
		{
			assets->CreateProjectile((playerPos - Vector2D(10, 0)), Vector2D(1, 0), 2000, 1, "projectile", "Right");
			isShooting = false;
		}
	}
	
	
	
	/*
	 
	
	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		
	}
	*/
	//left_down = false;
}




void Game::render()
{
	SDL_RenderClear(renderer);
	//This where we add stuff to render
	
	for (auto& t : tiles)
	{
		t->draw();
	}

	//Remove this for loop to hide collider boxes
	for (auto& c : colliders)
	{
		c->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& v : visuals)
	{
		v->draw();
	}
	

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned!" << std::endl;

}

