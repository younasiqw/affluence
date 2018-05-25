#pragma once

namespace sdk
{
	typedef float vec_t;

	class Vector2D
	{
	public:
		vec_t x, y;

		Vector2D(void);
		Vector2D(vec_t X, vec_t Y);
		Vector2D(vec_t* clr);

		Vector2D(const Vector2D &vOther)
		{
			x = vOther.x; y = vOther.y;
		}

		vec_t  operator[](int i) const;
		vec_t& operator[](int i);
		vec_t* Base();
		vec_t  const* Base() const;

		void Init(vec_t ix = 0.0f, vec_t iy = 0.0f);
		bool IsValid() const;
		void Invalidate();
		void Random(vec_t minVal, vec_t maxVal);
		void Zero();
		bool operator==(const Vector2D& v) const;
		bool operator!=(const Vector2D& v) const;

		Vector2D& operator+=(const Vector2D& v)
		{
			x += v.x; y += v.y;
			return *this;
		}

		Vector2D& operator-=(const Vector2D& v)
		{
			x -= v.x; y -= v.y;
			return *this;
		}

		Vector2D& operator*=(float fl)
		{
			x *= fl;
			y *= fl;
			return *this;
		}

		Vector2D& operator*=(const Vector2D& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vector2D& operator/=(const Vector2D& v)
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}

		Vector2D& operator+=(float fl)
		{
			x += fl;
			y += fl;
			return *this;
		}

		Vector2D& operator/=(float fl)
		{
			x /= fl;
			y /= fl;
			return *this;
		}

		Vector2D& operator-=(float fl)
		{
			x -= fl;
			y -= fl;
			return *this;
		}

		void Negate();

		vec_t Length() const;
		vec_t LengthSqr(void) const
		{
			return (x*x + y * y);
		}

		bool IsZero(float tolerance = 0.01f) const
		{
			return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance);
		}

		vec_t NormalizeInPlace();
		Vector2D Normalized() const;

		bool IsLengthGreaterThan(float val) const;
		bool IsLengthLessThan(float val) const;
		bool WithinAABox(Vector2D const &boxmin, Vector2D const &boxmax);

		vec_t DistTo(const Vector2D &vOther) const;
		vec_t DistToSqr(const Vector2D &vOther) const
		{
			Vector2D delta;

			delta.x = x - vOther.x;
			delta.y = y - vOther.y;

			return delta.LengthSqr();
		}

		void CopyToArray(float* rgfl) const;
		void MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

		vec_t Dot(const Vector2D& vOther) const;
		Vector2D& operator=(const Vector2D &vOther);
		vec_t Length2D(void) const;
		vec_t Length2DSqr(void) const;
		Vector2D  ProjectOnto(const Vector2D& onto);
		Vector2D operator-(void) const;
		Vector2D operator+(const Vector2D& v) const;
		Vector2D operator-(const Vector2D& v) const;
		Vector2D operator*(const Vector2D& v) const;
		Vector2D operator/(const Vector2D& v) const;
		Vector2D operator*(float fl) const;
		Vector2D operator/(float fl) const;
		Vector2D Cross(const Vector2D &vOther) const;
		Vector2D Min(const Vector2D &vOther) const;
		Vector2D Max(const Vector2D &vOther) const;
	};
}