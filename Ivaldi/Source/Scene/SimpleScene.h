#pragma once

#include "Precompiled.h"
#include "Core.h"

#include "Scene/Camera/Camera.h"
#include "Scene/Entity.h"
#include "Scene/ISceneParser.h"

namespace ivaldi {

	// FWD DEC
	namespace res {
		class ISceneLoader;
	}

	// FWD DEC
	namespace gpu {
		class GPUClient;
	}

	namespace scene {
		class ISceneParser;
		
		class IVALDI_API SimpleScene {
		public:
			SimpleScene(ivaldi::scene::ISceneParser* scene_parser, const Camera::CameraParams& camera_params)
				: m_scene_parser(scene_parser), m_camera(camera_params)
			{}

			~SimpleScene()
			{
				if (m_scene_parser)
					delete m_scene_parser;
			}
			
			const ISceneParser& getSceneParser() const { return *m_scene_parser; }
			void setSceneParser(ISceneParser* scene_parser) { m_scene_parser = scene_parser; }

			Camera& getCamera() { return m_camera; }
			
			void parse(const std::string& path, res::ISceneLoader& scene_loader);

			void update(float delta);
			void render(gpu::GPUClient& gpu_client, float delta);

		private:
			ivaldi::scene::ISceneParser* m_scene_parser;
			std::vector<Entity> m_entites;
			Camera m_camera;
		};
	}
}