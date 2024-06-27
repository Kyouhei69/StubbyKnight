#pragma once
#include "Components.h"
#include "SDL.h"
#include "../Vector2D.h"

struct EntityStatusComponent : public Component
{

	
	
public:
	TransformComponent* transform;

	bool isAlive = true;
	float HealthPoint = 5;
	int ManaPoint = 5;
	

	EntityStatusComponent()
	{
		HealthPoint = 5;
		ManaPoint = 5;
	};
	EntityStatusComponent(float hp, int mp)
	{
		HealthPoint = hp;
		ManaPoint = mp;
	}
	
	void Heal(int hp)
	{
		HealthPoint += hp;
	}

	void init()override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (HealthPoint <= 0)
		{
			isAlive = false;
			std::cout << "Dead 0 HP" << std::endl;

		}
		
		
	}
	~EntityStatusComponent()
	{

	}
};