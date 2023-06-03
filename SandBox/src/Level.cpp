#include "Level.h"

#include <random>

#include "Color.h"

void Level::Reset()
{
	m_Count = 0;
	Enemies.clear();
	m_Plane.reset(new PlayerPlane(0, -15, glm::vec2(10, 1)));
	PT_INFO("plane y is {0}", m_Plane->GetPos().y);
}

bool Level::OnUpdate(Poto::Timestep ts)
{
	m_Count ++;
	if (m_Count > 300)
	{
		m_Count = 0;
		SpawnNewEnemy();
	}
	return UpdateEnemyPosition();
}

void Level::OnRender()
{
	Poto::Renderer2D::DrawQuad(m_Plane->GetPos(), m_Plane->GetSize(), Color::Red);
	for (auto e : Enemies)
	{
		Poto::Renderer2D::DrawQuad(e->GetPos(), glm::vec2(1), Color::White);
	}
}

bool Level::UpdateEnemyPosition()
{
	for (size_t i = 0; i < Enemies.size(); ++i)
	{
		if (Enemies[i]->GetState())
		{
			Enemies[i]->MoveForward();
			auto pos = Enemies[i]->GetPos();
			if (pos.y <= -15)
			{
				PT_INFO("Touch line");
				Enemies[i]->Kill();

				if (m_Plane->Catch(pos.x))
				{
					PT_INFO("Catched");
					return true;
				}
				return false;
			}
		}
		else
		{
			delete Enemies[i];
			Enemies.erase(Enemies.begin() + i);
		}
	}
	return true;
}

void Level::SpawnNewEnemy()
{
	int min = -35, max = 35;
	std::random_device seed;//硬件生成随机数种子
	std::ranlux48 engine(seed());//利用种子生成随机数引擎
	std::uniform_int_distribution<> distrib(min, max);//设置随机数范围，并为均匀分布
	int random = distrib(engine);//随机数

	Enemies.push_back(new Enemy(random, 20));
}
