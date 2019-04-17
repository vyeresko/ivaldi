#pragma once

#include "Core.h"
#include "Math/Math.h"

namespace ivaldi {
	namespace math {

		class Vector3;

		class IVALDI_API Point3 {
		public:
			Point3() = default;

			explicit Point3(float c)
				:x(c), y(c), z(c)
			{}

			Point3(float x, float y, float z)
				:x(x), y(y), z(z)
			{}

			Point3(const Point3& rhs)
				:x(rhs.x), y(rhs.y), z(rhs.z)
			{}
			
			inline Point3& operator=(const Point3& rhs);
			inline Point3 operator+(const Vector3& rhs) const;
			inline Vector3 operator-(const Point3& rhs) const;
			inline Point3 operator-(const Vector3& rhs) const;

			inline Point3& operator+=(const Vector3& rhs);
			inline Point3& operator-=(const Vector3& rhs);
			
			inline float& operator[](int i);
			inline const float operator[](int i) const;
			
			union {
				struct {
					float x, y, z;
				};

				float val[3];
			};


			static const Point3 zero;
			static const Point3 one;
		};

		class IVALDI_API Vector3 {
		public:
			Vector3() = default;

			explicit Vector3(float c)
				:x(c), y(c), z(c)
			{}

			Vector3(float x, float y, float z)
				:x(x), y(y), z(z)
			{}

			Vector3(const Vector3& rhs)
				:x(rhs.x), y(rhs.y), z(rhs.z)
			{}
			
			Vector3& operator=(const Vector3& rhs)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;

				return *this;
			}
			
			Vector3 operator+(const Vector3& rhs) const
			{
				return { x + rhs.x, y + rhs.y, z + rhs.z };
			}

			Point3 operator+(const Point3& rhs) const
			{
				return { x + rhs.x, y + rhs.y, z + rhs.z };
			}

			Vector3 operator-(const Vector3& rhs) const
			{
				return { x - rhs.x, y - rhs.y, z - rhs.z };
			}

			Vector3 operator*(float c) const
			{
				return { x * c, y * c, z * c };
			}

			Vector3 operator/(float c) const
			{
				float c_inverse = 1.f / c;

				return { x * c_inverse, y * c_inverse, z * c_inverse };
			}

			Vector3& operator+=(const Vector3& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;

				return *this;
			}

			Vector3& operator-=(const Vector3& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				y -= rhs.z;

				return *this;
			}

			Vector3& operator*=(float c)
			{
				x *= c;
				y *= c;
				y *= c;

				return *this;
			}

			Vector3& operator/=(float c)
			{
				float c_inverse = 1.f / c;

				x *= c_inverse;
				y *= c_inverse;
				z *= c_inverse;

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
				return x * x + y * y + z * z;
			}

			void normalize()
			{
				float length_inverse = 1.f / sqrt(length());

				x *= length_inverse;
				y *= length_inverse;
				z *= length_inverse;
			}

			Vector3 normalized() const
			{
				float length_inverse = 1.f / sqrt(length());

				return { x * length_inverse, y * length_inverse, z * length_inverse };
			}

			float dot(const Vector3& v) const
			{
				return x * v.x + y * v.y + z * v.z;
			}

			Vector3 cross(const Vector3& v) const
			{
				return {
					y * v.z - v.y * z,
					z * v.x - v.z * x,
					x * v.y - v.x * y
				};
			}

			static float dot(const Vector3& v0, const Vector3& v1)
			{
				return v0.dot(v1);
			}

			static Vector3 cross(const Vector3& v0, const Vector3& v1)
			{
				return v0.cross(v1);
			}

			union {
				struct {
					float x, y, z;
				};

				float val[3];
			};


			static const Vector3 zero;
			static const Vector3 one;
		};


		// ** Point3 definition ** //

		Point3& Point3::operator=(const Point3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		
		Point3 Point3::operator+(const Vector3& rhs) const
		{
			return { x + rhs.x, y + rhs.y, z + rhs.z };
		}

		Vector3 Point3::operator-(const Point3& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z };
		}

		Point3 Point3::operator-(const Vector3& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z };
		}

		Point3& Point3::operator+=(const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Point3& Point3::operator-=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		float& Point3::operator[](int i)
		{
			return val[i];
		}

		const float Point3::operator[](int i) const
		{
			return val[i];
		}
	}
}

