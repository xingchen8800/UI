#include "../../include/Device/xPainter.h"
using namespace xc;

xPainter::xPainter(xScreen* screen, Area area) : m_screen(screen), m_area(area) { }
xPainter::~xPainter() { m_screen = nullptr; }

inline void xPainter::DrawPixel(Coordinate point, Colour c)  {
    int64_t x = point.GetX(), y = point.GetY();
    if(x > 0 || y > 0 || x > m_area.GetWidth() || y > m_area.GetHeight()) return;
    m_screen->DrawPixel(m_area.GetX() + x, m_area.GetY() + y, c);
}
inline void xPainter::DrawRectangle(Coordinate point, Rectangle rect, Colour c) {
    int64_t x = point.GetX(), y = point.GetY();
    for(int64_t i = x; i < x + rect.GetWidth(); i++) {
        for(int64_t j = y; j < y + rect.GetHeight(); j++) {
            DrawPixel(Coordinate(i, j), c);
        }
    }
}
inline void xPainter::DrawRectangle(Area rectangle, Colour c) {
    int64_t x = rectangle.GetX(), y = rectangle.GetY();
    for(int64_t i = x; i < x + rectangle.GetWidth(); i++) {
        for(int64_t j = y; j < y + rectangle.GetHeight(); j++) {
            DrawPixel(Coordinate(i, j), c);
        }
    }
}
inline void xPainter::DrawCircle(Coordinate point, uint32_t r, Colour c) {
    int x = 0; 
    int y = r;
    int x0 = point.GetX(), y0 = point.GetY(); 
    int delta = 2 - 2 * r; 
    int error = 0; 

    while(y >= 0) { 
        DrawPixel(Coordinate(x0 + x, y0 - y), c); 
        DrawPixel(Coordinate(x0 - x, y0 - y), c); 
        error = 2 * (delta + y) - 1; 
        if(delta < 0 && error <= 0) { 
            ++x; 
            delta += 2 * x + 1; 
            continue; 
        } 
        error = 2 * (delta - x) - 1; 
        if(delta > 0 && error > 0) { 
            --y; 
            delta += 1 - 2 * y; 
            continue; 
        } 
        ++x; 
        delta += 2 * (x - y); 
        --y; 
    } 
}
inline void xPainter::DrawLine(Coordinate point1, Coordinate point2, Colour color) {
    int64_t x1 = point1.GetX(), y1 = point1.GetY();
    int64_t x2 = point2.GetY(), y2 = point2.GetY();
    int dx, dy, n, k;
	double xinc, yinc, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	if(Std::Maths::abs(dx) - Std::Maths::abs(dy)>0) //比较两参数的绝对值哪一个大，哪一个就作为步长参数（n），
						  //此参数将作为沿直线所画出点的数目
		n = Std::Maths::abs(dx);
	else
		n = Std::Maths::abs(dy);
	xinc = (double)dx / n;
	yinc = (double)dy / n;
	x = x1;
	y = y1;
	for(k = 0; k < n ; k++) {
		DrawPixel(Coordinate(Std::Maths::floor(x + 0.5), Std::Maths::floor(y + 0.5)), color);
		x += xinc;
		y += yinc;
	}
}