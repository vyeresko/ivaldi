#pragma once

#include "Core.h"
#include "Math/Math.h"

namespace ivaldi {
	namespace math {

		class Vector4;

		class IVALDI_API Point4 {
		public:
			Point4() = default;

			explicit Point4(float c)
				:x(c), y(c), z(c), w(c)
			{}

			Point4(float x, float y, float z, float w)
				:x(x), y(y), z(z), w(w)
			{}

			Point4(const Point4& rhs)
				:x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
			{}

			inline Point4& operator=(const Point4& rhs);
			inline Point4 operator+(const Vector4& rhs) const;
			inline Vector4 operator-(const Point4& rhs) const;
			inline Point4 operator-(const Vector4& rhs) const;

			inline Point4& operator+=(const Vector4& rhs);
			inline Point4& operator-=(const Vector4& rhs);
			
			inline float& operator[](int i);
			inline const float operator[](int i) const;
			
			union {
				struct {
					float x, y, z, w;
				};

				float val[4];
			};
			
			static const Point4 zero;
			static const Point4 one;
		};

		class IVALDI_API Vector4 {
		public:
			Vector4() = default;

			explicit Vector4(float c)
				:x(c), y(c), z(c), w(c)
			{}

			Vector4(float x, float y, float z, float w)
				:x(x), y(y), z(z), w(w)
			{}

			Vector4(const Vector4& rhs)
				:x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
			{}

			Vector4& operator=(const Vector4& rhs)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;

				return *this;
			}

			Vector4 operator+(const Vector4& rhs) const
			{
				return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
			}

			Vector4 operator-(const Vector4& rhs) const
			{
				return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
			}

			Vector4 operator*(float c) const
			{
				return { x * c, y * c, z * c, w * c };
			}

			Vector4 operator/(float c) const
			{
				float c_inverse = 1.f / c;

				return { x * c_inverse, y * c_inverse, z * c_inverse, w * c_inverse };
			}

			Vector4& operator+=(const Vector4& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				w += rhs.w;

				return *this;
			}

			Vector4& operator-=(const Vector4& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				y -= rhs.z;
				w -= rhs.w;

				return *this;
			}

			Vector4& operator*=(float c)
			{
				x *= c;
				y *= c;
				y *= c;
				w *= c;

				return *this;
			}

			Vector4& operator/=(float c)
			{
				float c_inverse = 1.f / c;

				x *= c_inverse;
				y *= c_inverse;
				z *= c_inverse;
				w *= c_inverse;

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

			void normalize()
			{
				float length_inverse = 1.f / sqrt(length());

				x *= length_inverse;
				y *= length_inverse;
				z *= length_inverse;
				w *= length_inverse;
			}

			Vector4 normalized() const
			{
				float length_inverse = 1.f / sqrt(length());

				return { x * length_inverse, y * length_inverse, z * length_inverse, w * length_inverse };
			}

			float dot(const Vector4& v) const
			{
				return x * v.x + y * v.y + z * v.z + w * v.w;
			}

			static float dot(const Vector4& v0, const Vector4& v1)
			{
				return v0.dot(v1);
			}

			union {
				struct {
					float x, y, z, w;
				};

				float val[4];
			};

			static const Vector4 zero;
			static const Vector4 one;
		};
		

		// ** Point4 definition ** //

		Point4& Point4::operator=(const Point4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;

			return *this;
		}

		Point4 Point4::operator+(const Vector4& rhs) const
		{
			return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
		}

		Vector4 Point4::operator-(const Point4& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
		}

		Point4 Point4::operator-(const Vector4& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
		}

		Point4& Point4::operator+=(const Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		Point4& Point4::operator-=(const Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		float& Point4::operator[](int i)
		{
			return val[i];
		}

		const float Point4::operator[](int i) const
		{
			return val[i];
		}
	}
}