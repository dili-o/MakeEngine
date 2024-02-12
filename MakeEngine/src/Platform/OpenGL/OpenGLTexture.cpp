#include "mkpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace MK {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		MK_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = channels == 4 ? GL_RGBA8 : GL_RGB8;
		GLenum dataFormat = channels == 4 ? GL_RGBA : GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		// Mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	inline uint32_t OpenGLTexture2D::GetSlot() const
	{
		// Convert m_Slot back to a normal unsinged int
		return (uint32_t)(m_Slot - GL_TEXTURE0);
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		// Convert m_Slot to the OpenGL texture slots
		m_Slot = GL_TEXTURE0 + (int)slot;
		glActiveTexture(m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}