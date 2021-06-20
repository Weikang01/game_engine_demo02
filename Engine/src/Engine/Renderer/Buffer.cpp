#include "engine_pch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace Engine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
			break;
		}
		EG_CORE_ASSERT(false, "RendererAPI case is currently not supported!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		}
		EG_CORE_ASSERT(false, "RendererAPI case is currently not supported!");
		return nullptr;
	}
}