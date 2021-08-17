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

		virtual int getUniformLocation(const string& name) const = 0;
		virtual GLuint getUniformBlockIndex(const string& name) const = 0;
		virtual GLuint getUniformBlockIndex(const string& listName, const string& memberName, const unsigned int& idx) const = 0;
		virtual void uniformBlockBinding(GLuint uniformBlockIndex, int bindingPoint) = 0;

		virtual void setBool(const string& name, bool value) const = 0;
		virtual void setBool(int location, bool value) const = 0;

		virtual void setInt(const string& name, int value) const = 0;
		virtual void setInt(const string& listName, const string& memberName, const int& value) const = 0;
		virtual void setInt(const string& listName, const string& memberName, int value, const unsigned int& idx) const = 0;
		virtual void setInt(int location, int value) const = 0;
		virtual void setInt_vector(const string& name, const vector<int> vec) const = 0;
		virtual void setInt_vector(const string& name, const int& value, const unsigned int& size) const = 0;
		virtual void setInt_vector(const string& listName, const string& memberName, const vector<int>& vec) const = 0;
		virtual void setInt_vector(const string& listName, const string& memberName, const int& value, const unsigned int& size) const = 0;

		virtual void setFloat(const string& name, float value) const = 0;
		virtual void setFloat(const string& listName, const string& memberName, const float& value) const = 0;
		virtual void setFloat(const string& listName, const string& memberName, float value, const unsigned int& idx) const = 0;
		virtual void setFloat(int location, float value) const = 0;
		virtual void setFloat_vector(const string& name, const vector<float>& vec) const = 0;
		virtual void setFloat_vector(const string& name, const float& value, const unsigned int& size) const = 0;
		virtual void setFloat_vector(const string& listName, const string& memberName, const vector<float>& vec) const = 0;
		virtual void setFloat_vector(const string& listName, const string& memberName, const float& value, const unsigned int& size) const = 0;

		virtual void set2fv(const string& name, const glm::vec2& vec) const = 0;
		virtual void set2fv(const string& listName, const string& memberName, const glm::vec2& vec) const = 0;
		virtual void set2fv(const string& listName, const string& memberName, const glm::vec2& vec, const unsigned int& idx) const = 0;
		virtual void set2fv(int location, const glm::vec2& vec) const = 0;
		virtual void set2f(const string& name, float v1, float v2) const = 0;
		virtual void set2f(int location, float v1, float v2) const = 0;
		virtual void set2fv_vector(const string& name, const vector<glm::vec2>& vec) const = 0;
		virtual void set2fv_vector(const string& name, const glm::vec2& vec, const unsigned int& size) const = 0;
		virtual void set2fv_vector(const string& listName, const string& memberName, const vector<glm::vec2>& vec) const = 0;
		virtual void set2fv_vector(const string& listName, const string& memberName, const glm::vec2& vec, const unsigned int& size) const = 0;

		virtual void set3fv(const string& name, const glm::vec3& vec) const = 0;
		virtual void set3fv(const string& listName, const string& memberName, const glm::vec3& vec) const = 0;
		virtual void set3fv(const string& listName, const string& memberName, const glm::vec3& vec, const unsigned int& idx) const = 0;
		virtual void set3fv(int location, const glm::vec3& vec) const = 0;
		virtual void set3f(const string& name, float v1, float v2, float v3) const = 0;
		virtual void set3f(int location, float v1, float v2, float v3) const = 0;
		virtual void set3fv_vector(const string& name, const vector<glm::vec3>& vec) const = 0;
		virtual void set3fv_vector(const string& name, const glm::vec3& vec, const unsigned int& size) const = 0;
		virtual void set3fv_vector(const string& listName, const string& memberName, const vector<glm::vec3>& vec) const = 0;
		virtual void set3fv_vector(const string& listName, const string& memberName, const glm::vec3& vec, const unsigned int& size) const = 0;

		virtual void set4fv(const string& name, const glm::vec4& vec) const = 0;
		virtual void set4fv(const string& listName, const string& memberName, const glm::vec4& vec) const = 0;
		virtual void set4fv(const string& listName, const string& memberName, const glm::vec4& vec, const unsigned int& idx) const = 0;
		virtual void set4fv(int location, const glm::vec4& vec) const = 0;
		virtual void set4f(const string& name, float v1, float v2, float v3, float v4) const = 0;
		virtual void set4f(int location, float v1, float v2, float v3, float v4) const = 0;
		virtual void set4fv_vector(const string& name, const vector<glm::vec4>& vec) const = 0;
		virtual void set4fv_vector(const string& name, const glm::vec4& vec, const unsigned int& size) const = 0;
		virtual void set4fv_vector(const string& listName, const string& memberName, const vector<glm::vec4>& vec) const = 0;
		virtual void set4fv_vector(const string& listName, const string& memberName, const glm::vec4& vec, const unsigned int& size) const = 0;

		virtual void setMat3fv(const string& name, const glm::mat3& mat, bool transpose = false) const = 0;
		virtual void setMat3fv(const string& listName, const string& memberName, const glm::mat3& mat, bool transpose = false) const = 0;
		virtual void setMat3fv(const string& listName, const string& memberName, const glm::mat3& mat, const unsigned int& idx, bool transpose = false) const = 0;
		virtual void setMat3fv(int location, const glm::mat3& mat, bool transpose = false) const = 0;
		virtual void setMat3fv_vector(const string& name, const vector<glm::mat3>& vec, bool transpose = false) const = 0;
		virtual void setMat3fv_vector(const string& name, const glm::mat3& mat, const unsigned int& size, bool transpose = false) const = 0;
		virtual void setMat3fv_vector(const string& listName, const string& memberName, const vector<glm::mat3>& vec, bool transpose = false) const = 0;
		virtual void setMat3fv_vector(const string& listName, const string& memberName, const glm::mat3& mat, const unsigned int& size, bool transpose = false) const = 0;

		virtual void setMat4fv(const string& name, const glm::mat4& mat, bool transpose = false) const = 0;
		virtual void setMat4fv(const string& listName, const string& memberName, const glm::mat4& mat, bool transpose = false) const = 0;
		virtual void setMat4fv(const string& listName, const string& memberName, const glm::mat4& mat, const unsigned int& idx, bool transpose = false) const = 0;
		virtual void setMat4fv(int location, const glm::mat4& mat, bool transpose = false) const = 0;
		virtual void setMat4fv_vector(const string& name, const vector<glm::mat4>& vec, bool transpose = false) const = 0;
		virtual void setMat4fv_vector(const string& name, const glm::mat4& mat, const unsigned int& size, bool transpose = false) const = 0;
		virtual void setMat4fv_vector(const string& listName, const string& memberName, const vector<glm::mat4>& vec, bool transpose = false) const = 0;
		virtual void setMat4fv_vector(const string& listName, const string& memberName, const glm::mat4& mat, const unsigned int& size, bool transpose = false) const = 0;
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