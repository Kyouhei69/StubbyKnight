#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Camera.h"
#include "EntityTracker.h"
#include <cstdlib> 


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;



AssetManager* Game::assets = new AssetManager(&manager);
Camera* Game::cam = new Camera();



bool Game::isRunning = false;

bool Game::isSlashing = false;
bool Game::CountGameTime = false;
bool Game::playerAlive = true;

auto& player(manager.addEntity());


int GameTime;
int TotalScore = 0;

Vector2D initPlayer(600, 740);

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
		flags = SDL_WINDOW_RESIZABLE;
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

	assets->AddTexture("testMap", "Assets/map/watermap.png");
	assets->AddTexture("bloodMap", "Assets/map/bloodmap.png");
	assets->AddTexture("player", "Assets/StubbySheet.png");
	assets->AddTexture("zombie", "Assets/ZombieSheet.png");
	assets->AddTexture("projectile", "Assets/dagger_proj.png");
	assets->AddTexture("projectile_up", "Assets/dagger_proj_up.png");
	assets->AddTexture("pVisual", "Assets/Heart.png");

	//Initialize tilemap layers (map/items/object sprites)
	//Map layer sprite:
	map = new Map("testMap", 2, 16);
	map->LoadMap("Assets/map/map.map", 50, 50);
	//Object/item layer sprite:
	//map = new Map("bloodMap", 1, 32);
	//map->LoadMap("Assets/map/bloodmap.map", 10, 10);

	player.addComponent<TransformComponent>(initPlayer.x,initPlayer.y,42,42,2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	std::cout << "Collider: " << player.getComponent<ColliderComponent>().collider.w << std::endl;
	player.addComponent<EntityStatusComponent>();
	
	player.addGroup(groupPlayers);
	std::cout << "Player HP:" << player.getComponent<EntityStatusComponent>().HealthPoint << std::endl;

	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D newPos = playerPos + Vector2D(80,-16);

	//Testing visuals on top of player. (HP visual)
	for (int i = 0; i < 5; i++)
	{
		newPos = playerPos + Vector2D(-16, 0);
		assets->CreateVisual(newPos, 16, 16, 1, "pVisual");
		std::cout << "Creating Visual" << i << newPos << std::endl;
	}
	
	//Spawning enemies
	for (int i = 0; i < 1; i++)
	{
		int ub = 800, lb = 30;
		Vector2D enemyPos = Vector2D(((rand() % (ub - lb + 1)) + lb), ((rand() % (ub - lb + 1)) + lb));
		std::cout << enemyPos << std::endl;
		int usb = 2, lsb = 1;
		int speed = rand() % (usb - lsb + 1) + lsb;
		std::cout << speed << std::endl;
		assets->CreateEnemy(enemyPos, 42, 42, 2, "zombie",speed);
	}

	
	
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& visuals(manager.getGroup(Game::groupVisuals));

void Game::handleEvents()
{
	
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


Vector2D checkPlayerPos(initPlayer);
int GameTimeCounter = 0;

int Game::TotalGameTime = 0;
int Game::GameTime = 0;
int Game::InitialTime = 0;

void Game::update()
{
	
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerDim = Vector2D(player.getComponent<TransformComponent>().width, player.getComponent<TransformComponent>().height);

	int playerW = player.getComponent<TransformComponent>().width;
	int playerH = player.getComponent<TransformComponent>().height;
	int pHp = player.getComponent<EntityStatusComponent>().HealthPoint;
	

	manager.refresh();
	manager.update();

	
	cam->CameraMovement(playerPos, playerW, playerH);
	
	
	
	
	//Check time change in seconds
	/*
	if (Game::CountGameTime == true) 
	{
		if (GameTimeCounter != GameTime)
		{
			//std::cout << "Initial Game Time:" << GameTime << " seconds" << std::endl;
			std::cout << "Time change!" << std::endl;
			//std::cout << "End Game Time:" << GameTime << " seconds" << std::endl;
			TotalGameTime++;
			int damage = 1;
			player.getComponent<EntityStatusComponent>().HealthPoint = pHp - damage;
			std::cout << "Player HP:" << player.getComponent<EntityStatusComponent>().HealthPoint << std::endl;
			if (player.getComponent<EntityStatusComponent>().HealthPoint <= 0)
			{
				player.getComponent<EntityStatusComponent>().isAlive = false;
				//player.destroy();
			}
			GameTimeCounter = GameTime;
		}
	}
	if (Game::CountGameTime == true && (Game::GameTime - Game::InitialTime) == 5)
	{
		
		std::cout << GameTime << std::endl;
		std::cout << "Debuff Ends!" << std::endl;
		std::cout << TotalGameTime << std::endl;
		std::cout << "Player HP:" << player.getComponent<EntityStatusComponent>().HealthPoint << std::endl;
		Game::CountGameTime = false;
	}
	*/
	

	////////////////////////////////////////////////////////////////////////////////////////
	//CHECKING PLAYER COLLISION WITH WALL
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			std::cout << "Pcol: " << playerCol.w << " " << playerCol.h << std::endl;
			player.getComponent<TransformComponent>().position = playerPos;
		}
		
	}

	////////////////////////////////////////////////////////////////////////////////////////
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

	
	////////////////////////////////////////////////////////////////////////////////////////
	//CHECKING ENEMY COLLISION WITH PROJECTILES
	for (auto& e : enemies)
	{
		if (e->getComponent<EntityStatusComponent>().isAlive != true)
		{
			std::cout << "Enemy Destroyed!" << std::endl;
			e->destroy();
			TotalScore += 100;
		}
		for (auto& p : projectiles)
		{
			if (Collision::AABB(e->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				std::cout << "Hit enemy" << std::endl;
				e->getComponent<EntityStatusComponent>().HealthPoint -= 1;
				std::cout << "Enemy HP: " << e->getComponent<EntityStatusComponent>().HealthPoint << std::endl;
				
				p->destroy();
				
			}
		}
	}


	bool playerHit = false;
	////////////////////////////////////////////////////////////////////////////////////////
	// Checking Enemy attack to player
	for (auto& e : enemies)
	{
		int damage = 1;
		if (Collision::AABB(e->getComponent<ColliderComponent>().collider, player.getComponent<ColliderComponent>().collider))
		{
			//std::cout << "Player Hit" << std::endl;
			if (GameTimeCounter != GameTime)
			{
				Vector2D trackerDir = EntityTracker::InitTracker(e->getComponent<TransformComponent>().position, player.getComponent<TransformComponent>().position);
				float range = EntityTracker::getLength();
				std::cout << "Player Hit" << std::endl;
				playerHit = true;
				std::cout << "Time change!" << std::endl;
				TotalGameTime++;
				
				player.getComponent<EntityStatusComponent>().HealthPoint = pHp - damage;
				std::cout << "Player HP:" << player.getComponent<EntityStatusComponent>().HealthPoint << std::endl;
				if (player.getComponent<EntityStatusComponent>().HealthPoint <= 0)
				{
					player.getComponent<EntityStatusComponent>().isAlive = false;
				}
				GameTimeCounter = GameTime;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Update pvisual to HP
	for (auto& v : visuals)
	{
		if (playerHit == true)
		{
			v->destroy();
		}
		playerHit = false;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//Enemy tracking player
	//Change direction sprite
	for (auto& e : enemies)
	{
		for (auto& p : players)
		{
			Vector2D trackerDir = EntityTracker::InitTracker(e->getComponent<TransformComponent>().position, p->getComponent<TransformComponent>().position);
			float range = EntityTracker::getLength();
			if (range > 80 && range < 400)
			{
				e->getComponent<TransformComponent>().position += trackerDir*(e->getComponent<TransformComponent>().speed);
				e->getComponent<SpriteComponent>().Play("Walk");
				if (trackerDir.x < 0) {
					e->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
				}
				if (trackerDir.x > 0) {
					e->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
				}
				
			}
			else
			{
				e->getComponent<TransformComponent>().velocity = Vector2D();
				e->getComponent<SpriteComponent>().Play("Idle");
			}
			if (range < 100)
			{
				e->getComponent<SpriteComponent>().Play("Slash");
			}

			

			
			//std::cout << trackerDir << range << std::endl;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////
	// CHECKING ENEMY COLLISION WITH WALL
	for (auto& e : enemies)
	{
		Vector2D enemyPos = e->getComponent<TransformComponent>().position;
		for (auto& c : colliders)
		{
			SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
			if (Collision::AABB(cCol, e->getComponent<ColliderComponent>().collider))
			{
				std::cout << "Enemy Hit Wall!" << std::endl;
				e->getComponent<TransformComponent>().position = enemyPos;
			}
		}
	}

	

	
	////////////////////////////////////////////////////////////////////////////////////////
	//Moving pVisual with Player position
	if (checkPlayerPos.x != playerPos.x || checkPlayerPos.y != playerPos.y)
	{
		Vector2D diffPos = checkPlayerPos - playerPos;
		//std::cout << "move vis" << diffPos << std::endl;
		for (auto& v : visuals)
		{
			Vector2D vPos = v->getComponent<TransformComponent>().position;
			v->getComponent<TransformComponent>().position = vPos - diffPos;
		}
		checkPlayerPos = playerPos;
	}
	
	

	

	
	


	////////////////////////////////////////////////////////////////////////////////////////
	//Player projectile function

	std::string pDirection = player.getComponent<TransformComponent>().direction;

	if (isSlashing == true )
	{
		player.getComponent<SpriteComponent>().Play("Slash");
		Vector2D projectilePos = playerPos;
		Vector2D projectileDirection = player.getComponent<TransformComponent>().lastDirection;
		std::string projectile_id;
		SDL_RendererFlip projectile_flip = SDL_FLIP_NONE;
		
		if (projectileDirection.x >= 1) // Right
		{
			projectilePos = playerPos + Vector2D(playerDim.x * 2, playerDim.y /4);
			projectile_id = "projectile";
			projectile_flip = SDL_FLIP_HORIZONTAL;
		}
		if (projectileDirection.x <= -1) //Left
		{
			projectilePos = playerPos + Vector2D(-playerDim.x, playerDim.y / 4);
			projectile_id = "projectile";
			projectile_flip = SDL_FLIP_NONE;
		}

		if (projectileDirection.y <= -1) //Up
		{
			projectilePos = playerPos + Vector2D(playerDim.x / 2, -playerDim.y);
			projectile_id = "projectile_up";
			projectile_flip = SDL_FLIP_NONE;
		}
		if (projectileDirection.y >= 1) //Down
		{
			projectilePos = playerPos + Vector2D(playerDim.x / 2, playerDim.y * 2);
			projectile_id = "projectile_up";
			projectile_flip = SDL_FLIP_VERTICAL;
		}
		std::cout<< player.getComponent<TransformComponent>().lastDirection << std::endl;
		assets->CreateProjectile(projectilePos, projectileDirection, 30, 1, projectile_id, projectile_flip);
		isSlashing = false;		
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	//Check damage and player status
	if (player.getComponent<EntityStatusComponent>().isAlive == false)
	{
		Game::playerAlive = false;
		player.getComponent<SpriteComponent>().Play("Died");
		player.getComponent<TransformComponent>().velocity = Vector2D();
	}

	

	//std::cout << "TotalScore: " << TotalScore << std::endl;
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

