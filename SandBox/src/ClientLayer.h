#pragma once

#include <Poto.h>
#include "GameState.h"
#include "Level.h"

class ClientLayer : public Poto::Layer
{
public:
	ClientLayer();
	virtual ~ClientLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Poto::Timestep ts) override;

	void OnEvent(Poto::Event& event) override;
	bool OnKeyPressed(Poto::KeyPressedEvent& e);
	bool OnWindowResize(Poto::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

	Poto::Scope<Poto::OrthographicCamera> m_Camera;
	GameState m_GameState = GameState::Menu;
	float m_WorldTimer;
	Poto::Scope<Level> m_Level;
};
