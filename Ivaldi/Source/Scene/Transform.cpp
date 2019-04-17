#include "Precompiled.h"
#include "Transform.h"

namespace ivaldi {
	namespace scene {
		math::Matrix4x4 Transform::getTransfomMatrix() const
		{
			math::Matrix4x4 matrix(
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 5.f,
				0.f, 0.f, 0.f, 1.f
			);

			return matrix;
		}
	}
}
