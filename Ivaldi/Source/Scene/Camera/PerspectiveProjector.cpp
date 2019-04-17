#include "Precompiled.h"
#include "PerspectiveProjector.h"

namespace ivaldi {
	namespace scene {
		math::Matrix4x4 PerspectiveProjector::getProjectionMatrix() const
		{
			const float n = 2;
			const float f = 20;

			const float r = 3;
			const float l = -3;
			const float t = 5;
			const float b = -5;

			math::Matrix4x4 projection(
				(2 * n) / (r - l), 0, (r + l) / (r - l), 0,
				0, (2 * n) / (t - b), (t + b) / (t - b), 0,
				0, 0, -(f + n) / (f - n), (-2 * f * n) / (f - n),
				0, 0, -1, 0
			);

			return projection;
		}
	}
}