#pragma once

#include <math.h>
#include <cmath>

namespace sdk
{
	class QAngle
	{
	public:
		QAngle(void)
		{
			init();
		}

		QAngle(float X, float Y, float Z)
		{
			init(X, Y, Z);
		}

		QAngle(const float* clr)
		{
			init(clr[0], clr[1], clr[2]);
		}

		void init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
		{
			pitch = ix;
			yaw = iy;
			roll = iz;
		}

		__inline bool isvalid() const
		{
			return std::isfinite(pitch) && std::isfinite(yaw) && std::isfinite(roll);
		}

		float operator[](int i) const
		{
			return ((float*)this)[i];
		}

		float &operator[](int i)
		{
			return ((float*)this)[i];
		}

		bool operator==(const QAngle &src) const
		{
			return (src.pitch == pitch) && (src.yaw == yaw) && (src.roll == roll);
		}

		bool operator!=(const QAngle &src) const
		{
			return (src.pitch != pitch) || (src.yaw != yaw) || (src.roll != roll);
		}

		QAngle &operator+=(const QAngle &v)
		{
			pitch += v.pitch; yaw += v.yaw; roll += v.roll;
			return *this;
		}

		QAngle &operator-=(const QAngle &v)
		{
			pitch -= v.pitch; yaw -= v.yaw; roll -= v.roll;
			return *this;
		}

		QAngle &operator*=(float fl)
		{
			pitch *= fl;
			yaw *= fl;
			roll *= fl;
			return *this;
		}

		QAngle &operator*=(const QAngle &v)
		{
			pitch *= v.pitch;
			yaw *= v.yaw;
			roll *= v.roll;
			return *this;
		}

		QAngle &operator/=(const QAngle &v)
		{
			pitch /= v.pitch;
			yaw /= v.yaw;
			roll /= v.roll;
			return *this;
		}

		QAngle &operator+=(float fl)
		{
			pitch += fl;
			yaw += fl;
			roll += fl;
			return *this;
		}

		QAngle &operator/=(float fl)
		{
			pitch /= fl;
			yaw /= fl;
			roll /= fl;
			return *this;
		}

		QAngle &operator-=(float fl)
		{
			pitch -= fl;
			yaw -= fl;
			roll -= fl;
			return *this;
		}

		QAngle &operator=(const QAngle &vOther)
		{
			pitch = vOther.pitch; yaw = vOther.yaw; roll = vOther.roll;
			return *this;
		}

		QAngle operator-(void) const
		{
			return QAngle(-pitch, -yaw, -roll);
		}

		QAngle operator+(const QAngle &v) const
		{
			return QAngle(pitch + v.pitch, yaw + v.yaw, roll + v.roll);
		}

		QAngle operator-(const QAngle &v) const
		{
			return QAngle(pitch - v.pitch, yaw - v.yaw, roll - v.roll);
		}

		QAngle operator*(float fl) const
		{
			return QAngle(pitch * fl, yaw * fl, roll * fl);
		}

		QAngle operator*(const QAngle &v) const
		{
			return QAngle(pitch * v.pitch, yaw * v.yaw, roll * v.roll);
		}

		QAngle operator/(float fl) const
		{
			return QAngle(pitch / fl, yaw / fl, roll / fl);
		}

		QAngle operator/(const QAngle &v) const
		{
			return QAngle(pitch / v.pitch, yaw / v.yaw, roll / v.roll);
		}

		float length() const
		{
			return sqrt(pitch*pitch + yaw * yaw + roll * roll);
		}

		float lengthsqr(void) const
		{
			return (pitch*pitch + yaw * yaw + roll * roll);
		}

		bool iszero(float tolerance = 0.01f) const
		{
			return (pitch > -tolerance && pitch < tolerance &&
				yaw > -tolerance && yaw < tolerance &&
				roll > -tolerance && roll < tolerance);
		}

		void normalizeangles()
		{
			while (pitch < -89.0f)
				pitch += 89.0f;

			if (pitch > 89.0f)
				pitch = 89.0f;

			while (yaw < -180.0f)
				yaw += 360.0f;

			while (yaw > 180.0f)
				yaw -= 360.0f;

			roll = 0.0f;
		}

		float pitch, yaw, roll;
	};

	inline QAngle operator*(float lhs, const QAngle &rhs)
	{
		return rhs * lhs;
	}

	inline QAngle operator/(float lhs, const QAngle &rhs)
	{
		return rhs / lhs;
	}
}