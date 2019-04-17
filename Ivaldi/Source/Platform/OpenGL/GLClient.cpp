#include "Precompiled.h"
#include "GLClient.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "Log/Log.h"
#include "Platform/OpenGL/GLVertexArray.h"
#include "Platform/OpenGL/GLIndexBuffer.h"
#include "Platform/OpenGL/GLVertexBuffer.h"
#include "Platform/OpenGL/GLProgram.h"
#include "Platform/OpenGL/GLShader.h"
#include "Platform/OpenGL/GLTexture.h"
#include "Platform/OpenGL/GLMaterialSystem.h"

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

namespace ivaldi {
	namespace gpu {

		GLClient::GLClient()
		{

			auto logger = Logger::get("Ivaldi");
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				auto logger = Logger::get("Ivaldi");
				logger.error("OpenGL Client::Failed to initialize glad");
				throw std::exception("OpenGL Client::Failed to initialize ");
			}

			GLMaterialSystem system;
			
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glEnable(GL_DEPTH_TEST);


			auto vertex_shader = createShader(ShaderType::Vertex);
			vertex_shader->setSource(system.createVertexShaderSrc(VertexAttribute::None, ""));
			vertex_shader->compile();

			auto pixel_shader = createShader(ShaderType::Pixel);
			pixel_shader->setSource(system.createPixelShaderSrc(VertexAttribute::None, ""));
			pixel_shader->compile();

			m_gpu_program = createGPUProgram();
			m_gpu_program->setShader(ShaderType::Vertex, vertex_shader);
			m_gpu_program->setShader(ShaderType::Pixel, pixel_shader);
			m_gpu_program->link();
			
			m_varray = createVertexArray();
			
			auto vbo = createVertexBuffer();
			auto ebo = createIndexBuffer();
			
			std::vector<float> vertices = {
				-0.5f, -0.5f, 0.f, // bottom-left
				-0.5f, 0.5f, 0.f, // top-left
				0.5f, 0.5f, 0.f, // top-right
				0.5f, -0.5f, 0.f // bottom-right
			};

			std::vector<unsigned int> indices = {
				0, 1, 2,
				2, 3, 0
			};
			
			vbo->copyData(vertices);
			ebo->copyData(indices);

			m_varray->setVertexBuffer(vbo);
			m_varray->setIndexBuffer(ebo);

			ShaderInputLayout input_layout;

			input_layout.addAttribute({ VertexAttribute::Position, 3, 0, 3 * sizeof(float) });

			m_varray->setInputLayout(input_layout);
		}

		void GLClient::setViewport(unsigned short x, unsigned short y, unsigned short width, unsigned short height)
		{
			glViewport(x, y, width, height);
		}

		void GLClient::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void GLClient::drawImp(int size)
		{
			//m_gpu_program->bind();
			// m_varray->bind();
			
			glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

			//m_varray->unbind();
			//m_gpu_program->unbind();
		}

		std::shared_ptr<VertexArray> GLClient::createVertexArray() const
		{
			return std::make_shared<GLVertexArray>();
		}
		
		std::shared_ptr<VertexBuffer> GLClient::createVertexBuffer() const
		{
			return std::make_shared<GLVertexBuffer>();
		}

		std::shared_ptr<IndexBuffer> GLClient::createIndexBuffer() const
		{
			return std::make_shared<GLIndexBuffer>();
		}

		std::shared_ptr<GPUProgram> GLClient::createGPUProgram() const
		{
			return std::make_shared<GLProgram>();
 		}

		std::shared_ptr<Shader> GLClient::createShader(ShaderType shader_type) const
		{
			return std::make_shared<GLShader>(shader_type);
		}

		std::shared_ptr<Texture> GLClient::createTexture() const
		{
			return std::make_shared<GLTexture>();
		}
	}
}
