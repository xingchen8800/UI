#include "../../include/Device/xScreen.h"
#include "../../include/Device/xPainter.hpp"
using namespace xc;

xScreen::xScreen(DrawPixel_t func, Rectangle size) 
        : m_size(size) {
    uint64_t w = m_size.GetWidth(), h = m_size.GetHeight();
    m_buffer = new Colour[w * h];
    m_painter = new xPainter(this, Area(0, 0, w, h));
}

void xScreen::DrawPixel(uint64_t x, uint64_t y, Colour c) {
    m_buffer[m_size.GetWidth() * y + x] = c;
}

int16_t xScreen::loop(ui::xuiObject* baseObj) {
    uint64_t w = m_size.GetWidth(), h = m_size.GetHeight();
    m_painter->SetArea(Area(0, 0, w, h));
    baseObj->Paint(m_painter);
    Push();

    return loop(baseObj);
}

void xScreen::Push() {
    for(uint64_t i = 0; i < m_size.GetWidth(); i++) {
        for(uint64_t j = 0; j < m_size.GetHeight(); j++) {
            DrawPixel(i, j, m_buffer[j * m_size.GetHeight() + i]);
        }
    }
}