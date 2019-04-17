#pragma once

#include "Core.h"
#include "Math/Math.h"

namespace ivaldi {
	namespace math {
		class IVALDI_API Quaternion {
		public:
			Quaternion() = default;
			Quaternion(float w, float x, float y, float z)
				:w(w), x(x), y(y), z(z)
			{}

			Quaternion(const Quaternion& rhs)
				:w(rhs.w), x(rhs.x), y(rhs.y), z(rhs.z)
			{}

			Quaternion& operator=(const Quaternion& rhs)
			{
				w = rhs.w;
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;

				return *this;
			}

			Quaternion operator+(const Quaternion& rhs) const
			{
				return {
					w + rhs.w,
					x + rhs.x,
					y + rhs.y,
					z + rhs.z
				};
			}

			Quaternion operator-(const Quaternion& rhs) const
			{
				return {
					w - rhs.w,
					x - rhs.x,
					y - rhs.y,
					z - rhs.z
				};
			}

			Quaternion operator*(const Quaternion& rhs) const
			{
				return {
					w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
					w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
					w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
					w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x
				};
			}

			Quaternion operator*(float c) const
			{
				return {
					w * c,
					x * c,
					y * c,
					z * c
				};
			}

			Quaternion& operator+=(const Quaternion& rhs)
			{
				w += rhs.w;
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;

				return *this;
			}

			Quaternion& operator-=(const Quaternion& rhs)
			{
				w -= rhs.w;
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;

				return *this;
			}

			Quaternion& operator*=(const Quaternion& rhs)
			{
				w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
				x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
				y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
				z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;

				return *this;
			}

			float& operator[](int i)
			{
				return val[i];
			}

			const float operator[](int i) const
			{
				return val[i];
			}

			float length() const
			{
				return Math::sqrt(lengthSquared());
			}

			float lengthSquared() const
			{
				return x * x + y * y + z * z + w * w;
			}

			Quaternion conjugate() const
			{
				return { w, -x, -y, -z };
			}

			bool inverse(Quaternion& inverse_out) const
			{
				auto length_squared = lengthSquared();

				if (length_squared == 0)
					return false;

				inverse_out = conjugate() *  (1 / length_squared);

				return true;
			}

			static Quaternion identity;

		private:
			union {
				struct {
					float w, x, y, z;
				};

				float val[4];
			};
		};
	}
}