#pragma once
#include "math.h"

namespace rmtc
{
	
	/// <summary>
	/// »Ì‰÷»æ∆˜
	/// </summary>
	class SoftRender
	{
	public:
		void Init(int width, int height);
		void Clear();
		void SetVertext(char* vb, unsigned int  size);
		void SetIndices(unsigned int* ib, unsigned int size);
		void SetVertexShader();
		void SetFragmentShader();
		void DrawPrimitive(); 
	};
}


