#pragma once

#include "Precompiled.h"

namespace ivaldi {
	namespace res {
		class MeshResource;

		class ResourceBundle {
		public:
			ResourceBundle() = default;
			~ResourceBundle() = default;
			
			void pushMesh(std::shared_ptr<MeshResource> mesh) { m_meshes.push_back(mesh); }
			std::shared_ptr<const MeshResource> getMesh(size_t index) const { return m_meshes[index]; }
			size_t getMeshCount() const { return m_meshes.size(); }
			
		private:
			std::vector<std::shared_ptr<MeshResource>> m_meshes;
		};
	}
}