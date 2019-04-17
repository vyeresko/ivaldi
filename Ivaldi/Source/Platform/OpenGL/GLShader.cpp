#include "Precompiled.h"
#include "GLShader.h"

#include "Log/Log.h"

namespace ivaldi {
	namespace gpu {
		GLShader::GLShader(ShaderType shader_type)
		{
			m_index = glCreateShader(getShaderType(shader_type));
		}

		GLShader::~GLShader()
		{
			glDeleteShader(m_index);
		}

		void GLShader::setSource(const std::string& source)
		{
			const char* source_char = source.c_str();
			glShaderSource(m_index, 1, &source_char, NULL);
		}

		void GLShader::compile()
		{
			glCompileShader(m_index);

			GLint success;
			GLchar infoLog[1024];

			auto logger = Logger::get("Ivaldi");
			

			glGetShaderiv(m_index, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_index, 1024, NULL, infoLog);

				logger.error("SHADER_COMPILATION_FAILED::{0}", infoLog);
			}

			logger.info("SHADER_COMPILATION_SUCCEEDED"); // add some id to shader
		}

		GLenum GLShader::getShaderType(ShaderType shader_type)
		{
			switch (shader_type) {
			case ShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case ShaderType::Geometry:
				return GL_GEOMETRY_SHADER;
			case ShaderType::Pixel:
				return GL_FRAGMENT_SHADER;
				
			default: {
				auto logger = Logger::get("Ivaldi");
				logger.warn("Could not convert shader type to gl specific type: {0}", shader_type);
				return 0;
				}
			}
		}
	}
}