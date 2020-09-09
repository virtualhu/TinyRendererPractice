#pragma once

#include "../math.h"

namespace rmtc
{
	class RenderSurface
	{
	public:
		enum class Format
		{
			GRAY = 1,
			RGB = 3,
			ARGB = 4,
		};

		RenderSurface(int w, int h, RenderSurface::Format format, BYTE* buffer);
		~RenderSurface();

		void Clear(Color clr);
		bool Set(int x, int y, Color clr);
		Color Get(int x, int y)const;
		BYTE* buffer()const { return m_data; }

	private:
		int m_width;
		int m_height;
		int m_bytePerPixel;

		BYTE* m_data;
		BYTE* m_innerCreate;
	};
}