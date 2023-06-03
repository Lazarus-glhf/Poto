#include "ClientLayer.h"

#include "Color.h"

ClientLayer::ClientLayer()
	: Layer("ClientLayer")
{
	auto& window = Poto::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	m_Level = Poto::CreateScope<Level>();
}

ClientLayer::~ClientLayer()
{
	
}

void ClientLayer::OnAttach()
{
	m_Level->Reset();
}

void ClientLayer::OnDetach()
{
	
}

void ClientLayer::OnUpdate(Poto::Timestep ts)
{
	m_WorldTimer = ts;

	m_Level->OnUpdate(ts);

	Poto::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Poto::RenderCommand::Clear();

	Poto::Renderer2D::BeginScene(*m_Camera);
	m_Level->OnRender();
	Poto::Renderer2D::EndScene();
}

void ClientLayer::OnEvent(Poto::Event& event)
{
	Poto::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Poto::KeyPressedEvent>(PT_BIND_EVENT_FN(ClientLayer::OnKeyPressed));
	dispatcher.Dispatch<Poto::WindowResizeEvent>(PT_BIND_EVENT_FN(ClientLayer::OnWindowResize));
}

bool ClientLayer::OnKeyPressed(Poto::KeyPressedEvent& e)
{
    switch (m_GameState)
    {
    case GameState::Menu:
        m_GameState = GameState::Playing;
        return true;
    case GameState::Dead:
        m_Level->Reset();
        m_GameState = GameState::Playing;
        return true;
    }
    switch (e.GetKeyCode())
    {
    case PT_KEY_LEFT:
    case PT_KEY_A:
	    {
			m_Level->MovePlane(-50 * m_WorldTimer);
			break;
	    }
    case PT_KEY_RIGHT:
    case PT_KEY_D:
	    {
			m_Level->MovePlane(50 * m_WorldTimer);
			break;
	    }
    }
    return true;
}

bool ClientLayer::OnWindowResize(Poto::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void ClientLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 12.f * 40u / 21.f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Poto::CreateScope<Poto::OrthographicCamera>(left, right, bottom, top);
}
