#include "Precompiled.h"

#include "Math/Matrix3x3.h"

namespace ivaldi {
	namespace math {
		Matrix3x3 Matrix3x3::identity = {
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f
		};
	}
}