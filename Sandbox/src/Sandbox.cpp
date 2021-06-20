#include <Engine.h>
#include <imgui.h>

class ExampleLayer :public Engine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -.9f, .9f)
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


		float squareVertices[3 * 4] =
		{
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f,
		};

		std::shared_ptr<Engine::VertexBuffer> squareVB;
		squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Engine::BufferLayout squareLayout =
		{
			{Engine::ShaderDataType::Float3, "a_Position"}
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

		const char* vertexSrc = R"(
#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec3 pos;
out vec4 col;

uniform mat4 viewProjMat;

void main()
{
	gl_Position = viewProjMat * vec4(position, 1.f);
	pos = position * .5f + vec3(.5f);
	col = color;
}
)";

		const char* fragmentSrc = R"(
#version 440 core

in vec3 pos;
in vec4 col;

void main()
{
	gl_FragColor = col;
}
)";

		m_shader.reset(new Engine::Shader(1, vertexSrc, fragmentSrc));

		const char* squareVertexSrc = R"(
#version 440 core
layout(location = 0) in vec3 position;

out vec3 pos;
uniform mat4 viewProjMat;

void main()
{
	gl_Position = viewProjMat * vec4(position, 1.f);
	pos = position + vec3(.5f);
}
)";

		const char* squareFragmentSrc = R"(
#version 440 core

in vec3 pos;

void main()
{
	gl_FragColor = vec4(pos, 1.f);
}
)";

		m_squareShader.reset(new Engine::Shader(1, squareVertexSrc, squareFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Engine::Input::IsKeyPressed(Engine::Key::A))
		{
			m_CamPos.x -= m_CamSpeed;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::D))
		{
			m_CamPos.x += m_CamSpeed;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::S))
		{
			m_CamPos.y -= m_CamSpeed;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::W))
		{
			m_CamPos.y += m_CamSpeed;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::Q))
		{
			m_CamAngle += m_CamRotSpeed;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::E))
		{
			m_CamAngle -= m_CamRotSpeed;
		}

		Engine::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
		Engine::RenderCommand::Clear();


		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamAngle);
		Engine::Renderer::BeginScene(m_Camera);

		Engine::Renderer::Submit(m_SquareVA, m_squareShader);

		Engine::Renderer::Submit(m_vertexArray, m_shader);

		Engine::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Engine::Event& evnt) override
	{

	}

private:
	std::shared_ptr<Engine::Shader> m_shader;
	std::shared_ptr<Engine::Shader> m_squareShader;
	std::shared_ptr<Engine::VertexBuffer> m_vertexBuffer;
	std::shared_ptr<Engine::IndexBuffer> m_indexBuffer;
	std::shared_ptr<Engine::VertexArray> m_vertexArray;
	std::shared_ptr<Engine::VertexArray> m_SquareVA;

	Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CamPos = glm::vec3();
	float m_CamSpeed = .1f;
	float m_CamAngle = 0.f;
	float m_CamRotSpeed = 1.f;
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