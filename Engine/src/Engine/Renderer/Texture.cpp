#include "engine_pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine
{
	Ref<Texture2D> Texture2D::Create(const char* path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
			break;
		}
		EG_CORE_ASSERT(false, "RendererAPI case is currently not supported!");
		return nullptr;
	}
}