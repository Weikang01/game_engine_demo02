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
	protected:

		virtual unsigned int loadShader(const char* code, GLenum type, const char* fileName) = 0;
		virtual unsigned int loadShader(const char* fileName, GLenum type);
	public:
		Shader() {}

		static Shader* Create(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		static Shader* Create(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);

		virtual void compile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		virtual void compile(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);
		virtual void compile_debug(const char* vertexSource, const char* fragmentSource, const char* geometrySource) = 0;
		virtual ~Shader() = default;
	};

}