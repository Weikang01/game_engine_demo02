#pragma once
#include "RenderCommand.h"

#include "OrthographicCamera.h"

namespace Engine
{
	class Shader;

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMat;
		};

		static SceneData* m_SceneData;
	};
}
