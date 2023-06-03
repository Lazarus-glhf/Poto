#include "PlayerPlane.h"

PlayerPlane::PlayerPlane(float x, float y, glm::vec2 size)
	:worldPositionX(x), worldPositonY(y), planeSize(size)
{
	
}


bool PlayerPlane::Catch(float x)
{
	if (x < worldPositionX + planeSize.x / 2 && x > worldPositionX - planeSize.x)
	{
		return true;
	}
	return false;
}

bool PlayerPlane::Move(float x)
{
	if (worldPositionX + x < 35 || worldPositionX + x > 35)
	{
		worldPositionX += x;
		return true;
	}
	return false;
}
