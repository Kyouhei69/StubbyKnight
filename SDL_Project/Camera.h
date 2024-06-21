#pragma once
#include "SDL.h"
#include "Vector2D.h"

class Camera
{
public:
	Camera();
	~Camera();

	SDL_Rect camDimension;
	int p_width;
	int p_height;

	Vector2D pPosition;
	Vector2D camPos;


	Vector2D CameraMovement(Vector2D pPos, int width, int height);

};