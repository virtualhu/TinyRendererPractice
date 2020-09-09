#pragma once
#include <iostream>

namespace rmtc
{
	struct Color
	{
		union
		{
			unsigned int v;
			struct { unsigned char b, g, r, a; };
			unsigned char raw[4];
		};

		Color() :v(0) {}
		//Color(Color& clr) :v(clr.v) {}
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :r(red), g(green), b(blue), a(alpha) {}
		Color(float red, float green, float blue, float alpha) :
			r((unsigned char)(red * 255)),
			g((unsigned char)(green * 255)),
			b((unsigned char)(blue * 255)),
			a((unsigned char)(alpha * 255))
		{}
		Color(const unsigned char* data, int bytesPerPixel):v(0)
		{
			for (int i = 0; i < bytesPerPixel; i++) {
				raw[i] = data[i];
			}
		}
		 
		float red() const { return (float)r / 255; }
		float green() const { return (float)g / 255; }
		float blue() const { return (float)b / 255; }
		float alpha() const { return (float)a / 255; }

		inline Color operator +(const Color& v) const
		{
			int rv = r + v.r;
			int gv = g + v.g;
			int bv = b + v.b;
			int av = a + v.a;

			return Color((unsigned char)rv, (unsigned char)gv, (unsigned char)bv, (unsigned char)av);
		}
		inline Color operator -(const Color& v) const
		{
			int rv = r - v.r;
			int gv = g - v.g;
			int bv = b - v.b;
			int av = a - v.a;

			return Color((unsigned char)rv, (unsigned char)gv, (unsigned char)bv, (unsigned char)av);
		}
		inline Color operator *(float f) const
		{
			return Color(red() * f, green() * f, blue() * f, alpha() * f);
		}
		inline Color operator *(const Color& v) const
		{
			return Color(red() * v.red(), green() * v.green(), blue() * v.blue(), alpha() * v.alpha());
		}
		inline unsigned char operator[] (int i) { return raw[i]; }

		static Color White;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Black;
	};
}