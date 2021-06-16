#pragma once
#include "Core.h"

#include "Engine/Window.h"
#include "Engine/LayerStack.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Renderer/Shader.h"
#include <Engine/Renderer/Buffer.h>

namespace Engine
{
	class ImGuiLayer;

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& evnt);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_instance; }
		Window& GetWindow() { return *m_window; }
	private:
		static Application* s_instance;

		bool OnWindowClose(WindowCloseEvent& evnt);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imGuiLayer = nullptr;
		bool m_running = true;
		LayerStack m_layerStack;


		unsigned int VAO;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
