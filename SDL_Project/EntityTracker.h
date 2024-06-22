#pragma once

#include "Game.h"
#include "Vector2D.h"

class EntityTracker
{
public:
	
	
	//EntityTracker();

	static Vector2D InitTracker(Vector2D tracker, Vector2D target);
	static float getLength();
};