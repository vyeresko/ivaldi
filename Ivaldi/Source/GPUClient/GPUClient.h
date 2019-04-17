#pragma once

#include "GPUClient/GPUProgram.h"
#include "GPUClient/IndexBuffer.h"
#include "GPUClient/Texture.h"
#include "GPUClient/VertexArray.h"
#include "GPUClient/VertexBuffer.h"

namespace ivaldi {
	namespace gpu {
		class GPUClient {
		public:
			GPUClient() = default;
			~GPUClient() = default;
			
			void setVertexArray(std::shared_ptr<VertexArray> vertex_array) { m_active_varray = vertex_array; }
			void setProgram(std::shared_ptr<GPUProgram> gpu_program) { m_active_program = gpu_program; }
			void setTextures(const std::vector<std::shared_ptr<Texture>>& textures) { m_active_textures = textures; }

			void resetBuffers();
			void resetTextures();
			void resetProgram();

			virtual void clear() = 0;
			void draw();

			virtual void drawImp(int size) = 0;
			virtual void setViewport(unsigned short x, unsigned short y, unsigned short width, unsigned short height) = 0;
			virtual std::shared_ptr<VertexArray> createVertexArray() const = 0;
			virtual std::shared_ptr<VertexBuffer> createVertexBuffer() const = 0;
			virtual std::shared_ptr<IndexBuffer> createIndexBuffer() const = 0;
			virtual std::shared_ptr<GPUProgram> createGPUProgram() const = 0;
			virtual std::shared_ptr<Shader> createShader(ShaderType shader_type) const = 0;
			virtual std::shared_ptr<Texture> createTexture() const = 0;

		private:
			// TODO add const qualifiers to template args
			std::shared_ptr<VertexArray> m_active_varray;
			std::shared_ptr<GPUProgram> m_active_program;
			std::vector<std::shared_ptr<Texture>> m_active_textures;
		};
	}
}