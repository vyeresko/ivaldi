#pragma once

#include "Core.h"
#include "Shader.h"

namespace ivaldi {
	namespace gpu {
		class GPUProgram {
		public:
			friend class GPUClient;

			virtual void setShader(ShaderType type, std::shared_ptr<Shader> shader) = 0;
			
			virtual void link() = 0;
			
			virtual void setVSUniformBuffer(const char* data, unsigned int size) = 0;
			virtual void setPSUniformBuffer(const char* data, unsigned int size) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;
		};
	}
}
