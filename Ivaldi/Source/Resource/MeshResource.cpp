#include "Precompiled.h"

#include "MeshResource.h"

namespace ivaldi {
	namespace res {

		bool MeshResource::hasChannel(VertexAttribute channel) const
		{
			return MESH_CHECK_FLAG(m_channels, channel);
		}

		void MeshResource::addPosition(const math::Point3& point) 
		{
			IVALDI_ASSERT(MESH_CHECK_FLAG(m_channels, VertexAttribute::Position), "Channels inconsistency! Position is not set!");
			m_vertices.push_back(point.x);
			m_vertices.push_back(point.y);
			m_vertices.push_back(point.z);
		}

		void MeshResource::addNormal(const math::Point3& normal) 
		{
			IVALDI_ASSERT(MESH_CHECK_FLAG(m_channels, VertexAttribute::Normal), "Channels inconsistency! Normal is not set!");
			m_vertices.push_back(normal.x);
			m_vertices.push_back(normal.y);
			m_vertices.push_back(normal.z);
		}

		void MeshResource::addTexCoord(const math::Point2& tex_coord) 
		{
			IVALDI_ASSERT(MESH_CHECK_FLAG(m_channels, VertexAttribute::Texture), "Channels inconsistency! Texture is not set!");
			m_vertices.push_back(tex_coord.x);
			m_vertices.push_back(tex_coord.y);
		}

		void MeshResource::addIndex(unsigned int index)
		{
			m_indices.push_back(index);
		}
	}
}