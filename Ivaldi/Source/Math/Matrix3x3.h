#pragma once

#include "Core.h"
#include "Math/Point3.h"

namespace ivaldi {
	namespace math {
		class IVALDI_API Matrix3x3 {
		public:
			Matrix3x3() = default;

			Matrix3x3(
				const Vector3& v0,
				const Vector3& v1,
				const Vector3& v2)
			{
				m_val[0] = v0;
				m_val[1] = v1;
				m_val[2] = v2;
			}

			Matrix3x3(
				float x0, float x1, float x2,
				float y0, float y1, float y2,
				float z0, float z1, float z2)
			{
				m_val[0] = Vector3(x0, y0, z0);
				m_val[1] = Vector3(x1, y1, z1);
				m_val[2] = Vector3(x2, y2, z2);
			}

			Matrix3x3(const Matrix3x3& rhs)
			{
				m_val[0] = rhs[0];
				m_val[1] = rhs[1];
				m_val[2] = rhs[2];
			}

			Matrix3x3(Matrix3x3&& rhs)
			{

			}

			Matrix3x3 operator+(const Matrix3x3& rhs)
			{
				return {
					m_val[0] + rhs[0],
					m_val[1] + rhs[1],
					m_val[2] + rhs[2]
				};
			}

			Matrix3x3 operator-(const Matrix3x3& rhs)
			{
				return {
					m_val[0] - rhs[0],
					m_val[1] - rhs[1],
					m_val[2] - rhs[2]
				};
			}

			Matrix3x3 operator*(const Matrix3x3& rhs)
			{
				return {
					m_val[0] * rhs[0].x + m_val[1] * rhs[0].y + m_val[2] * rhs[0].z,
					m_val[0] * rhs[1].x + m_val[1] * rhs[1].y + m_val[2] * rhs[1].z,
					m_val[0] * rhs[2].x + m_val[1] * rhs[2].y + m_val[2] * rhs[2].z,
				};
			}

			Matrix3x3 operator*(float c)
			{
				return {
					m_val[0] * c,
					m_val[1] * c,
					m_val[2] * c
				};
			}

			Vector3& operator[](int i)
			{
				return m_val[i];
			}

			const Vector3& operator[](int i) const
			{
				return m_val[i];
			}

			Matrix3x3& operator+=(const Matrix3x3& rhs)
			{
				m_val[0] += rhs[0];
				m_val[1] += rhs[1];
				m_val[2] += rhs[2];

				return *this;
			}

			Matrix3x3& operator-=(const Matrix3x3& rhs)
			{
				m_val[0] -= rhs[0];
				m_val[1] -= rhs[1];
				m_val[2] -= rhs[2];

				return *this;
			}

			Matrix3x3& operator*=(const Matrix3x3& rhs)
			{
				m_val[0] = m_val[0] * rhs[0].x + m_val[1] * rhs[0].y + m_val[2] * rhs[0].z;
				m_val[1] = m_val[0] * rhs[1].x + m_val[1] * rhs[1].y + m_val[2] * rhs[1].z;
				m_val[2] = m_val[0] * rhs[2].x + m_val[1] * rhs[2].y + m_val[2] * rhs[2].z;

				return *this;
			}

			Matrix3x3& operator*=(float c)
			{
				m_val[0] *= c;
				m_val[1] *= c;
				m_val[2] *= c;

				return *this;
			}

			void transpose()
			{
				float y0 = m_val[0].y;
				float z0 = m_val[0].z;
				float z1 = m_val[1].z;

				m_val[0] = Vector3(m_val[0].x, m_val[1].x, m_val[2].x);
				m_val[1] = Vector3(y0, m_val[1].y, m_val[2].y);
				m_val[2] = Vector3(z0, z1, m_val[2].z);
			}

			Matrix3x3 transposed() const
			{
				Matrix3x3 mtx_transposed;

				mtx_transposed[0] = Vector3(m_val[0].x, m_val[1].x, m_val[2].x);
				mtx_transposed[1] = Vector3(m_val[0].y, m_val[1].y, m_val[2].y);
				mtx_transposed[2] = Vector3(m_val[0].z, m_val[1].z, m_val[2].z);

				return mtx_transposed;
			}

			bool inverse(Matrix3x3& inverse_out) const
			{
				// Find determinant of matrix.
				auto top_row_cofactors = topRowCofactors();
				auto determinant = m_val[0].x * top_row_cofactors.x + m_val[1].x * top_row_cofactors.y + m_val[2].x * top_row_cofactors.z;

				if (determinant == 0)
					return false;

				// Find determinants of 2x2 submatrices for the elements of the inverse.
				inverse_out[0].x = top_row_cofactors.x;
				inverse_out[1].x = top_row_cofactors.y;
				inverse_out[2].x = top_row_cofactors.z;
				inverse_out[0].y = m_val[1].x * m_val[2].z - m_val[2].x * m_val[1].z;
				inverse_out[1].y = m_val[0].x * m_val[2].z - m_val[2].x * m_val[0].z;
				inverse_out[2].y = m_val[0].x * m_val[1].z - m_val[1].x * m_val[0].z;
				inverse_out[0].z = m_val[1].x * m_val[2].y - m_val[2].x * m_val[1].y;
				inverse_out[1].z = m_val[0].x * m_val[2].y - m_val[2].x * m_val[0].y;
				inverse_out[2].z = m_val[0].x * m_val[1].y - m_val[1].x * m_val[0].y;

				inverse_out *= 1 / determinant;

				return true;
			}

			float determinant() const
			{
				auto top_row_cofactors = topRowCofactors();

				return m_val[0].x * top_row_cofactors.x + m_val[1].x * top_row_cofactors.y + m_val[2].x * top_row_cofactors.z;
			}


			void scale()
			{

			}

			void shear()
			{

			}

			const float* getPtr() const
			{
				return &(m_val[0].x);
			}

			static Matrix3x3 identity;

		private:
			Vector3 topRowCofactors() const
			{
				return {
					m_val[1].y * m_val[2].z - m_val[2].y * m_val[1].z,
					-(m_val[0].y * m_val[2].z - m_val[2].y * m_val[0].z),
					m_val[0].y * m_val[1].z - m_val[1].y * m_val[0].z
				};
			}

			Vector3 m_val[3];
		};
	}
}