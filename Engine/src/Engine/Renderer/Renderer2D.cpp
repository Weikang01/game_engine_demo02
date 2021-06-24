#include "engine_pch.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Engine/Renderer/RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <glm/ext/matrix_transform.hpp>

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DStorage* s_data;

	void Renderer2D::Init()
	{
		s_data = new Renderer2DStorage();

		s_data->vertexArray = VertexArray::Create();

		float squareVertices[3 * 4] =
		{
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout squareLayout =
		{
			{ShaderDataType::Float3, "a_Position"},
		};
		squareVB->SetLayout(squareLayout);
		s_data->vertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] =
		{
			0,1,2,2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_data->vertexArray->SetIndexBuffer(squareIB);

		s_data->shader = Shader::Create("assets/shaders/flatColorTexture.glsl");

	}

	void Renderer2D::ShutDown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader> (s_data->shader)->setMat4fv("viewProjMat", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader> (s_data->shader)->set4fv("color", color);
		s_data->vertexArray->Bind();
		std::dynamic_pointer_cast<OpenGLShader> (s_data->shader)->setMat4fv("modelMat", glm::scale(glm::translate(glm::mat4(1.f), position), glm::vec3(size.x, size.y, 1.f)));
		RenderCommand::DrawIndexed(s_data->vertexArray);
	}
}