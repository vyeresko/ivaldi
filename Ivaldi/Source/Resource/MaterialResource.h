#pragma once

#include "Precompiled.h"

#include "Core.h"

#include "Resource/ShaderResource.h"
#include "Resource/TextureResource.h"

namespace ivaldi {
	namespace res {
		class MaterialResource {
		public:
			MaterialResource() = default;
			~MaterialResource() = default;

			void addTexture(std::shared_ptr<TextureResource> texture) { m_textures.push_back(texture); }
			std::shared_ptr<const TextureResource> getTexture(int index) const { return m_textures[index]; }
			size_t getTexturesNum() const { return m_textures.size(); }
			
			std::shared_ptr<const ShaderResource> getShader(ShaderType type) const { return m_shaders[type]; }
			void setShader(ShaderType type, std::shared_ptr<ShaderResource> shader_res) { m_shaders[type] = shader_res; }
			
		private:
			// gpu program
			std::array<std::shared_ptr<ShaderResource>, ShaderType::Count> m_shaders;

			// vector of textures pointers
			std::vector<std::shared_ptr<TextureResource>> m_textures;
		};
	}
}