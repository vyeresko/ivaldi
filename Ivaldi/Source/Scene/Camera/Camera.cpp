#include "Precompiled.h"
#include "Camera.h"

namespace ivaldi {
	namespace scene {
		math::Matrix4x4 Camera::getViewProjMatrix() const
		{
			math::Matrix4x4 view(
				1.f , 0.f, 0.f, m_position.x,
				0.f, 1.f, 0.f, m_position.y,
				0.f, 0.f, 1.f, m_position.z,
				0.f, 0.f, 0.f, 1.f
			);
			return view * m_projector->getProjectionMatrix();
		}

		void Camera::resetCamera()
		{
			// Setup camera type
			switch (m_type) {
			case CameraType::Orthogonal:
				m_projector = std::make_unique<OrthogonalProjector>();
				break;
			case CameraType::Perspective:
				m_projector = std::make_unique<PerspectiveProjector>();
				break;
			default:
				break;
			}
		}
	}
}
