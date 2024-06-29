#include "Camera.h"


Camera::Camera()
{
	camDimension = { 0,0,800,800 };
}

Camera::~Camera()
{
}

Vector2D Camera::CameraMovement(Vector2D pPos, int width, int height)
{
	pPosition = pPos;
	p_width = width;
	p_height = height;

	camPos.x = (pPos.x + (p_width / 2)) - 400;
	camPos.y = (pPos.y + (p_height / 2)) - 400;

	if (camPos.x < 0)
		camPos.x = 0;
	if (camPos.y < 0)
		camPos.y = 0;
	if (camPos.x > camDimension.w)
		camPos.x = camDimension.w;
	if (camPos.y > camDimension.h)
		camPos.y = camDimension.h;

	//std::cout << "Camera Function: x =" << camPos.x << " y = " << camPos.y << std::endl;

	return camPos;
}
