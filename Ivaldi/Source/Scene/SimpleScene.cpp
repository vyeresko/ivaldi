#include "Precompiled.h"
#include "SimpleScene.h"

#include "Resource/ISceneLoader.h"

#include "Core.h"

namespace ivaldi {
	namespace scene {
		void SimpleScene::parse(const std::string& path, res::ISceneLoader& scene_loader)
		{
			scene_loader.load(path);

			auto res_it = scene_loader.getIterator();

			while(res_it->hasNext()) {
				m_entites.push_back(m_scene_parser->getEntity(res_it->get()));
				res_it->advance();
			}
		}

		void SimpleScene::update(float delta)
		{
			for (auto& entity : m_entites)
				entity.update(delta);
		}
		
		void SimpleScene::render(gpu::GPUClient& gpu_client, float delta)
		{
			gpu_client.clear();

			for (auto& entity : m_entites) {
				for (size_t i = 0; i < entity.getMeshesCount(); ++i) {
					auto mesh = entity.getMesh(i);

					auto gpu_program = mesh.getMaterial()->getGPUProgram();
					gpu_client.setProgram(gpu_program);

					// Setup uniforms
					/*auto transform = (m_camera.getViewProjMatrix() * entity.transform.getTransfomMatrix());
					auto ptr = math::Matrix4x4::identity.getPtr();
					gpu_program->setVSUniformBuffer((const char*)ptr, 64);*/
					
					gpu_client.setTextures(mesh.getMaterial()->getTextures());
					gpu_client.setVertexArray(mesh.getVertexArray());

					gpu_client.draw();

					gpu_client.resetProgram();
					gpu_client.resetBuffers();
					gpu_client.resetTextures();
				}
			}	
		}
	}
}
