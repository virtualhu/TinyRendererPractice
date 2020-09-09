#pragma once
#include <iostream>

namespace rmtc
{
	template <class t> struct Vector3 {
		union {
			struct { t x, y, z; };
			struct { t ivert, iuv, inorm; };
			t raw[3];
		};
		Vector3() : x(0), y(0), z(0) {}
		Vector3(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}

		inline Vector3<t> operator ^(const Vector3<t>& v) const { return Vector3<t>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
		inline Vector3<t> operator +(const Vector3<t>& v) const { return Vector3<t>(x + v.x, y + v.y, z + v.z); }
		inline Vector3<t> operator -(const Vector3<t>& v) const { return Vector3<t>(x - v.x, y - v.y, z - v.z); }
		inline Vector3<t> operator *(float f)          const { return Vector3<t>(x * f, y * f, z * f); }
		inline t       operator *(const Vector3<t>& v) const { return x * v.x + y * v.y + z * v.z; }
		inline t& operator[] (int i) { return raw[i]; }
		float norm() const { return std::sqrt(x * x + y * y + z * z); }
		Vector3<t>& normalize(t l = 1) { *this = (*this) * (l / norm()); return *this; }
		template <class > friend std::ostream& operator<<(std::ostream& s, Vector3<t>& v);

		inline Vector3<t> cross(const Vector3<t>& v)
		{
			return Vector3<t>(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
				);
		}
	};
}