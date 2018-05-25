#include "matrix.hpp"

inline sdk::VMatrix::VMatrix() {}

inline sdk::VMatrix::VMatrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	Init(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	);
}

inline sdk::VMatrix::VMatrix(const sdk::matrix3x4_t& matrix3x4)
{
	Init(matrix3x4);
}

inline sdk::VMatrix::VMatrix(const sdk::Vector& xAxis, const sdk::Vector& yAxis, const sdk::Vector& zAxis)
{
	Init(
		xAxis.x, yAxis.x, zAxis.x, 0.0f,
		xAxis.y, yAxis.y, zAxis.y, 0.0f,
		xAxis.z, yAxis.z, zAxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

inline void sdk::VMatrix::Init(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

inline void sdk::VMatrix::Init(const sdk::matrix3x4_t& matrix3x4)
{
	memcpy(m, matrix3x4.Base(), sizeof(sdk::matrix3x4_t));

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

inline void Vector3DMultiplyPosition(const sdk::VMatrix& src1, const sdk::Vector& src2, sdk::Vector& dst)
{
	dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
	dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
	dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
}

inline sdk::Vector sdk::VMatrix::GetForward() const
{
	return sdk::Vector(m[0][0], m[1][0], m[2][0]);
}

inline sdk::Vector sdk::VMatrix::GetLeft() const
{
	return sdk::Vector(m[0][1], m[1][1], m[2][1]);
}

inline sdk::Vector sdk::VMatrix::GetUp() const
{
	return Vector(m[0][2], m[1][2], m[2][2]);
}

inline void sdk::VMatrix::SetForward(const sdk::Vector &vForward)
{
	m[0][0] = vForward.x;
	m[1][0] = vForward.y;
	m[2][0] = vForward.z;
}

inline void sdk::VMatrix::SetLeft(const sdk::Vector &vLeft)
{
	m[0][1] = vLeft.x;
	m[1][1] = vLeft.y;
	m[2][1] = vLeft.z;
}

inline void sdk::VMatrix::SetUp(const sdk::Vector &vUp)
{
	m[0][2] = vUp.x;
	m[1][2] = vUp.y;
	m[2][2] = vUp.z;
}

inline void sdk::VMatrix::GetBasisVectors(sdk::Vector &vForward, Vector &vLeft, Vector &vUp) const
{
	vForward.Init(m[0][0], m[1][0], m[2][0]);
	vLeft.Init(m[0][1], m[1][1], m[2][1]);
	vUp.Init(m[0][2], m[1][2], m[2][2]);
}

inline void sdk::VMatrix::SetBasisVectors(const sdk::Vector &vForward, const sdk::Vector &vLeft, const sdk::Vector &vUp)
{
	SetForward(vForward);
	SetLeft(vLeft);
	SetUp(vUp);
}

inline sdk::Vector sdk::VMatrix::GetTranslation() const
{
	return sdk::Vector(m[0][3], m[1][3], m[2][3]);
}

inline sdk::Vector& sdk::VMatrix::GetTranslation(sdk::Vector &vTrans) const
{
	vTrans.x = m[0][3];
	vTrans.y = m[1][3];
	vTrans.z = m[2][3];
	return vTrans;
}

inline void sdk::VMatrix::SetTranslation(const sdk::Vector &vTrans)
{
	m[0][3] = vTrans.x;
	m[1][3] = vTrans.y;
	m[2][3] = vTrans.z;
}

inline void sdk::VMatrix::PreTranslate(const Vector &vTrans)
{
	sdk::Vector tmp;

	Vector3DMultiplyPosition(*this, vTrans, tmp);

	m[0][3] = tmp.x;
	m[1][3] = tmp.y;
	m[2][3] = tmp.z;
}

inline void sdk::VMatrix::PostTranslate(const sdk::Vector &vTrans)
{
	m[0][3] += vTrans.x;
	m[1][3] += vTrans.y;
	m[2][3] += vTrans.z;
}

inline const sdk::matrix3x4_t& sdk::VMatrix::As3x4() const
{
	return *((const sdk::matrix3x4_t*)this);
}

inline sdk::matrix3x4_t& sdk::VMatrix::As3x4()
{
	return *((sdk::matrix3x4_t*)this);
}

inline void sdk::VMatrix::CopyFrom3x4(const matrix3x4_t &m3x4)
{
	memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;
}

inline void sdk::VMatrix::Set3x4(sdk::matrix3x4_t& matrix3x4) const
{
	memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
}

inline const sdk::VMatrix& sdk::VMatrix::operator+=(const sdk::VMatrix &other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] += other.m[i][j];
		}
	}

	return *this;
}

inline sdk::VMatrix sdk::VMatrix::operator+(const sdk::VMatrix &other) const
{
	sdk::VMatrix ret;

	for (int i = 0; i < 16; i++)
	{
		((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
	}
	return ret;
}

inline sdk::VMatrix sdk::VMatrix::operator-(const sdk::VMatrix &other) const
{
	sdk::VMatrix ret;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.m[i][j] = m[i][j] - other.m[i][j];
		}
	}

	return ret;
}

inline sdk::VMatrix sdk::VMatrix::operator-() const
{
	sdk::VMatrix ret;

	for (int i = 0; i < 16; i++)
	{
		((float*)ret.m)[i] = -((float*)m)[i];
	}
	return ret;
}

inline sdk::Vector sdk::VMatrix::operator*(const sdk::Vector &vVec) const
{
	sdk::Vector vRet;

	vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
	vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
	vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

	return vRet;
}

inline sdk::Vector sdk::VMatrix::VMul4x3(const sdk::Vector &vVec) const
{
	sdk::Vector vResult;
	Vector3DMultiplyPosition(*this, vVec, vResult);

	return vResult;
}

inline sdk::Vector sdk::VMatrix::VMul4x3Transpose(const sdk::Vector &vVec) const
{
	Vector tmp = vVec;

	tmp.x -= m[0][3];
	tmp.y -= m[1][3];
	tmp.z -= m[2][3];

	return Vector(
		m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
		m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
		m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
	);
}

inline sdk::Vector sdk::VMatrix::VMul3x3(const sdk::Vector &vVec) const
{
	return sdk::Vector(
		m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
		m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
		m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
	);
}

inline sdk::Vector sdk::VMatrix::VMul3x3Transpose(const sdk::Vector &vVec) const
{
	return sdk::Vector(
		m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
		m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
		m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
	);
}

inline void sdk::VMatrix::V3Mul(const sdk::Vector &vIn, sdk::Vector &vOut) const
{
	float rw;

	rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
	vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
	vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
	vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
}

inline void sdk::VMatrix::Identity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

inline bool sdk::VMatrix::IsIdentity() const
{
	return
		m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
		m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
		m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
		m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
}

inline sdk::Vector sdk::VMatrix::ApplyRotation(const sdk::Vector &vVec) const
{
	return VMul3x3(vVec);
}
