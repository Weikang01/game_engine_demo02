#include "Sandbox2D.h"
#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController((float)Engine::Application::Get().GetWindow().GetWidth() / (float)Engine::Application::Get().GetWindow().GetHeight())
{
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	m_CameraController.onUpdate(ts);

	Engine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
	Engine::RenderCommand::Clear();

	Engine::Renderer2D::BeginScene(m_CameraController.getCamera());
	Engine::Renderer2D::DrawQuad(glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f,1.f }, m_SquareCol);
	Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareCol));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& evnt)
{
	m_CameraController.onEvent(evnt);
}
