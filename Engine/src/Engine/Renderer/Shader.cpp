#include "engine_pch.h"
#include "Shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Engine
{
	Shader* Shader::Create(const char* shaderFile)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(shaderFile);
			break;
		}
		EG_CORE_ASSERT(false, "Shader case is currently not supported!");
	}

	Shader* Shader::Create(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexShaderFile, fragmentShaderFile, geometricShaderFile);
			break;
		}
		EG_CORE_ASSERT(false, "Shader case is currently not supported!");
	}

	Shader* Shader::Create(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(dummy, vertexShaderCode, fragmentShaderCode, geometricShaderCode);
			break;
		}
		EG_CORE_ASSERT(false, "Shader case is currently not supported!");
	}

	void Shader::compile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile)
	{
	}

	void Shader::compile(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode)
	{

	}
}