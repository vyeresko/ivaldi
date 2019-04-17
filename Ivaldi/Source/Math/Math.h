#pragma once

#include <cmath>

#include "Core.h"

namespace ivaldi { 
	namespace math {
		class IVALDI_API Math {
		public:
			Math() = delete;

			static float pow(float x, float exp)
			{
				return std::pow(x, exp);
			}

			static float sqrt(float x)
			{
				return std::sqrt(x);
			}
		};
	}
}