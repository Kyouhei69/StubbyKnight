#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include <string>



struct TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	Vector2D lastDirection = Vector2D(1,0);
	std::string direction;
	

	int height = 60;
	int width = 60;
	int scale = 2;

	int speed = 3;

	

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.x = 400;
		position.y = 320;

		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	

	void init() override
	{
		velocity.Zero();
		direction = "Right";
		
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		if (velocity.x != 0 || velocity.y != 0)
		{
			lastDirection = velocity;
		}
		
	}

	
	

	
};