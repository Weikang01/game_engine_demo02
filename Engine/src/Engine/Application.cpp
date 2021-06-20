#include "engine_pch.h"
#include "Application.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Input.h"
#include "Engine/ImGui/ImGuiLayer.h"


namespace Engine
{
	Application* Application::s_instance = nullptr;

	Application::Application()
		:m_Camera(-1.6f, 1.6f, -.9f, .9f)
	{
		EG_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		m_imGuiLayer = new ImGuiLayer();
		PushLayer(m_imGuiLayer);

		m_vertexArray.reset(VertexArray::Create());
		m_SquareVA.reset(VertexArray::Create());

		float vertices[(3 + 4) * 3] =
		{
			-.5f, -.5f, .0f, 1.f, 0.25f, 1.f, 1.f,
			 .5f, -.5f, .0f, 0.25f, 1.f, 1.f, 1.f,
			 .0f,  .5f, .0f, 1.f, 1.f, 0.25f, 1.f
		};

		m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		m_vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);


		uint32_t indices[3] =
		{
			0,1,2
		};

		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(m_indexBuffer);


		float squareVertices[3 * 4] =
		{
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f,
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout squareLayout =
		{
			{ShaderDataType::Float3, "a_Position"}
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] =
		{
			0,1,2,2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		m_shader.reset(new Shader(1, vertexSrc, fragmentSrc));

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
		
		m_squareShader.reset(new Shader(1, squareVertexSrc, squareFragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& evnt)
	{
		EventDispatcher dispatcher(evnt);
		dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(evnt);
			if (evnt.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& evnt)
	{
		m_running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_running)
		{
			RenderCommand::SetClearColor({ 0, 0, 0, 1 });
			RenderCommand::Clear();

			m_Camera.SetRotation(10.f);
			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_SquareVA, m_squareShader);

			Renderer::Submit(m_vertexArray, m_shader);

			Renderer::EndScene();

			m_imGuiLayer->begin();
			for (Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
				layer->OnImGuiRender();
			}
			m_imGuiLayer->end();

			m_window->OnUpdate();
		}
	}
}