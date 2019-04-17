#pragma once

#include "Core.h"
#include "Math/Math.h"

namespace ivaldi {
	namespace math {

		class Vector2;

		class IVALDI_API Point2 {
		public:
			Point2() = default;

			explicit Point2(float c)
				:x(c), y(c)
			{}

			Point2(float x, float y)
				:x(x), y(y)
			{}

			Point2(const Point2& rhs)
				:x(rhs.x), y(rhs.y)
			{}

			inline Point2& operator=(const Point2& rhs);
			inline Point2 operator+(const Vector2& rhs) const;
			inline Vector2 operator-(const Point2& rhs) const;
			inline Point2 operator-(const Vector2& rhs) const;
			inline Point2& operator+=(const Vector2& rhs);
			inline Point2& operator-=(const Vector2& rhs);
			inline float& operator[](int i);
			inline const float operator[](int i) const;
			
			union {
				struct {
					float x, y;
				};

				float val[2];
			};

			static const Point2 zero;
			static const Point2 one;
		};

		class IVALDI_API Vector2 {
		public:
			Vector2() = default;

			explicit Vector2(float c)
				:x(c), y(c)
			{}

			Vector2(float x, float y)
				:x(x), y(y)
			{}

			Vector2(const Vector2& rhs)
				:x(rhs.x), y(rhs.y)
			{}

			Vector2& operator=(const Vector2& rhs)
			{
				x = rhs.x;
				y = rhs.y;

				return *this;
			}

			Vector2 operator+(const Vector2& rhs) const
			{
				return { x + rhs.x, y + rhs.y };
			}

			Point2 operator+(const Point2& rhs) const
			{
				return { x + rhs.x, y + rhs.y };
			}

			Vector2 operator-(const Vector2& rhs) const
			{
				return { x - rhs.x, y - rhs.y };
			}

			Point2 operator-(const Point2& rhs) const
			{
				return { x - rhs.x, y - rhs.y };
			}

			Vector2 operator*(float c) const
			{
				return { x * c, y * c };
			}

			Vector2 operator/(float c) const
			{
				float c_inverse = 1.f / c;

				return { x * c_inverse, y * c_inverse };
			}

			Vector2& operator+=(const Vector2& rhs)
			{
				x += rhs.x;
				y += rhs.y;

				return *this;
			}

			Vector2& operator-=(const Vector2& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;

				return *this;
			}

			Vector2& operator*=(float c)
			{
				x *= c;
				y *= c;

				return *this;
			}

			Vector2& operator/=(float c)
			{
				float c_inverse = 1.f / c;
				x *= c_inverse;
				y *= c_inverse;

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
				return x * x + y * y;
			}

			void normalize()
			{
				float length_inverse = 1.f / sqrt(length());

				x *= length_inverse;
				y *= length_inverse;
			}

			Vector2 normalized() const
			{
				float length_inverse = 1.f / sqrt(length());

				return { x * length_inverse, y * length_inverse };
			}

			float dot(const Vector2& v) const
			{
				return x * v.x + y * v.y;
			}

			static float dot(const Vector2& v0, const Vector2& v1)
			{
				return v0.dot(v1);
			}

			union {
				struct {
					float x, y;
				};

				float val[2];
			};

			static const Vector2 zero;
			static const Vector2 one;
		};

		// ** Point4 definition ** //

		Point2& Point2::operator=(const Point2& rhs)
		{
			x = rhs.x;
			y = rhs.y;

			return *this;
		}

		Point2 Point2::operator+(const Vector2& rhs) const
		{
			return { x + rhs.x, y + rhs.y };
		}

		Vector2 Point2::operator-(const Point2& rhs) const
		{
			return { x - rhs.x, y - rhs.y };
		}

		Point2 Point2::operator-(const Vector2& rhs) const
		{
			return { x - rhs.x, y - rhs.y };
		}

		Point2& Point2::operator+=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Point2& Point2::operator-=(const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		float& Point2::operator[](int i)
		{
			return val[i];
		}

		const float Point2::operator[](int i) const
		{
			return val[i];
		}
	}
}
