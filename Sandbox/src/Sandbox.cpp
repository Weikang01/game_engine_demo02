#include <Engine.h>
#include <imgui.h>

class ExampleLayer :public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Engine::Input::IsKeyPressed(Engine::Key::Tab))
			EG_TRACE("Tab is pressed [Poll]");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Layer");
		ImGui::Text("Hello");
		ImGui::End();
	}

	void OnEvent(Engine::Event& evnt) override
	{
		if (evnt.GetEventType() == Engine::EventType::KeyPressed)
		{
			Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)evnt;

			if (e.GetKeyCode() == Engine::Key::Tab)
			{
				EG_TRACE("Tab is pressed [Event]");
			}
		}
	}
};


class Sandbox:public Engine::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
}

Sandbox::~Sandbox()
{
}

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}