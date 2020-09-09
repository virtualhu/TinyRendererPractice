#include "SoftRender.h"

using namespace rmtc;

SoftRender::~SoftRender()
{
    if (m_surface != NULL)
    {
        delete m_surface;
        m_surface = NULL;
    }
}

void SoftRender::Init(int width, int height, BYTE* frameBuff)
{
    if (m_surface != NULL)
    {
        return;
    }
    m_surface = new RenderSurface(width, height, RenderSurface::Format::ARGB, frameBuff);
}

void SoftRender::SetVertext(BYTE* vertexBuffer, DWORD size)
{

}  

void SoftRender::Clear(Color clr)
{
    m_surface->Clear(clr);
}

void _SetImage(RenderSurface& surface, int x, int y, Color color) { surface.Set(x, y, color); }
void _SetImageFlipXY(RenderSurface& surface, int x, int y, Color color) { surface.Set(y, x, color); }

void SoftRender::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
    void (*setFunc)(RenderSurface&, int, int, Color) = _SetImage;
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {//象限转换，以保证x+1递增
        std::swap(x0, y0);
        std::swap(x1, y1);
        setFunc = _SetImageFlipXY;
    }
    if (x0 > x1) {//方向转换
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int inc = y1 > y0 ? 1 : -1;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        setFunc(*m_surface, x, y, color);
        error2 += derror2;
        if (error2 > dx) {
            y += inc;
            error2 -= dx * 2;
        }
    }
}