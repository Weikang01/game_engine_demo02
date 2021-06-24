#include "engine_pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
			break;
		}
		EG_CORE_ASSERT(false, "RendererAPI case is currently not supported!");
		return nullptr;
	}
}
