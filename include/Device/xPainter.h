#ifndef __XPAINTER_H_
#define __XPAINTER_H_

#include "../Std/types.h"
#include "../Std/String.hpp"
#include "xScreen.h"

namespace xc::ui {
    class xFont;
}

namespace xc {
    class xPainter {
    private:
        Area m_area;
        xScreen* m_screen;
    public:
        xPainter(xScreen* screen, Area area);
        ~xPainter();

        inline void DrawPixel(Coordinate point, Colour c);
        inline void DrawRectangle(Coordinate point, Rectangle rect, Colour c);
        inline void DrawRectangle(Area rectangle, Colour c);
        inline void DrawCircle(Coordinate point, uint32_t r, Colour c);
        inline void DrawLine(Coordinate point1, Coordinate point2, uint32_t lineWidth);
        inline void DrawChar(Coordinate top_left, Rectangle size, char c, xFont font, Colour color, uint8_t font_size);
        inline void DrawChar(Area area, char c, xFont font, Colour color, uint8_t font_size);

        inline void SetArea(Area area) { m_area = area; }
    };
}

#endif