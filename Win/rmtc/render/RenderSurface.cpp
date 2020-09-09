#include "RenderSurface.h"

using namespace rmtc;

RenderSurface::RenderSurface(int w, int h, RenderSurface::Format format, BYTE* buffer)
{
	m_width = w;
	m_height = h;
	m_bytePerPixel = (int)format;
	if (buffer == NULL)
	{
		m_innerCreate = new BYTE[m_width * m_height * m_bytePerPixel];
		m_data = m_innerCreate;
	}
	else
	{
		m_innerCreate = NULL;
		m_data = buffer;
	}
}

RenderSurface::~RenderSurface()
{
	if (m_innerCreate != NULL)
	{
		delete[] m_innerCreate;
		m_innerCreate = NULL;
	}
	m_data = NULL;
}

void RenderSurface::Clear(Color clr)
{
	size_t length = m_width * m_height;
	for (size_t pixel = 0; pixel < length; pixel++)
	{
		memcpy(m_data + pixel * m_bytePerPixel, clr.raw, m_bytePerPixel);
	}
}

bool RenderSurface::Set(int x, int y, Color clr)
{
	if (x < 0 || y < 0 || x >= m_width || y >= m_height)
	{
		return false;
	}
	memcpy(m_data + (x + y * m_width) * m_bytePerPixel, clr.raw, m_bytePerPixel);
	return true;
}

Color RenderSurface::Get(int x, int y) const
{
	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		return Color();
	}
	return Color(m_data + (x + y * m_width) * m_bytePerPixel, m_bytePerPixel);
}