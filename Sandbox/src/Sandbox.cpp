#include <Engine.h>
#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer :public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController((float)Engine::Application::Get().GetWindow().GetWidth() / (float)Engine::Application::Get().GetWindow().GetHeight())
	{
		m_vertexArray.reset(Engine::VertexArray::Create());
		m_SquareVA.reset(Engine::VertexArray::Create());

		float vertices[(3 + 4) * 3] =
		{
			-.5f, -.5f, .0f, 1.f, 0.25f, 1.f, 1.f,
			 .5f, -.5f, .0f, 0.25f, 1.f, 1.f, 1.f,
			 .0f,  .5f, .0f, 1.f, 1.f, 0.25f, 1.f
		};

		m_vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		Engine::BufferLayout layout =
		{
			{Engine::ShaderDataType::Float3, "a_Position"},
			{Engine::ShaderDataType::Float4, "a_Color"}
		};
		m_vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);


		uint32_t indices[3] =
		{
			0,1,2
		};

		m_indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		float squareVertices[5 * 4] =
		{
			-.5f, -.5f, .0f, 0.f, 0.f,
			 .5f, -.5f, .0f, 1.f, 0.f,
			 .5f,  .5f, .0f, 1.f, 1.f,
			-.5f,  .5f, .0f, 0.f, 1.f
		};

		std::shared_ptr<Engine::VertexBuffer> squareVB;
		squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Engine::BufferLayout squareLayout =
		{
			{Engine::ShaderDataType::Float3, "a_Position"},
			{Engine::ShaderDataType::Float2, "a_texCoord"}
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

		auto squareShader = m_shaderLibrary.Load("assets/shaders/texture.glsl");
		m_checkerBoardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_faceTexture = Engine::Texture2D::Create("assets/textures/awesomeface.png");
		std::dynamic_pointer_cast<Engine::OpenGLShader> (squareShader)->setInt("u_texture", 0);
	}

	void OnUpdate(Engine::Timestep ts) override
	{
		m_CameraController.onUpdate(ts);

		Engine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
		Engine::RenderCommand::Clear();

		Engine::Renderer::BeginScene(m_CameraController.getCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(.05f));

		auto squareShader = m_shaderLibrary.Get("texture");

		m_checkerBoardTexture->Bind(0);

		Engine::Renderer::Submit(m_SquareVA, squareShader, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		m_faceTexture->Bind(0);
		Engine::Renderer::Submit(m_SquareVA, squareShader, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		std::dynamic_pointer_cast<Engine::OpenGLShader> (squareShader)->set3fv("tint", m_SquareCol);

		//Engine::Renderer::Submit(m_vertexArray, m_shader);

		Engine::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareCol));
		ImGui::End();
	}

	void OnEvent(Engine::Event& evnt) override
	{
		m_CameraController.onEvent(evnt);
	}

private:
	Engine::ShaderLibrary m_shaderLibrary;
	Engine::Ref<Engine::VertexBuffer> m_vertexBuffer;
	Engine::Ref<Engine::IndexBuffer> m_indexBuffer;
	Engine::Ref<Engine::VertexArray> m_vertexArray;
	Engine::Ref<Engine::VertexArray> m_SquareVA;
	Engine::Ref<Engine::Texture2D> m_checkerBoardTexture;
	Engine::Ref<Engine::Texture2D> m_faceTexture;

	Engine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquarePos = glm::vec3(.3f, .3f, 0.f);
	glm::vec3 m_SquareCol = glm::vec3(1.f, 1.f, 1.f);
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