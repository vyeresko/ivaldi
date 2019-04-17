#pragma once

#include "Core.h"
#include "Scene/ISceneParser.h"

namespace ivaldi {
	
	// FWD DEC
	namespace res {
		class MeshResource;
		class MaterialResource;
		class ShaderResource;
		class TextureResource;
	}
	
	// FWD DEC
	namespace gpu {
		class GPUClient;
		class VertexBuffer;
	}

	namespace scene {
		class IVALDI_API SimpleSceneParser : public ISceneParser {
		public:
			SimpleSceneParser(const gpu::GPUClient &gpu_client)
				: m_gpu_client(gpu_client)
			{}
			
			Entity getEntity(const res::ResourceBundle& res_bundle) override;

		private:
			std::shared_ptr<Mesh> createMesh(std::shared_ptr<const res::MeshResource>);
			std::shared_ptr<gpu::VertexArray> createVertexArray(std::shared_ptr<const res::MeshResource>);
			std::shared_ptr<gpu::VertexBuffer> createVertexBuffer(std::shared_ptr<const res::MeshResource>);
			std::shared_ptr<gpu::IndexBuffer> createIndexBuffer(std::shared_ptr<const res::MeshResource>);
			std::shared_ptr<Material> createMaterial(std::shared_ptr<const res::MaterialResource>);
			std::shared_ptr<gpu::GPUProgram> createGPUProgram(std::shared_ptr<const res::MaterialResource>);
			std::shared_ptr<gpu::Shader> createShader(std::shared_ptr<const res::ShaderResource>);
			std::shared_ptr<gpu::Texture> createTexture(std::shared_ptr<const res::TextureResource>);
			
			std::map<std::shared_ptr<const res::MeshResource>, std::shared_ptr<scene::Mesh>> m_meshes_registry;
			std::map<std::shared_ptr<const res::MaterialResource>, std::shared_ptr<scene::Material>> m_materials_registry;
			std::map<std::shared_ptr<const res::ShaderResource>, std::shared_ptr<gpu::Shader>> m_shaders_registry;
			std::map<std::shared_ptr<const res::TextureResource>, std::shared_ptr<gpu::Texture>> m_textures_registry;

			const gpu::GPUClient& m_gpu_client;
		};
	}
}