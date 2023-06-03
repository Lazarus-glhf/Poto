#pragma once

#include <Poto.h>

class PlayerPlane
{
public:
	PlayerPlane(float x, float y, glm::vec2 size);
	bool Catch(float x);
	bool Move(float x);

	inline glm::vec2 GetPos() const { return glm::vec2(worldPositionX, worldPositonY); }
	inline glm::vec2 GetSize() const { return planeSize; }
private:
	float worldPositionX = 0, worldPositonY = 0;
	glm::vec2 planeSize = {3, 1};
};

