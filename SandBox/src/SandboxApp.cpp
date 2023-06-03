#include <Poto.h>
#include <Poto/Core/EntryPoint.h>

#include "ClientLayer.h"

class Sandbox : public Poto::Application
{
public:
	Sandbox()
	{
		PushLayer(new ClientLayer());
	}

	~Sandbox()
	{
		
	}
};

Poto::Application* Poto::CreateApplication()
{
	return new Sandbox();
}
