#pragma once
#include "Engine.h"



class Sandbox2D :public Engine::Layer
{
public:
	Sandbox2D();
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Engine::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Engine::Event& evnt) override;
private:
	Engine::Ref<Engine::Shader> m_shader;
	Engine::Ref<Engine::VertexArray> m_SquareVA;

	Engine::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareCol = glm::vec4(1.f, 1.f, 1.f, 1.f);
};

