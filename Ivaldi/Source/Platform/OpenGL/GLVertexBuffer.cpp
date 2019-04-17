#include "Precompiled.h"
#include "GLVertexBuffer.h"

namespace ivaldi {
	namespace gpu {
		GLVertexBuffer::GLVertexBuffer()
		{
			glGenBuffers(1, &m_index);
		}

		GLVertexBuffer::~GLVertexBuffer()
		{
			glDeleteBuffers(1, &m_index);
		}

		void GLVertexBuffer::copyData(const std::vector<float> &data)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_index);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
		void GLVertexBuffer::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_index);
		}

		void GLVertexBuffer::unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
