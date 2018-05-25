#include <cmath>
#include "vector2d.hpp"

sdk::Vector2D::Vector2D(void) {}

sdk::Vector2D::Vector2D(sdk::vec_t X, sdk::vec_t Y)
{
	x = X; y = Y;
}

sdk::Vector2D::Vector2D(sdk::vec_t* clr)
{
	x = clr[0]; y = clr[1];
}

void sdk::Vector2D::Init(vec_t ix, vec_t iy)
{
	x = ix; y = iy;
}

void sdk::Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void Vector2DClear(sdk::Vector2D& a)
{
	a.x = a.y = 0.0f;
}

sdk::Vector2D& sdk::Vector2D::operator=(const sdk::Vector2D &vOther)
{
	x = vOther.x; y = vOther.y;

	return *this;
}

sdk::vec_t& sdk::Vector2D::operator[](int i)
{
	return ((vec_t*)this)[i];
}

sdk::vec_t sdk::Vector2D::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

sdk::vec_t* sdk::Vector2D::Base()
{
	return (vec_t*)this;
}

sdk::vec_t const* sdk::Vector2D::Base() const
{
	return (vec_t const*)this;
}

bool sdk::Vector2D::IsValid() const
{
	return !isinf(x) && !isinf(y);
}

bool sdk::Vector2D::operator==(const sdk::Vector2D& src) const
{
	return (src.x == x) && (src.y == y);
}

bool sdk::Vector2D::operator!=(const sdk::Vector2D& src) const
{
	return (src.x != x) || (src.y != y);
}

void Vector2Copy(const sdk::Vector2D& src, sdk::Vector2D& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

void sdk::Vector2D::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y;
}

void sdk::Vector2D::Negate()
{
	x = -x; y = -y;
}

void Vector2DAdd(const sdk::Vector2D& a, const sdk::Vector2D& b, sdk::Vector2D& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void Vector2DSubtract(const sdk::Vector2D& a, const sdk::Vector2D& b, sdk::Vector2D& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void Vector2DMultiply(const sdk::Vector2D& a, sdk::vec_t b, sdk::Vector2D& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
}

void Vector2DMultiply(const sdk::Vector2D& a, const sdk::Vector2D& b, sdk::Vector2D& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}

void Vector2DDivide(const sdk::Vector2D& a, sdk::vec_t b, sdk::Vector2D& c)
{
	sdk::vec_t oob = 1.0f / b;

	c.x = a.x * oob;
	c.y = a.y * oob;
}

void Vector2DDivide(const sdk::Vector2D& a, const sdk::Vector2D& b, sdk::Vector2D& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void Vector2DMA(const sdk::Vector2D& start, float s, const sdk::Vector2D& dir, sdk::Vector2D& result)
{
	result.x = start.x + s*dir.x;
	result.y = start.y + s*dir.y;
}

void sdk::Vector2D::MulAdd(const sdk::Vector2D& a, const sdk::Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void Vector2DLerp(const sdk::Vector2D& src1, const sdk::Vector2D& src2, sdk::vec_t t, sdk::Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

sdk::vec_t DotProduct2D(const sdk::Vector2D& a, const sdk::Vector2D& b)
{
	return(a.x*b.x + a.y*b.y);
}

sdk::vec_t sdk::Vector2D::Dot(const sdk::Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}

sdk::vec_t Vector2DNormalize(sdk::Vector2D& v)
{
	sdk::vec_t l = v.Length();

	if (l != 0.0f)
		v /= l;
	else
		v.x = v.y = 0.0f;

	return l;
}

sdk::vec_t Vector2DLength(const sdk::Vector2D& v)
{
	return (sdk::vec_t)sqrt(v.x*v.x + v.y*v.y);
}

sdk::vec_t sdk::Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

bool sdk::Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val*val;
}

bool sdk::Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val*val;
}

sdk::vec_t sdk::Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}

void Vector2Min(const sdk::Vector2D &a, const sdk::Vector2D &b, sdk::Vector2D &result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}

void Vector2Max(const sdk::Vector2D &a, const sdk::Vector2D &b, sdk::Vector2D &result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

void ComputeClosestPoint2D(const sdk::Vector2D& vecStart, float flMaxDist, const sdk::Vector2D& vecTarget, sdk::Vector2D *pResult)
{
	sdk::Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);

	float flDistSqr = vecDelta.LengthSqr();

	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	} 
	else
	{
		vecDelta /= sqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

sdk::Vector2D sdk::Vector2D::Min(const sdk::Vector2D &vOther) const
{
	return sdk::Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

sdk::Vector2D sdk::Vector2D::Max(const sdk::Vector2D &vOther) const
{
	return sdk::Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}

sdk::Vector2D sdk::Vector2D::operator-(void) const
{
	return sdk::Vector2D(-x, -y);
}

sdk::Vector2D sdk::Vector2D::operator+(const sdk::Vector2D& v) const
{
	sdk::Vector2D res;
	Vector2DAdd(*this, v, res);

	return res;
}

sdk::Vector2D sdk::Vector2D::operator-(const sdk::Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);

	return res;
}

sdk::Vector2D sdk::Vector2D::operator*(float fl) const
{
	sdk::Vector2D res;
	Vector2DMultiply(*this, fl, res);

	return res;
}

sdk::Vector2D sdk::Vector2D::operator*(const sdk::Vector2D& v) const
{
	sdk::Vector2D res;
	Vector2DMultiply(*this, v, res);

	return res;
}

sdk::Vector2D sdk::Vector2D::operator/(float fl) const
{
	sdk::Vector2D res;
	Vector2DDivide(*this, fl, res);

	return res;
}

sdk::Vector2D sdk::Vector2D::operator/(const sdk::Vector2D& v) const
{
	sdk::Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

sdk::Vector2D operator*(float fl, const sdk::Vector2D& v)
{
	return v * fl;
}