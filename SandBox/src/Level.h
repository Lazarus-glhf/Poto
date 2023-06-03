#pragma once

#include <Poto.h>

#include "Enemy.h"
#include "PlayerPlane.h"

class Level
{
public:
	void Reset();
	bool OnUpdate(Poto::Timestep ts);
	void OnRender();

	bool UpdateEnemyPosition();
	void SpawnNewEnemy();

	void MovePlane(float x) { m_Plane->Move(x); }
private:
	Poto::Scope<PlayerPlane> m_Plane;
	std::vector<Enemy*> Enemies;
	float m_Count = 0;
};
