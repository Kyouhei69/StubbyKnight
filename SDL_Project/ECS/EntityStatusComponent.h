#pragma once
#include "Components.h"

struct EntityStatusComponent : public Component
{
public:
	float HealthPoint;
	int ManaPoint;
	bool isAlive = true;

	EntityStatusComponent(float hp, int mp)
	{
		HealthPoint = hp;
		ManaPoint = mp;
	}
	
	void init() override
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

};