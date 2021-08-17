#include "engine_pch.h"
#include "Renderer2D.h"

#include "Engine/Renderer/RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <glm/ext/matrix_transform.hpp>

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DStorage* s_data;

	void Renderer2D::Init()
	{
		s_data = new Renderer2DStorage();

		s_data->vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-.5f, -.5f, .0f, 0.0f, 0.0f,
			 .5f, -.5f, .0f, 1.0f, 0.0f,
			 .5f,  .5f, .0f, 1.0f, 1.0f,
			-.5f,  .5f, .0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout squareLayout =
		{
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
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

		s_data->flatColorShader = Shader::Create("assets/shaders/flatColorShader.glsl");
		s_data->textureShader = Shader::Create("assets/shaders/textureShader.glsl");

	}

	void Renderer2D::ShutDown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_data->flatColorShader->setMat4fv("viewProjMat", camera.GetViewProjectionMatrix());
		s_data->textureShader->setMat4fv("viewProjMat", camera.GetViewProjectionMatrix());
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
		s_data->flatColorShader->set4fv("color", color);

		s_data->flatColorShader->setMat4fv("modelMat", glm::scale(glm::translate(glm::mat4(1.f), position), glm::vec3(size.x, size.y, 1.f)));
		s_data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.f), size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{

		s_data->textureShader->setMat4fv("modelMat", glm::scale(glm::translate(glm::mat4(1.f), position), glm::vec3(size.x, size.y, 1.f)));

		texture->Bind();
		s_data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->vertexArray);
	}
}