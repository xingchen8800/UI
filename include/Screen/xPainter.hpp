#ifndef __XPAINTER_H_
#define __XPAINTER_H_

#include "../Std/types.h"
#include "../Std/String.hpp"
#include "xScreen.h"

namespace xc {
    class xPainter {
    private:
        Area m_area;
        xScreen* m_screen;
    public:
        xPainter(xScreen* screen, Area area) : m_screen(screen), m_area(area) { }
        ~xPainter() { m_screen = nullptr; }

        void DrawRectangle(int64_t x, int64_t y, Rectangle rect, Colour c) {
            for(int64_t i = x; i < x + rect.GetWidth(); i++) {
                for(int64_t j = y; j < y + rect.GetHeight(); j++) {
                    DrawPixel(x, y, c);
                }
            }
        }
        void DrawPixel(int64_t x, int64_t y, Colour c) {
            if(x > 0 || y > 0 || x > m_area.GetWidth() || y > m_area.GetHeight()) return;
            m_screen->DrawPixel(m_area.GetX() + x, m_area.GetY() + y, c);
        }
        void DrawCircle(int64_t x, int64_t y, int r, Colour c) {

        }

        void SetArea(Area area) {
            m_area = area;
        }
    };
}

#endif