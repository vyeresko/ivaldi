#include "Precompiled.h"
#include "GLIndexBuffer.h"

#include "glad/glad.h"

namespace ivaldi {
	namespace gpu {
		GLIndexBuffer::GLIndexBuffer()
		{
			glGenBuffers(1, &m_index);
		}
			
		GLIndexBuffer::~GLIndexBuffer()
		{
			glDeleteBuffers(1, &m_index);
		}
		
		void GLIndexBuffer::copyData(const std::vector<unsigned int> &data)
		{
			m_size = data.size();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		int GLIndexBuffer::getSize() const
		{
			return m_size;
		}

		void GLIndexBuffer::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
		}

		void GLIndexBuffer::unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}

