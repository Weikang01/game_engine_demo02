#include "engine_pch.h"
#include "Renderer.h"
#include <Engine/Renderer/Shader.h>
#include <Platform/OpenGL/OpenGLShader.h>

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

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
    {
        std::dynamic_pointer_cast<OpenGLShader> (shader)->use();
        std::dynamic_pointer_cast<OpenGLShader> (shader)->setMat4fv("modelMat", transform);
        std::dynamic_pointer_cast<OpenGLShader> (shader)->setMat4fv("viewProjMat", m_SceneData->ViewProjectionMat);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}