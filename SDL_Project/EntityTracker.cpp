#include "EntityTracker.h"


//Get 2 entities position
//Get the movement direction (x,y) for tracker in relation between the two entities
//Return the direction for movement to the entity

float distLength = 0;

Vector2D EntityTracker::InitTracker(Vector2D tracker, Vector2D target)
{
	Vector2D vectDistance = target-tracker;
	distLength = std::sqrtf((pow(vectDistance.x,2)) + (pow(vectDistance.y, 2)));
	Vector2D vectDirection = Vector2D((vectDistance.x / distLength), (vectDistance.y / distLength));

	//std::cout << distLength << vectDirection << std::endl;
	return vectDirection;
}

float EntityTracker::getLength()
{
	float sendLength = distLength;
	return sendLength;
}
