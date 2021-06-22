#include "engine_pch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Engine
{
	OpenGLTexture2D::OpenGLTexture2D(const char* path)
		:m_Path(path)
	{
		int width, height, channel;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path, &width, &height, &channel, 0);

		EG_CORE_ASSERT(data, "Failed to loat image!");
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, GL_RGB8, width, height);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum colorChannelArray[]{ GL_FALSE, GL_RED, GL_RG, GL_RGB, GL_RGBA };

		glTextureSubImage2D(m_ID, 0, 0, 0, width, height, colorChannelArray[channel], GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}
}