#pragma once
#include "Components.h"

class StatusComponent : public Component
{
private:

public:
	int HP;
	TransformComponent* transform;

	StatusComponent() = default;
	~StatusComponent()
	{

	}


};