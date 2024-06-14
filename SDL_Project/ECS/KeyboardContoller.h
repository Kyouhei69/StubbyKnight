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
	
	bool key_down = false;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		
	}

	void update() override
	{
		//Single press function
		if (Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_SPACE:
				//Game::left_down = true;
				key_down = true;

				if (key_down == true)
				{
					Game::isShooting = true;
					sprite->Play("Shoot");
				}

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
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				transform->direction = "Left";
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				transform->direction = "Right";
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				transform->direction = "Down";
				break;
			
			case SDLK_ESCAPE:
				Game::isRunning = false;
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
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			default:
				break;
			}
		}
	}
};