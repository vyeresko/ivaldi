#pragma once

#include "GPUClient/VertexArray.h"

#include <glad/glad.h>

namespace ivaldi {
	namespace gpu {
		class GLVertexArray : public VertexArray {
		public:
			GLVertexArray();
			~GLVertexArray();
			
			void setInputLayout(const ShaderInputLayout& input_layout) override;
			
			void bind() override;
			void unbind() override;

		private:
			GLuint m_index;
		};
	}
}
