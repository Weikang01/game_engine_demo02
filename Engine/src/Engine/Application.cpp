#include "engine_pch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Engine/Input.h"
#include "Engine/ImGui/ImGuiLayer.h"


namespace Engine
{
	Application* Application::s_instance = nullptr;

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

		float vertices[3 * 3] =
		{
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .0f,  .5f, .0f
		};

		m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		uint32_t indices[3] =
		{
			0,1,2
		};

		m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		glBindVertexArray(0);

		const char* vertexSrc = R"(
#version 440 core
layout(location = 0) in vec3 position;

out vec3 pos;

void main()
{
	gl_Position = vec4(position, 1.f);
	pos = position * .5f + vec3(.5f);
}
)";

		const char* fragmentSrc = R"(
#version 440 core

in vec3 pos;

void main()
{
	gl_FragColor = vec4(pos, 1.f);
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