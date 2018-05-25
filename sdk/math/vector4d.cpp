#include <cmath>
#include <limits>
#include "Vector4D.hpp"

void VectorCopy(const sdk::Vector4D& src, sdk::Vector4D& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	dst.w = src.w;
}

void VectorLerp(const sdk::Vector4D& src1, const sdk::Vector4D& src2, sdk::vec_t t, sdk::Vector4D& dest)
{
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
	dest.w = src1.w + (src2.w - src1.w) * t;
}

float VectorLength(const sdk::Vector4D& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

sdk::vec_t NormalizeVector(sdk::Vector4D& v)
{
	sdk::vec_t l = v.Length();

	if (l != 0.0f)
		v /= l;
	else
		v.x = v.y = v.z = v.w = 0.0f;

	return l;
}

sdk::Vector4D::Vector4D(void)
{
	Invalidate();
}

sdk::Vector4D::Vector4D(sdk::vec_t X, sdk::vec_t Y, sdk::vec_t Z, sdk::vec_t W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

sdk::Vector4D::Vector4D(sdk::vec_t* clr)
{
	x = clr[0];
	y = clr[1];
	z = clr[2];
	w = clr[3];
}

void sdk::Vector4D::Init(sdk::vec_t ix, sdk::vec_t iy, sdk::vec_t iz, sdk::vec_t iw)
{
	x = ix; y = iy; z = iz; w = iw;
}

void sdk::Vector4D::Random(sdk::vec_t minVal, sdk::vec_t maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void sdk::Vector4D::Zero()
{
	x = y = z = w = 0.0f;
}

sdk::Vector4D& sdk::Vector4D::operator=(const sdk::Vector4D &vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
	return *this;
}

sdk::vec_t& sdk::Vector4D::operator[](int i)
{
	return ((sdk::vec_t*)this)[i];
}

sdk::vec_t sdk::Vector4D::operator[](int i) const
{
	return ((sdk::vec_t*)this)[i];
}

sdk::vec_t* sdk::Vector4D::Base()
{
	return (sdk::vec_t*)this;
}

sdk::vec_t const* sdk::Vector4D::Base() const
{
	return (sdk::vec_t const*)this;
}

bool sdk::Vector4D::IsValid() const
{
	return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
}

void sdk::Vector4D::Invalidate()
{
	x = y = z = w = std::numeric_limits<float>::infinity();
}

bool sdk::Vector4D::operator==(const sdk::Vector4D& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

bool sdk::Vector4D::operator!=(const sdk::Vector4D& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}

void sdk::Vector4D::CopyToArray(float* rgfl) const
{
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
}

void sdk::Vector4D::Negate()
{
	x = -x; y = -y; z = -z; w = -w;
}

sdk::Vector4D sdk::Vector4D::ProjectOnto(const sdk::Vector4D& onto)
{
	return onto * (this->Dot(onto) / (onto.LengthSqr()));
}

void sdk::Vector4D::MulAdd(const sdk::Vector4D& a, const sdk::Vector4D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
	w = a.w + b.w * scalar;
}

sdk::Vector4D VectorLerp(const sdk::Vector4D& src1, const sdk::Vector4D& src2, sdk::vec_t t)
{
	sdk::Vector4D result;
	VectorLerp(src1, src2, t, result);
	return result;
}

sdk::vec_t sdk::Vector4D::Dot(const sdk::Vector4D& b) const
{
	return (x*b.x + y * b.y + z * b.z + w * b.w);
}

void VectorClear(sdk::Vector4D& a)
{
	a.x = a.y = a.z = a.w = 0.0f;
}

sdk::vec_t sdk::Vector4D::Length(void) const
{
	return sqrt(x*x + y * y + z * z + w * w);
}

bool sdk::Vector4D::WithinAABox(sdk::Vector4D const &boxmin, sdk::Vector4D const &boxmax)
{
	return (
		   (x >= boxmin.x) && (x <= boxmax.x) &&
		   (y >= boxmin.y) && (y <= boxmax.y) &&
		   (z >= boxmin.z) && (z <= boxmax.z) &&
		   (w >= boxmin.w) && (w <= boxmax.w)
		   );
}

sdk::vec_t sdk::Vector4D::DistTo(const sdk::Vector4D &vOther) const
{
	sdk::Vector4D delta;
	delta = *this - vOther;
	return delta.Length();
}

sdk::Vector4D sdk::Vector4D::Min(const sdk::Vector4D &vOther) const
{
	return sdk::Vector4D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y,
		z < vOther.z ? z : vOther.z,
		w < vOther.w ? w : vOther.w);
}

sdk::Vector4D sdk::Vector4D::Max(const sdk::Vector4D &vOther) const
{
	return sdk::Vector4D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y,
		z > vOther.z ? z : vOther.z,
		w > vOther.w ? w : vOther.w);
}

sdk::Vector4D sdk::Vector4D::operator-(void) const
{
	return sdk::Vector4D(-x, -y, -z, -w);
}

sdk::Vector4D sdk::Vector4D::operator+(const sdk::Vector4D& v) const
{
	return sdk::Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}

sdk::Vector4D sdk::Vector4D::operator-(const sdk::Vector4D& v) const
{
	return sdk::Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}

sdk::Vector4D sdk::Vector4D::operator*(float fl) const
{
	return sdk::Vector4D(x * fl, y * fl, z * fl, w * fl);
}

sdk::Vector4D sdk::Vector4D::operator*(const sdk::Vector4D& v) const
{
	return sdk::Vector4D(x * v.x, y * v.y, z * v.z, w * v.w);
}

sdk::Vector4D sdk::Vector4D::operator/(float fl) const
{
	return sdk::Vector4D(x / fl, y / fl, z / fl, w / fl);
}

sdk::Vector4D sdk::Vector4D::operator/(const sdk::Vector4D& v) const
{
	return sdk::Vector4D(x / v.x, y / v.y, z / v.z, w / v.w);
}

sdk::Vector4D operator*(float fl, const sdk::Vector4D& v)
{
	return v * fl;
}