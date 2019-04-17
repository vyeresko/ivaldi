#pragma once

#include "Precompiled.h"

#include "Core.h"
#include "Math/Point2.h"
#include "Math/Point3.h"

#define MESH_CHECK_FLAG(flag, channel) (flag & channel) == channel

namespace ivaldi {
	namespace res {
		
		class MaterialResource;

		class MeshResource {
		public:
			MeshResource() = default;
			MeshResource(std::shared_ptr<MaterialResource> material)
				: m_material(material)
			{}
			
			void setChannels(VertexAttribute channels) { m_channels = channels; }
			bool hasChannel(VertexAttribute channel) const;
			
			std::shared_ptr<const MaterialResource> getMaterial() const { return m_material; }
			void setMaterial(std::shared_ptr<MaterialResource> material) { m_material = material; }
			
			void addPosition(const math::Point3& point);
			void addNormal(const math::Point3& normal);
			void addTexCoord(const math::Point2& tex_coord);
			void addIndex(unsigned int index);

			const std::vector<float>& getVertices() const { return m_vertices; }
			const std::vector<unsigned int>& getIndices() const { return m_indices; }
			
		private:
			VertexAttribute m_channels; // channels are represented as a bit flag
			std::shared_ptr<MaterialResource> m_material;

			std::vector<float> m_vertices; // vertex attributes tightly packed (channels)
			std::vector<unsigned int> m_indices;
		};
	}
}