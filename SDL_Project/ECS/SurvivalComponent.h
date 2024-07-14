#pragma once
#include "ECS.h"
#include "Components.h"

class SurvivalComponent : public Component
{
public:
	SurvivalComponent() = default;

	~SurvivalComponent();

	void init() override
	{
		std::cout << "Initialized Survival Component!" << std::endl;
	}
private:

};

