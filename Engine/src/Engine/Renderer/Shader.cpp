#include "engine_pch.h"
#include "Shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Engine
{
	using std::endl;
	using std::ifstream;
	using std::stringstream;

	unsigned int Shader::loadShader(const char* fileName, GLenum type)
	{
		string codeString;
		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);
		stringstream fileStream;
		try
		{
			file.open(fileName);
			fileStream << file.rdbuf();
			codeString = fileStream.str();
		}
		catch (ifstream::failure e)
		{
			EG_CORE_ERROR("Unable to open shader file! {0}", fileName);
		}
		const char* code = codeString.c_str();

		return loadShader(code, type, fileName);
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