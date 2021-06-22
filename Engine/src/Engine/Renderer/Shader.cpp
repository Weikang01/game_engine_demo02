#include "engine_pch.h"
#include "Shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Engine
{
	Ref<Shader> Shader::Create(const char* shaderFile)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(shaderFile);
			break;
		}
		EG_CORE_ASSERT(false, "Shader case is currently not supported!");
	}

	Ref<Shader> Shader::Create(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexShaderFile, fragmentShaderFile, geometricShaderFile);
			break;
		}
		EG_CORE_ASSERT(false, "Shader case is currently not supported!");
	}

	Ref<Shader> Shader::Create(int dummy, const char* shaderName, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(dummy, shaderName, vertexShaderCode, fragmentShaderCode, geometricShaderCode);
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

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		EG_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		EG_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[shader->GetName()] = shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath.c_str());
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath.c_str());
		Add(name, shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		EG_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}