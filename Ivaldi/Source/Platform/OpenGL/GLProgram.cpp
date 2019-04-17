#include "Precompiled.h"
#include "GLProgram.h"

#include "Platform/OpenGL/GLShader.h"

#include "Log/Log.h"

namespace ivaldi {
	namespace gpu {
		GLProgram::GLProgram()
		{
			m_index = glCreateProgram();
		}

		GLProgram::~GLProgram()
		{
			glDeleteProgram(m_index);
		}

		void GLProgram::setShader(ShaderType type, std::shared_ptr<Shader> shader)
		{
			auto platform_shader = reinterpret_cast<GLShader*>(&*shader); // REDESIGN OR NOT??!!!
			glAttachShader(m_index, platform_shader->m_index);
		}
		
		void GLProgram::link()
		{
			glLinkProgram(m_index);

			GLint success;
			GLchar infoLog[1024];

			auto logger = Logger::get("Ivaldi");
			

			glGetProgramiv(m_index, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(m_index, 1024, NULL, infoLog);
				
				logger.error("PROGRAM_LINKING_FAILED::{0}", infoLog);
			}

			logger.info("PROGRAM_LINKING_SUCCEEDED"); // add some id to program 
		}

		void GLProgram::setVSUniformBuffer(const char* data, unsigned int size)
		{
			const GLfloat* formatted_data = (const GLfloat*)data;
			int location = glGetUniformLocation(m_index, "v_transform");
			glUniformMatrix4fv(location, 1, GL_TRUE, formatted_data);
		}

		void GLProgram::setPSUniformBuffer(const char* data, unsigned int size)
		{

		}
		
		void GLProgram::bind()
		{
			glUseProgram(m_index);
		}

		void GLProgram::unbind()
		{
			glUseProgram(0);
		}
	}
}