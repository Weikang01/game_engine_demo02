#include "engine_pch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:GraphicsContext(), m_windowHandle(windowHandle)
	{
		EG_CORE_ASSERT(windowHandle, "Window does not exists!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_CORE_ASSERT(status, "Failed to initialize Glad!");

		EG_CORE_INFO("OpenGL Info:");
		EG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		EG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		EG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}