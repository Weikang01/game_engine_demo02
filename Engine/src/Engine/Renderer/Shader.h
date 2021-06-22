#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Engine
{
	using std::string;
	using std::vector;

	typedef unsigned int GLenum;
	typedef unsigned int GLuint;

	class Shader
	{
	public:
		Shader() {}

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const char* shaderFile);
		static Ref<Shader> Create(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		static Ref<Shader> Create(int dummy, const char* shaderName, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);

		virtual void compile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		virtual void compile(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);
		virtual void compile_debug(const char* vertexSource, const char* fragmentSource, const char* geometrySource) = 0;
		virtual ~Shader() = default;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}