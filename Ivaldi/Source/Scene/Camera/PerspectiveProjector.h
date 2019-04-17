#pragma once

#include "Scene/Camera/ICameraProjector.h"

namespace ivaldi {
	namespace scene {
		class PerspectiveProjector : public ICameraProjector {
		public:
			PerspectiveProjector() = default;
			~PerspectiveProjector() = default;

			math::Matrix4x4 getProjectionMatrix() const override;
		};
	}
}