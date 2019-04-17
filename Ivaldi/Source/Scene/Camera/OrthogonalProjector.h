#pragma once

#include "Scene/Camera/ICameraProjector.h"

namespace ivaldi {
	namespace scene {
		class OrthogonalProjector : public ICameraProjector {
		public:
			OrthogonalProjector() = default;
			~OrthogonalProjector() = default;

			math::Matrix4x4 getProjectionMatrix() const override;
		};
	}
}