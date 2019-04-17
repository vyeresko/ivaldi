#pragma once

#include "Core.h"
#include "Math/Matrix4x4.h"
#include "Math/Point3.h"
#include "Math/Quaternion.h"

namespace ivaldi {
	namespace scene {
		class Transform {
		public:
			Transform() = default;
			~Transform() = default;
			
			void setPosition(const math::Point3& position) { m_position = position; }
			math::Point3 getPosition() const { return m_position; }
			
			void setRotation(math::Quaternion rotation) { m_rotation = rotation; }
			math::Quaternion getRotation() const { return m_rotation; }

			void setScale(float scale) { m_scale = scale; }
			float getScale() const { return m_scale; }

			math::Matrix4x4 getTransfomMatrix() const;
			
		private:
			math::Point3 m_position;
			math::Quaternion m_rotation;
			float m_scale; // uniform scale
		};
	}
}
