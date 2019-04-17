#include "Precompiled.h"

#include "AssimpSceneLoader.h"

#include "Core.h"

#include "MaterialSystem/MaterialSystem.h"

#include "Platform/Assimp/AssimpResourceIterator.h"
#include "Resource/ShaderResource.h"

#include "Log/Log.h"

namespace ivaldi {

	AssimpSceneLoader::AssimpSceneLoader(const MaterialSystem& material_system)
		: m_material_system(material_system)
	{
		m_vertex_res = std::make_shared<res::ShaderResource>(ShaderType::Vertex);
		m_vertex_res->setSource(m_material_system.createVertexShaderSrc(VertexAttribute::None, ""));
		
		m_pixel_res = std::make_shared<res::ShaderResource>(ShaderType::Pixel);
		m_pixel_res->setSource(m_material_system.createPixelShaderSrc(VertexAttribute::None, ""));
	}

	void AssimpSceneLoader::load(const std::string& path)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		auto logger = Logger::get("Ivaldi");

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			//logger.error("ASSIMP::scene load failed::{0}", import.GetErrorString());
			return;
		}

		logger.info("ASSIMP::scene finished to load");
		logger.info("ASSIMP::start parsing...");

		processNode(scene->mRootNode, scene);

		m_is_loaded = true;
	}

	void AssimpSceneLoader::unload()
	{
		m_is_loaded = false;
	}

	res::IResourceIterator* AssimpSceneLoader::getIterator() const 
	{
		return new AssimpResourceIterator(*this);
	}
	
	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void AssimpSceneLoader::processNode(aiNode *node, const aiScene *scene)
	{
		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {

			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).

			auto mesh_it = m_meshes_registry.find(node->mMeshes[i]);

			if (mesh_it != m_meshes_registry.end())
				m_bundle_res.pushMesh(mesh_it->second);
			else {
				auto mesh_res = processMesh(scene->mMeshes[node->mMeshes[i]], scene);
				m_bundle_res.pushMesh(mesh_res);
				// Add mesh id (path) to registry.
				m_meshes_registry.insert(std::make_pair(node->mMeshes[i], mesh_res));
			}
		}

		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}

	std::shared_ptr<res::MeshResource> AssimpSceneLoader::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		// Setup channels
		auto channels = VertexAttribute::None;

		if (mesh->HasPositions())
			channels = (channels | VertexAttribute::Position);

		/*if (mesh->HasNormals())
			channels = (channels | VertexAttribute::Normal);

		if (mesh->HasTextureCoords(0))
			channels = (channels | VertexAttribute::Texture);*/

		auto mesh_res = std::make_shared<res::MeshResource>();
		mesh_res->setChannels(channels);
		
		// Process geometry
		for (decltype(mesh->mNumVertices) i = 0; i < mesh->mNumVertices; ++i) {
			if (MESH_CHECK_FLAG(channels, VertexAttribute::Position)) {
				math::Point3 position;
				position.x = mesh->mVertices[i].x;
				position.y = mesh->mVertices[i].y;
				position.z = mesh->mVertices[i].z;
				mesh_res->addPosition(position);
			}

			/*if (MESH_CHECK_FLAG(channels, VertexAttribute::Normal)) {
				math::Point3 normal;
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;
				mesh_res->addNormal(normal);
			}
			
			if (MESH_CHECK_FLAG(channels, VertexAttribute::Texture)) {
				math::Point2 texture_coords;
				texture_coords.x = mesh->mTextureCoords[0][i].x;
				texture_coords.y = mesh->mTextureCoords[0][i].y;
				mesh_res->addTexCoord(texture_coords);
			}*/
		}

		for (decltype(mesh->mNumFaces) i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];
			for (decltype(face.mNumIndices) j = 0; j < face.mNumIndices; ++j)
				mesh_res->addIndex(face.mIndices[j]);
		}
		
		// Process material
		auto material_it = m_materials_registry.find(mesh->mMaterialIndex);
		
		if (material_it != m_materials_registry.end())
			mesh_res->setMaterial(material_it->second);
		else {
			auto material_res = processMaterial(scene->mMaterials[mesh->mMaterialIndex], channels);
			mesh_res->setMaterial(material_res);
			// Add material id (path) to registry.
			m_materials_registry.insert(std::make_pair(mesh->mMaterialIndex, material_res));
		}

		return mesh_res;
	}

	std::shared_ptr<res::MaterialResource> AssimpSceneLoader::processMaterial(aiMaterial *material, VertexAttribute channels)
	{
		auto material_res = std::make_shared<res::MaterialResource>();
		
		// Setup shaders
		material_res->setShader(ShaderType::Vertex, m_vertex_res);
		material_res->setShader(ShaderType::Pixel, m_pixel_res);
		

		// process diffuse
		processTexture(material, aiTextureType_DIFFUSE, *material_res);
		// process specular
		processTexture(material, aiTextureType_SPECULAR, *material_res);

		return material_res;
	}

	void AssimpSceneLoader::processTexture(aiMaterial *material, aiTextureType texture_type, res::MaterialResource &material_res_out)
	{
		for (unsigned int i = 0; i < material->GetTextureCount(texture_type); ++i) {
			aiString path;
			material->GetTexture(texture_type, i, &path);

			auto texture_res_it = m_textures_registry.find(path.C_Str());

			if (texture_res_it != m_textures_registry.end())
				material_res_out.addTexture(texture_res_it->second);
			else {
				auto texture_res = std::make_shared<res::TextureResource>(path.C_Str());
				texture_res->load();
				material_res_out.addTexture(texture_res);
				// Add texture id (path) to registry.
				m_textures_registry.insert(std::make_pair(path.C_Str(), texture_res));
			}
		}
	}
}