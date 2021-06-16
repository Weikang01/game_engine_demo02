#include "engine_pch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Engine/Input.h"
#include "Engine/ImGui/ImGuiLayer.h"


namespace Engine
{
	Application* Application::s_instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Float:
		case Engine::ShaderDataType::Float2:
		case Engine::ShaderDataType::Float3:
		case Engine::ShaderDataType::Float4:
		case Engine::ShaderDataType::Mat3:
		case Engine::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Engine::ShaderDataType::Int:
		case Engine::ShaderDataType::Int2:
		case Engine::ShaderDataType::Int3:
		case Engine::ShaderDataType::Int4:
			return GL_INT;
		case Engine::ShaderDataType::Bool:
			return GL_BOOL;
		}
	}

	Application::Application()
	{
		EG_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		m_imGuiLayer = new ImGuiLayer();
		PushLayer(m_imGuiLayer);

		// Render
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		float vertices[(3 + 4) * 3] =
		{
			-.5f, -.5f, .0f, 1.f, 0.f, 1.f, 1.f,
			 .5f, -.5f, .0f, 0.f, 1.f, 1.f, 1.f,
			 .0f,  .5f, .0f, 1.f, 1.f, 0.f, 1.f
		};

		{
			m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			BufferLayout layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};
			m_vertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}



		uint32_t indices[3] =
		{
			0,1,2
		};

		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		glBindVertexArray(0);

		const char* vertexSrc = R"(
#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec3 pos;
out vec4 col;

void main()
{
	gl_Position = vec4(position, 1.f);
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
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VAO);
			m_vertexBuffer->Bind();
			m_indexBuffer->Bind();

			m_shader->use();
			glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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