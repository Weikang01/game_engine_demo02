#include "engine_pch.h"
#include "Renderer.h"
#include <Engine/Renderer/Shader.h>


namespace Engine
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMat = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->use();
        shader->setMat4fv("viewProjMat", m_SceneData->ViewProjectionMat);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}