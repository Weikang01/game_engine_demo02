#pragma once
#include "Engine/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Engine
{
	class GraphicsContext;
	
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_data.Width; }
		unsigned int GetHeight() const override { return m_data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return m_data.VSync; }

		virtual void* GetNativeWindow() const { return m_window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_window = nullptr;
		GraphicsContext* m_context = nullptr;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		}m_data;
	};
}
