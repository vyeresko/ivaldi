#pragma once

#include <glad/glad.h>

#include "GPUClient/IndexBuffer.h"

namespace ivaldi {
	namespace gpu {
		class GLIndexBuffer : public IndexBuffer {
		public:
			GLIndexBuffer();
			~GLIndexBuffer();

			void copyData(const std::vector<unsigned int> &data) override;
			int getSize() const override;
			
			void bind() override;
			void unbind() override;

		private:
			GLuint m_index;
			GLsizei m_size;
		};

	}
}
