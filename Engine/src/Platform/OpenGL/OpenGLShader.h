#pragma once
#include "Engine/Renderer/Shader.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		unsigned int texSlotCounter;
	private:
		unsigned int id;
		string name;

		unsigned int loadShader(const char* code, GLenum type, const char* fileName);
		unsigned int loadShader(const char* fileName, GLenum type);
		void loadShader(const char* fileName);
		
		void loadProgram(const std::unordered_map<GLenum, std::string>& shaderMap, const char* fileName);
		void loadProgram(unsigned int vertexId, unsigned int fragmentId, unsigned int geometryId);
	public:
		OpenGLShader();
		OpenGLShader(const OpenGLShader& shader);
		OpenGLShader(const char* shaderFile);
		OpenGLShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		OpenGLShader(int dummy, const char* shaderName, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);

		const std::string& GetName() const override { return name; }

		void compile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometricShaderFile = nullptr);
		void compile(int dummy, const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometricShaderCode = nullptr);
		void compile_debug(const char* vertexSource, const char* fragmentSource, const char* geometrySource);
		virtual ~OpenGLShader();
		unsigned int getId()const { return id; }
		void setId(unsigned int id) { this->id = id; }

		void checkCompileErrors(unsigned int object, std::string type);
		OpenGLShader& use();
		//void bindTextures(Texture* textures);
		//void bindTexture(Texture& texture, unsigned int idx);
		int getUniformLocation(const string& name) const;
		GLuint getUniformBlockIndex(const string& name) const;
		GLuint getUniformBlockIndex(const string& listName, const string& memberName, const unsigned int& idx) const;
		void uniformBlockBinding(GLuint uniformBlockIndex, int bindingPoint);

		void setBool(const string& name, bool value) const;
		void setBool(int location, bool value) const;

		void setInt(const string& name, int value) const;
		void setInt(const string& listName, const string& memberName, const int& value) const;
		void setInt(const string& listName, const string& memberName, int value, const unsigned int& idx) const;
		void setInt(int location, int value) const;
		void setInt_vector(const string& name, const vector<int> vec) const;
		void setInt_vector(const string& name, const int& value, const unsigned int& size) const;
		void setInt_vector(const string& listName, const string& memberName, const vector<int>& vec) const;
		void setInt_vector(const string& listName, const string& memberName, const int& value, const unsigned int& size) const;

		void setFloat(const string& name, float value) const;
		void setFloat(const string& listName, const string& memberName, const float& value) const;
		void setFloat(const string& listName, const string& memberName, float value, const unsigned int& idx) const;
		void setFloat(int location, float value) const;
		void setFloat_vector(const string& name, const vector<float>& vec) const;
		void setFloat_vector(const string& name, const float& value, const unsigned int& size) const;
		void setFloat_vector(const string& listName, const string& memberName, const vector<float>& vec) const;
		void setFloat_vector(const string& listName, const string& memberName, const float& value, const unsigned int& size) const;

		void set2fv(const string& name, const glm::vec2& vec) const;
		void set2fv(const string& listName, const string& memberName, const glm::vec2& vec) const;
		void set2fv(const string& listName, const string& memberName, const glm::vec2& vec, const unsigned int& idx) const;
		void set2fv(int location, const glm::vec2& vec) const;
		void set2f(const string& name, float v1, float v2) const;
		void set2f(int location, float v1, float v2) const;
		void set2fv_vector(const string& name, const vector<glm::vec2>& vec) const;
		void set2fv_vector(const string& name, const glm::vec2& vec, const unsigned int& size) const;
		void set2fv_vector(const string& listName, const string& memberName, const vector<glm::vec2>& vec) const;
		void set2fv_vector(const string& listName, const string& memberName, const glm::vec2& vec, const unsigned int& size) const;

		void set3fv(const string& name, const glm::vec3& vec) const;
		void set3fv(const string& listName, const string& memberName, const glm::vec3& vec) const;
		void set3fv(const string& listName, const string& memberName, const glm::vec3& vec, const unsigned int& idx) const;
		void set3fv(int location, const glm::vec3& vec) const;
		void set3f(const string& name, float v1, float v2, float v3) const;
		void set3f(int location, float v1, float v2, float v3) const;
		void set3fv_vector(const string& name, const vector<glm::vec3>& vec) const;
		void set3fv_vector(const string& name, const glm::vec3& vec, const unsigned int& size) const;
		void set3fv_vector(const string& listName, const string& memberName, const vector<glm::vec3>& vec) const;
		void set3fv_vector(const string& listName, const string& memberName, const glm::vec3& vec, const unsigned int& size) const;

		void set4fv(const string& name, const glm::vec4& vec) const;
		void set4fv(const string& listName, const string& memberName, const glm::vec4& vec) const;
		void set4fv(const string& listName, const string& memberName, const glm::vec4& vec, const unsigned int& idx) const;
		void set4fv(int location, const glm::vec4& vec) const;
		void set4f(const string& name, float v1, float v2, float v3, float v4) const;
		void set4f(int location, float v1, float v2, float v3, float v4) const;
		void set4fv_vector(const string& name, const vector<glm::vec4>& vec) const;
		void set4fv_vector(const string& name, const glm::vec4& vec, const unsigned int& size) const;
		void set4fv_vector(const string& listName, const string& memberName, const vector<glm::vec4>& vec) const;
		void set4fv_vector(const string& listName, const string& memberName, const glm::vec4& vec, const unsigned int& size) const;

		void setMat3fv(const string& name, const glm::mat3& mat, bool transpose = false) const;
		void setMat3fv(const string& listName, const string& memberName, const glm::mat3& mat, bool transpose = false) const;
		void setMat3fv(const string& listName, const string& memberName, const glm::mat3& mat, const unsigned int& idx, bool transpose = false) const;
		void setMat3fv(int location, const glm::mat3& mat, bool transpose = false) const;
		void setMat3fv_vector(const string& name, const vector<glm::mat3>& vec, bool transpose = false) const;
		void setMat3fv_vector(const string& name, const glm::mat3& mat, const unsigned int& size, bool transpose = false) const;
		void setMat3fv_vector(const string& listName, const string& memberName, const vector<glm::mat3>& vec, bool transpose = false) const;
		void setMat3fv_vector(const string& listName, const string& memberName, const glm::mat3& mat, const unsigned int& size, bool transpose = false) const;

		void setMat4fv(const string& name, const glm::mat4& mat, bool transpose = false) const;
		void setMat4fv(const string& listName, const string& memberName, const glm::mat4& mat, bool transpose = false) const;
		void setMat4fv(const string& listName, const string& memberName, const glm::mat4& mat, const unsigned int& idx, bool transpose = false) const;
		void setMat4fv(int location, const glm::mat4& mat, bool transpose = false) const;
		void setMat4fv_vector(const string& name, const vector<glm::mat4>& vec, bool transpose = false) const;
		void setMat4fv_vector(const string& name, const glm::mat4& mat, const unsigned int& size, bool transpose = false) const;
		void setMat4fv_vector(const string& listName, const string& memberName, const vector<glm::mat4>& vec, bool transpose = false) const;
		void setMat4fv_vector(const string& listName, const string& memberName, const glm::mat4& mat, const unsigned int& size, bool transpose = false) const;
	};
}

