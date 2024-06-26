#pragma once
#include "Components.h"
#include "SDL.h"

class EntityStatusComponent : public Component
{
private:
	
	
public:
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
		
	}

	void update() override
	{
		if (HealthPoint <= 0)
		{
			isAlive = false;
			std::cout << "Dead" << std::endl;
		}
		
	}
	~EntityStatusComponent()
	{

	}
};