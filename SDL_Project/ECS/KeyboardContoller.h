#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"



class KeyboardController : public Component
{
public:
	
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	
	//bool key_down = false;

	void init() override
	{
		
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		//Checks if player is still alive to be controlled
		if (Game::playerAlive == true)
		{
			//Single press function
			if (Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_SPACE:
					Game::isSlashing = true;
					sprite->Play("Slash");
					break;
				case SDLK_t:
					Game::InitialTime = Game::GameTime;
					Game::TotalGameTime = 0;
					Game::CountGameTime = true;
					break;
				case SDLK_y:
					Game::CountGameTime = false;
					std::cout << Game::TotalGameTime << std::endl;
					break;
				case SDLK_h:

					break;
				}
			}

			//Continuos press function
			if (Game::event.type == SDL_KEYDOWN)
			{

				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = -1;
					transform->direction = "Up";
					sprite->Play("Walk");
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					transform->direction = "Left";
					sprite->Play("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					transform->direction = "Right";
					sprite->Play("Walk");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_s:
					transform->velocity.y = 1;
					transform->direction = "Down";
					sprite->Play("Walk");
					break;
				default:
					break;
				}
			}

			if (Game::event.type == SDL_KEYUP)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = 0;
					sprite->Play("Idle");
					break;
				case SDLK_a:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					break;
				case SDLK_d:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					break;
				case SDLK_s:
					transform->velocity.y = 0;
					sprite->Play("Idle");
					break;
				case SDLK_SPACE:

					sprite->Play("Idle");
					break;
				default:
					break;
				}
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
};