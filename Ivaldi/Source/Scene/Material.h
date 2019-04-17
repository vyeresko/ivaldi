#pragma once
#include "Precompiled.h"

#include "Core.h"
#include "GPUClient/GPUProgram.h"
#include "GPUClient/Texture.h"

namespace ivaldi {
	namespace scene {
		class IVALDI_API Material {
		public:
			Material() = default;
			~Material() = default;

			std::shared_ptr<gpu::GPUProgram> getGPUProgram() { return m_program; }
			void setGPUProgram(std::shared_ptr<gpu::GPUProgram> gpu_program) { m_program = gpu_program; }
			
			const std::vector<std::shared_ptr<gpu::Texture>>& getTextures() const { return m_textures; }
			void addTexture(std::shared_ptr<gpu::Texture> texture) { m_textures.push_back(texture); }

		private:
			std::shared_ptr<gpu::GPUProgram> m_program;
			std::vector<std::shared_ptr<gpu::Texture>> m_textures;
		};
	}
}