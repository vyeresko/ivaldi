#pragma once

#include "GPUClient/VertexBuffer.h"

#include <glad/glad.h>

namespace ivaldi {
	namespace gpu {
		class GLVertexBuffer : public VertexBuffer {
		public:
			GLVertexBuffer();
			~GLVertexBuffer();

			void copyData(const std::vector<float> &data) override;

			void bind() override;
			void unbind() override;

		private:
			GLuint m_index;
			ShaderInputLayout m_input_layout;
		};

	}
}

