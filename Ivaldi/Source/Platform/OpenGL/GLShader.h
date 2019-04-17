#pragma once

#include "Core.h"
#include "GPUClient/Shader.h"

#include <glad/glad.h>

namespace ivaldi {
	namespace gpu {
		class GLShader: public Shader {
		public:
			friend class GLProgram;

			GLShader(ShaderType shader_type);
			~GLShader();
			
			void setSource(const std::string& source) override;
			void compile() override;

			static GLenum getShaderType(ShaderType shader_type);

		private:
			int m_index;
		};
	}
	
}