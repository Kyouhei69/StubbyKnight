#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	
	std::map<const char*, Animation>animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 6, 100);
		Animation shoot = Animation(1, 19, 100);
		Animation hurt = Animation(2, 6, 100);
		Animation reload = Animation(3, 14, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Shoot", shoot);
		animations.emplace("Hurt", hurt);
		animations.emplace("Reload", reload);

		Play("Idle");

		texture = TextureManager::LoadTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	
	
	

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width; 
		
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

		}
		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;
	}

	void draw() override
	{
		TextureManager::DrawTexture(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};