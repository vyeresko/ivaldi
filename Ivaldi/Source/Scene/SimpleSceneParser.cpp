#include "Precompiled.h"

#include "SimpleSceneParser.h"

#include "GPUClient/GPUClient.h"
#include "GPUClient/ShaderInputLayout.h"
#include "Resource/MaterialResource.h"
#include "Resource/ResourceBundle.h"
#include "Resource/TextureResource.h"

namespace ivaldi {
	namespace scene {
		Entity SimpleSceneParser::getEntity(const res::ResourceBundle& res_bundle)
		{
			Entity entity;

			for (size_t i = 0; i < res_bundle.getMeshCount(); ++i) {
				auto mesh_res = res_bundle.getMesh(i);
				auto mesh_it = m_meshes_registry.find(mesh_res);

				if (mesh_it != m_meshes_registry.end())
					entity.addMesh(mesh_it->second);
				else {
					auto mesh = createMesh(mesh_res);
					m_meshes_registry.insert(make_pair(mesh_res, mesh));
					entity.addMesh(mesh);
				}
			}

			return entity;
		}
		
		std::shared_ptr<Mesh> SimpleSceneParser::createMesh(std::shared_ptr<const res::MeshResource> mesh_res)
		{
			auto mesh = std::make_shared<Mesh>();

			mesh->setVertexArray(createVertexArray(mesh_res));
			
			auto material_res = mesh_res->getMaterial();
			auto material_it = m_materials_registry.find(material_res);

			if (material_it != m_materials_registry.end())
				mesh->setMaterial(material_it->second);
			else {
				auto material = createMaterial(material_res);
				m_materials_registry.insert(make_pair(material_res, material));
				mesh->setMaterial(material);
			}
			
			return mesh;
		}

		std::shared_ptr<gpu::VertexArray> SimpleSceneParser::createVertexArray(std::shared_ptr<const res::MeshResource> mesh_res)
		{
			auto vertex_array = m_gpu_client.createVertexArray();
			vertex_array->setVertexBuffer(createVertexBuffer(mesh_res));
			vertex_array->setIndexBuffer(createIndexBuffer(mesh_res));
			
			// TODO:
			// calculate stride
			gpu::ShaderInputLayout input_layout;

			if (mesh_res->hasChannel(VertexAttribute::Position))
				input_layout.addAttribute({ VertexAttribute::Position , 3, 0, 3 * sizeof(float) });

			if (mesh_res->hasChannel(VertexAttribute::Normal))
				input_layout.addAttribute({ VertexAttribute::Normal , 3, 3 * sizeof(float), 8 * sizeof(float) });

			if (mesh_res->hasChannel(VertexAttribute::Texture))
				input_layout.addAttribute({ VertexAttribute::Texture , 2, 6 * sizeof(float), 8 * sizeof(float) });

			vertex_array->setInputLayout(input_layout);

			return vertex_array;
		}

		std::shared_ptr<gpu::VertexBuffer> SimpleSceneParser::createVertexBuffer(std::shared_ptr<const res::MeshResource> mesh_res)
		{
			auto vertex_buffer = m_gpu_client.createVertexBuffer();
			vertex_buffer->copyData(mesh_res->getVertices());

			return vertex_buffer;
		}

		std::shared_ptr<gpu::IndexBuffer> SimpleSceneParser::createIndexBuffer(std::shared_ptr<const res::MeshResource> mesh_res)
		{
			auto index_buffer = m_gpu_client.createIndexBuffer();
			index_buffer->copyData(mesh_res->getIndices());

			return index_buffer;
		}

		std::shared_ptr<Material> SimpleSceneParser::createMaterial(std::shared_ptr<const res::MaterialResource> material_res)
		{
			auto material = std::make_shared<Material>();
			// TODO:
			// check for gpu program
			material->setGPUProgram(createGPUProgram(material_res));
			
			// Process textures
			for (size_t i = 0; i < material_res->getTexturesNum(); ++i) {
				auto texture_res = material_res->getTexture(i);

				auto texture_it = m_textures_registry.find(texture_res);
				if (texture_it != m_textures_registry.end())
					material->addTexture(texture_it->second);
				else {
					auto texture = createTexture(texture_res);
					m_textures_registry.insert(make_pair(texture_res, texture));
					material->addTexture(texture);
				}
			}

			return material;
		}

		std::shared_ptr<gpu::GPUProgram> SimpleSceneParser::createGPUProgram(std::shared_ptr<const res::MaterialResource> material_res)
		{

			auto gpu_program = m_gpu_client.createGPUProgram();
			{
				// Process vertex shader
				auto vertex_shader_res = material_res->getShader(ShaderType::Vertex);
				auto vertex_shader_it = m_shaders_registry.find(vertex_shader_res);
				if (vertex_shader_it != m_shaders_registry.end())
					gpu_program->setShader(ShaderType::Vertex, vertex_shader_it->second);
				else {
					auto vertex_shader = createShader(vertex_shader_res);
					m_shaders_registry.insert(make_pair(vertex_shader_res, vertex_shader));
					gpu_program->setShader(ShaderType::Vertex, vertex_shader);
				}
			}

			{
				// Process pixel shader
				auto pixel_shader_res = material_res->getShader(ShaderType::Pixel);
				auto pixel_shader_it = m_shaders_registry.find(pixel_shader_res);
				if (pixel_shader_it != m_shaders_registry.end())
					gpu_program->setShader(ShaderType::Pixel, pixel_shader_it->second);
				else {
					auto pixel_shader = createShader(pixel_shader_res);
					m_shaders_registry.insert(make_pair(pixel_shader_res, pixel_shader));
					gpu_program->setShader(ShaderType::Pixel, pixel_shader);
				}
			}

			gpu_program->link();

			return gpu_program;
		}

		std::shared_ptr<gpu::Shader> SimpleSceneParser::createShader(std::shared_ptr<const res::ShaderResource> shader_res)
		{
			auto shader = m_gpu_client.createShader(shader_res->getType());
			shader->setSource(shader_res->getSource());
			shader->compile();

			return shader;
		}

		std::shared_ptr<gpu::Texture> SimpleSceneParser::createTexture(std::shared_ptr<const res::TextureResource> texture_res)
		{
			auto texture = m_gpu_client.createTexture();
			texture->setWidth(texture_res->getWidth());
			texture->setHeight(texture_res->getHeight());
			texture->setChannels(texture_res->getChannelsNum());
			texture->copyData(texture_res->getData(), texture_res->getWidth(), texture_res->getHeight());
			return texture;
		}
	}
}
