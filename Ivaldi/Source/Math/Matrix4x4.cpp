#include "Precompiled.h"

#include "Math/Matrix4x4.h"

namespace ivaldi {
	namespace math {
		Matrix4x4 Matrix4x4::identity = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}
}