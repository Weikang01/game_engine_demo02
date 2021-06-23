#pragma once
#include "RenderCommand.h"

#include "OrthographicCamera.h"

namespace Engine
{
	class Shader;

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMat;
		};

		static SceneData* m_SceneData;
	};
}
