#include "engine_pch.h"
#include "WindowsWindow.h"

#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine
{
	static bool s_GLFWInitialized = false;

	static void GLFWerrorCallback(int error_code, const char* description)
	{
		EG_CORE_ERROR("GLFW Error ({0}) : {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_data.VSync = enabled;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		EG_CORE_INFO("Creating window {0}, ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			EG_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWerrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), nullptr, nullptr);
		m_context = new OpenGLContext(m_window);
		m_context->Init();

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent evnt(width, height);
				data.EventCallback(evnt);
			}
		);

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent evnt;
				data.EventCallback(evnt);
			}
		);

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
					{
						KeyPressedEvent evnt(key, 0);
						data.EventCallback(evnt);
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent evnt(key);
						data.EventCallback(evnt);
						break;
					}
				case GLFW_REPEAT:
					{
						KeyPressedEvent evnt(key, 1);
						data.EventCallback(evnt);
						break;
					}
				}
			}
		);

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent evnt(keycode);
				data.EventCallback(evnt);
			}
		);

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent evnt(button);
						data.EventCallback(evnt);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent evnt(button);
						data.EventCallback(evnt);
						break;
					}
				}
			}
		);

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent evnt((float)xoffset, (float)yoffset);
				data.EventCallback(evnt);
			}
		);

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent evnt((float)xpos, (float)ypos);
				data.EventCallback(evnt);
			}
		);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}