#pragma once

#include "assimp/include/assimp/Importer.hpp"
#include "assimp/include/assimp/scene.h"
#include "assimp/include/assimp/postprocess.h"

#include "Core.h"

#include "Platform/Assimp/AssimpResourceIterator.h"

#include "Resource/ISceneLoader.h"
#include "Resource/MaterialResource.h"
#include "Resource/MeshResource.h"
#include "Resource/TextureResource.h"

namespace ivaldi {
	class MaterialSystem;

	class IVALDI_API AssimpSceneLoader : public res::ISceneLoader {
	public:
		friend class AssimpResourceIterator;

		AssimpSceneLoader(const MaterialSystem& material_system);
		void load(const std::string& path) override;
		void unload() override;
		res::IResourceIterator* getIterator() const override;

	private:
		void processNode(aiNode *node, const aiScene *scene);
		std::shared_ptr<res::MeshResource> processMesh(aiMesh *mesh, const aiScene *scene);
		std::shared_ptr<res::MaterialResource> processMaterial(aiMaterial *material, VertexAttribute channels);
		void processTexture(aiMaterial *material, aiTextureType texture_type, res::MaterialResource &material_res_out);

		bool m_is_loaded = false;

		// TODO:
		// USE set of shared pointers instead of map
		std::map <int, std::shared_ptr<res::MaterialResource>> m_materials_registry;
		std::map <int, std::shared_ptr<res::MeshResource>> m_meshes_registry;
		std::map <std::string, std::shared_ptr<res::TextureResource>> m_textures_registry;

		const MaterialSystem& m_material_system;

		// TEMP:
		// two shaders shared 
		// between all materials
		std::shared_ptr<res::ShaderResource> m_vertex_res;
		std::shared_ptr<res::ShaderResource> m_pixel_res;

		res::ResourceBundle m_bundle_res;
	};
}