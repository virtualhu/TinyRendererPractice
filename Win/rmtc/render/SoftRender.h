#pragma once
#include "../math.h"
#include "RenderSurface.h"

namespace rmtc
{
	typedef Vector4f VertextPragramm(BYTE* in);
	typedef Color FragmentParamgramm();

	/// <summary>
	/// »Ì‰÷»æ∆˜
	/// </summary>
	class SoftRender
	{
	private:
		RenderSurface* m_surface;
		BYTE* m_vb;
		DWORD m_vbSize;

	public:
		~SoftRender();

		void Init(int width, int height, BYTE* frameBuff);
		void Clear(Color clr);
		void SetVertexAttribute(int idx, int size, int type, int stride, int offset);
		void SetVertext(BYTE* vertexBuffer, DWORD size);
		void SetIndices(DWORD* ib, DWORD size);
		void SetVertexShader();
		void SetFragmentShader();
		void DrawPrimitive()const; 

		void DrawLine(int x0, int y0, int x1, int y1, Color color);

	private:
		
	};
}


 