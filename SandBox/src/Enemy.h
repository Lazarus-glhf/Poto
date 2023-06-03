#pragma once

#include <Poto.h>

class Enemy
{
public:
	Enemy(float X, float Y);

	inline bool GetState() const { return Alive; }
	inline void Kill() { Alive = false; }
	inline void MoveForward() { WorldPositionY += moveSpeed; }
	inline glm::vec2 GetPos() const { return glm::vec2(WorldPositionX, WorldPositionY); }
private:
	bool Alive = true;
	float moveSpeed = -0.01;
	float WorldPositionX, WorldPositionY;
};
