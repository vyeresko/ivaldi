#pragma once

#include "Scene/Mesh.h"
#include "Scene/Transform.h"

namespace ivaldi {
	
	// FWD DEC
	namespace gpu {
		class GPUClient;
	}

	namespace scene {
		class Entity {
		public:
			void addMesh(std::shared_ptr<Mesh> mesh) { m_meshes.push_back(mesh); }
			Mesh& getMesh(size_t index) { return *m_meshes[index]; }

			size_t getMeshesCount() const { return m_meshes.size(); }

			void update(float delta);
			
			Transform transform;

		private:
			std::vector<std::shared_ptr<Mesh>> m_meshes;
			
		};
	}
}