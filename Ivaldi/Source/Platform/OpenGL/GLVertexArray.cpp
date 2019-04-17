#include "Precompiled.h"
#include "GLVertexArray.h"

#include "Core.h"
#include "GPUClient/VertexBuffer.h"
#include "GPUClient/IndexBuffer.h"

namespace ivaldi {
	namespace gpu {
		GLVertexArray::GLVertexArray()
		{
			glGenVertexArrays(1, &m_index);
		}

		GLVertexArray::~GLVertexArray()
		{
			glDeleteBuffers(1, &m_index);
		}
		
		void GLVertexArray::setInputLayout(const ShaderInputLayout& input_layout)
		{
			IVALDI_ASSERT(m_vbuffer, "Set vertex buffer before layout");
			IVALDI_ASSERT(m_ibuffer, "Set index buffer before layout");

			glBindVertexArray(m_index);

			m_vbuffer->bind();
			m_ibuffer->bind();
			
			for (auto& shader_input : input_layout.getLayout()) {
				int index = log2((int)shader_input.vertex_attribute);

				glVertexAttribPointer(index, shader_input.size, GL_FLOAT, GL_FALSE, shader_input.stride, (const void*)shader_input.offset);
				glEnableVertexAttribArray(index);
			}

			glBindVertexArray(0);

			m_vbuffer->unbind();
			m_ibuffer->unbind();
		}

		void GLVertexArray::bind()
		{
			glBindVertexArray(m_index);
		}

		void GLVertexArray::unbind()
		{
			glBindVertexArray(0);
		}
	}
}