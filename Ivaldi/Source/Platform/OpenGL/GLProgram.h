#pragma once

#include <glad/glad.h>

#include "GPUClient/GPUProgram.h"

namespace ivaldi {
	namespace gpu {
		class GLProgram : public GPUProgram {
		public:
			GLProgram();
			~GLProgram();

			virtual void setShader(ShaderType type, std::shared_ptr<Shader> shader) override;
			virtual void link() override;
			
			void setVSUniformBuffer(const char* data, unsigned int size) override;
			void setPSUniformBuffer(const char* data, unsigned int size) override;
			
			void bind() override;
			void unbind() override;

		private:
			GLuint m_index;
		};

	}
}
