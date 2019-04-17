#pragma once

#include "Core.h"
#include "GPUClient/GPUClient.h"

namespace ivaldi {
	namespace gpu {
		class IVALDI_API GLClient : public GPUClient {
		public:
			GLClient();
			~GLClient() = default;

			void clear() override;
			void drawImp(int size) override;
			void setViewport(unsigned short x, unsigned short y, unsigned short width, unsigned short height) override;
			std::shared_ptr<VertexArray> createVertexArray() const override;
			std::shared_ptr<VertexBuffer> createVertexBuffer() const override;
			std::shared_ptr<IndexBuffer> createIndexBuffer() const override;
			std::shared_ptr<Texture> createTexture() const override;
			std::shared_ptr<Shader> createShader(ShaderType type) const override;
			std::shared_ptr<GPUProgram> createGPUProgram() const override;

		private:
			unsigned int vao_index_test;
			unsigned int program_test;

			std::shared_ptr<VertexArray> m_varray;
			std::shared_ptr<GPUProgram> m_gpu_program;
		};
	}
}
