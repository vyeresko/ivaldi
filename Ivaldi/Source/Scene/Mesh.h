#pragma once

#include "Precompiled.h"
#include "Core.h"

#include "GPUClient/GPUClient.h"
#include "GPUClient/VertexArray.h"
#include "GPUClient/VertexBuffer.h"
#include "GPUClient/IndexBuffer.h"


#include "Scene/Material.h"
#include "Resource/MeshResource.h"

namespace ivaldi {
	namespace scene {
		class IVALDI_API Mesh {
		public:
			Mesh() = default;
			~Mesh() = default;
			
			std::shared_ptr<Material> getMaterial() const { return m_material; }
			void setMaterial(std::shared_ptr<Material> material) { m_material = material; }

			std::shared_ptr<gpu::VertexArray> getVertexArray() const { return m_vertex_array; }
			void setVertexArray(std::shared_ptr<gpu::VertexArray> vertex_array) { m_vertex_array = vertex_array; }
			
		private:
			std::shared_ptr<gpu::VertexArray> m_vertex_array;
			
			std::shared_ptr<Material> m_material;
		};
	}
}