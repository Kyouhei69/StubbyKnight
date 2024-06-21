#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
	{

	}
	~ProjectileComponent()
	{

	}
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		
	}

	void update() override
	{
		transform->position.x += velocity.x * speed;
		transform->position.y += velocity.y * speed;

		if (distance > range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		else if (transform->position.x > Game::cam->camPos.x + Game::cam->camDimension.w ||
			transform->position.x < Game::cam->camPos.x ||
			transform->position.y > Game::cam->camPos.y + Game::cam->camDimension.h ||
			transform->position.y < Game::cam->camPos.y
			)
		{
			std::cout << "Out of bounds" << std::endl;
			entity->destroy();
		}
	}

private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};