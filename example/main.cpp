//在Visual Studio 2022 + easyx上编译

#include "../include/Device/xScreen.h"
#include "../include/Device/xPainter.h"
#include <graphics.h>
using namespace xc;

xScreen *screen;

void DrawPixel(uint64_t x, uint64_t y, Colour c) {
    PutPixel(x, y, RGB(c.r, c.g, c.b));
}

int main() {
    initgraph(640, 480);
    screen = new xScreen(DrawPixel, Std::Rectangle(640, 480));
    xPainter* painter = new xPainter(screen, Std::Area(640, 480));
    painter->DrawLine(Std::Coordinate(0, 0), Std::Coordinate(100, 100));
    screen->Push();
    while (1);
    closegraph();
}