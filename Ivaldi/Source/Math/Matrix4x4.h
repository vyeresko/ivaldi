#pragma once

#include "Core.h"
#include "Math/Point4.h"

namespace ivaldi {
	namespace math {
		class IVALDI_API Matrix4x4 {
		public:
			Matrix4x4() = default;

			Matrix4x4(
				const Vector4& v0,
				const Vector4& v1,
				const Vector4& v2,
				const Vector4& v3)
			{
				m_val[0] = v0;
				m_val[1] = v1;
				m_val[2] = v2;
				m_val[3] = v3;
			}

			Matrix4x4(
				float x0, float x1, float x2, float x3,
				float y0, float y1, float y2, float y3,
				float z0, float z1, float z2, float z3,
				float w0, float w1, float w2, float w3)
			{
				m_val[0] = Vector4(x0, y0, z0, w0);
				m_val[1] = Vector4(x1, y1, z1, w1);
				m_val[2] = Vector4(x2, y2, z2, w2);
				m_val[3] = Vector4(x3, y3, z3, w3);
			}

			Matrix4x4(const Matrix4x4& rhs)
			{
				m_val[0] = rhs[0];
				m_val[1] = rhs[1];
				m_val[2] = rhs[2];
				m_val[3] = rhs[3];
			}

			Matrix4x4(Matrix4x4&& rhs)
			{

			}

			Matrix4x4 operator+(const Matrix4x4& rhs) const
			{
				return {
					m_val[0] + rhs[0],
					m_val[1] + rhs[1],
					m_val[2] + rhs[2],
					m_val[3] + rhs[3]
				};
			}

			Matrix4x4 operator-(const Matrix4x4& rhs) const
			{
				return {
					m_val[0] - rhs[0],
					m_val[1] - rhs[1],
					m_val[2] - rhs[2],
					m_val[3] - rhs[3]
				};
			}

			Matrix4x4 operator*(const Matrix4x4& rhs) const
			{
				return {
					m_val[0] * rhs[0].x + m_val[1] * rhs[0].y + m_val[2] * rhs[0].z + m_val[3] * rhs[0].w,
					m_val[0] * rhs[1].x + m_val[1] * rhs[1].y + m_val[2] * rhs[1].z + m_val[3] * rhs[1].w,
					m_val[0] * rhs[2].x + m_val[1] * rhs[2].y + m_val[2] * rhs[2].z + m_val[3] * rhs[2].w,
					m_val[0] * rhs[3].x + m_val[1] * rhs[3].y + m_val[2] * rhs[3].z + m_val[3] * rhs[3].w
				};
			}

			Matrix4x4 operator*(float c) const
			{
				return {
					m_val[0] * c,
					m_val[1] * c,
					m_val[2] * c,
					m_val[3] * c
				};
			}

			Vector4& operator[](int i)
			{
				return m_val[i];
			}

			const Vector4& operator[](int i) const
			{
				return m_val[i];
			}

			Matrix4x4& operator+=(const Matrix4x4& rhs)
			{
				m_val[0] += rhs[0];
				m_val[1] += rhs[1];
				m_val[2] += rhs[2];
				m_val[3] += rhs[3];

				return *this;
			}

			Matrix4x4& operator-=(const Matrix4x4& rhs)
			{
				m_val[0] -= rhs[0];
				m_val[1] -= rhs[1];
				m_val[2] -= rhs[2];
				m_val[3] -= rhs[3];

				return *this;
			}

			Matrix4x4& operator*=(const Matrix4x4& rhs)
			{
				m_val[0] = m_val[0] * rhs[0].x + m_val[1] * rhs[0].y + m_val[2] * rhs[0].z + m_val[3] * rhs[0].w;
				m_val[1] = m_val[0] * rhs[1].x + m_val[1] * rhs[1].y + m_val[2] * rhs[1].z + m_val[3] * rhs[1].w,
					m_val[2] = m_val[0] * rhs[2].x + m_val[1] * rhs[2].y + m_val[2] * rhs[2].z + m_val[3] * rhs[2].w,
					m_val[3] = m_val[0] * rhs[3].x + m_val[1] * rhs[3].y + m_val[2] * rhs[3].z + m_val[3] * rhs[3].w;

				return *this;
			}

			Matrix4x4& operator*=(float c)
			{
				m_val[0] *= c;
				m_val[1] *= c;
				m_val[2] *= c;
				m_val[3] *= c;

				return *this;
			}

			void transpose()
			{
				float y0 = m_val[0].y;
				float z0 = m_val[0].z;
				float w0 = m_val[0].w;
				float z1 = m_val[1].z;
				float w1 = m_val[1].w;
				float w2 = m_val[2].w;

				m_val[0] = Vector4(m_val[0].x, m_val[1].x, m_val[2].x, m_val[3].x);
				m_val[1] = Vector4(y0, m_val[1].y, m_val[2].y, m_val[3].y);
				m_val[2] = Vector4(z0, z1, m_val[2].z, m_val[3].z);
				m_val[3] = Vector4(w0, w1, w2, m_val[3].w);
			}

			Matrix4x4 transposed() const
			{
				Matrix4x4 mtx_transposed;

				mtx_transposed[0] = Vector4(m_val[0].x, m_val[1].x, m_val[2].x, m_val[3].x);
				mtx_transposed[1] = Vector4(m_val[0].y, m_val[1].y, m_val[2].y, m_val[3].y);
				mtx_transposed[2] = Vector4(m_val[0].z, m_val[1].z, m_val[2].z, m_val[3].z);
				mtx_transposed[3] = Vector4(m_val[0].w, m_val[1].w, m_val[2].w, m_val[3].w);

				return mtx_transposed;
			}

			bool inverse(Matrix4x4& inverse_out) const
			{
				return true;
			}

			float determinant() const
			{
				return 0.f;
			}

			const float* getPtr() const
			{
				return &(m_val[0].x);
			}

			static Matrix4x4 identity;

		private:
			Vector4 m_val[4];
		};
	}
}