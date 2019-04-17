#include "Precompiled.h"
#include "GLTexture.h"

namespace ivaldi {
	namespace gpu {
		GLTexture::GLTexture()
		{
			glGenTextures(1, &m_index);
		}
		
		GLTexture::~GLTexture()
		{
			glDeleteTextures(1, &m_index);
		}

		void GLTexture::copyData(const unsigned char *data, const unsigned short width, const unsigned short height)
		{
			glBindTexture(GL_TEXTURE_2D, m_index);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		void GLTexture::bind(unsigned short unit)
		{
			glActiveTexture(unit);
			glBindTexture(GL_TEXTURE_2D, m_index);
		}

		void GLTexture::unbind()
		{
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}