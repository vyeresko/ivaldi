#pragma once

#include "Scene/Camera/ICameraProjector.h"
#include "Scene/Camera/OrthogonalProjector.h"
#include "Scene/Camera/PerspectiveProjector.h"

#include "Math/Matrix4x4.h"
#include "Math/Point3.h"
#include "Math/Quaternion.h"

namespace ivaldi {
	namespace scene {
		
		// FWD DEC
		class ICameraProjector;

		class IVALDI_API Camera {
		public:
			enum class CameraType {
				Orthogonal,
				Perspective
			};

			struct CameraParams {
				math::Point3 position;
				math::Quaternion rotation;
				CameraType type;
			};
			
			Camera(const CameraParams& params)
				: m_position(params.position), 
				  m_rotation(params.rotation),
				  m_type(params.type)
			{
				resetCamera();
			}

			~Camera() = default;
			
			CameraType getCameraType() const { return m_type; }
			void setCameraType(CameraType type) { m_type = type; resetCamera(); }
			
			math::Point3 getPosition() const { return m_position; }
			void setPosition(const math::Point3& position) { m_position = position; }

			math::Quaternion getRotation() const { return m_rotation; }
			void setRotation(const math::Quaternion& rotation) { m_rotation = rotation; }
			
			math::Matrix4x4 getViewProjMatrix() const;
			
		private:
			void resetCamera();

			CameraType m_type;
			math::Point3 m_position;
			math::Quaternion m_rotation;
			std::unique_ptr<ICameraProjector> m_projector;
		};
	}
}
