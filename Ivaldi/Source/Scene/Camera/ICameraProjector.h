#pragma once

#include "Math/Matrix4x4.h"

namespace ivaldi {
	namespace scene {
		class ICameraProjector {
		public:
			virtual ~ICameraProjector() = default;

			virtual math::Matrix4x4 getProjectionMatrix() const = 0;	
		};
	}
}