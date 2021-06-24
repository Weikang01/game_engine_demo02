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
	m_SquareVA = Engine::VertexArray::Create();

	float squareVertices[3 * 4] =
	{
		-.5f, -.5f, .0f,
		 .5f, -.5f, .0f,
		 .5f,  .5f, .0f,
		-.5f,  .5f, .0f
	};

	std::shared_ptr<Engine::VertexBuffer> squareVB;
	squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	Engine::BufferLayout squareLayout =
	{
		{Engine::ShaderDataType::Float3, "a_Position"},
	};
	squareVB->SetLayout(squareLayout);
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] =
	{
		0,1,2,2,3,0
	};
	std::shared_ptr<Engine::IndexBuffer> squareIB;
	squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_shader = Engine::Shader::Create("assets/shaders/flatColorTexture.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	m_CameraController.onUpdate(ts);

	Engine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
	Engine::RenderCommand::Clear();

	Engine::Renderer::BeginScene(m_CameraController.getCamera());

	std::dynamic_pointer_cast<Engine::OpenGLShader> (m_shader)->set4fv("color", m_SquareCol);
	Engine::Renderer::Submit(m_SquareVA, m_shader, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

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
