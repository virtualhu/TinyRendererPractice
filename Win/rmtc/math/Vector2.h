#pragma once
#include <iostream>

namespace rmtc
{
	template <class t> struct Vector2
	{
		union {
			struct { t u, v; };
			struct { t x, y; };
			t raw[2];
		};
		Vector2() : u(0), v(0) {}
		Vector2(t _u, t _v) : u(_u), v(_v) {}
		inline Vector2<t> operator +(const Vector2<t>& V) const { return Vector2<t>(u + V.u, v + V.v); }
		inline Vector2<t> operator -(const Vector2<t>& V) const { return Vector2<t>(u - V.u, v - V.v); }
		inline Vector2<t> operator *(float f)          const { return Vector2<t>(u * f, v * f); }
		inline t       operator *(const Vector2<t>& v) const { return x * v.x + y * v.y; }
		inline t& operator[] (int i) { return raw[i]; }
		template <class > friend std::ostream& operator<<(std::ostream& s, Vector2<t>& v);
	};
}