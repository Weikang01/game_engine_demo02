#include <Engine.h>
#include <Engine/EntryPoint.h>
#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class Sandbox:public Engine::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
	PushLayer(new Sandbox2D());
}

Sandbox::~Sandbox()
{
}

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}