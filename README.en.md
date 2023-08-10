
<h1 align="center">xcUI - Cross-platform UI Library</h1>

<h2 align="center">⚠⚠ This project uses the GNU3.0 license. Please comply with the license content, otherwise you bear the consequences ⚠⚠</h2>
English | Simplified Chinese
✨Overview
This is a cross-platform UI library, written in pure C++, _without using the std library_. You only need to provide a function for outputting pixels void(uint64t, uint64_t, Color)] and a function for input devices const char()] to use it on the device.
### Implementation Logic of xcUI
<img src="xcUI.png" alt="Flowchart of xcUI operation (apologies for the poor diagram)"/>
The main structure of xcUI is as shown in the figure above: in a loop, it continuously calls the function to get input device information, then processes the received data into xEvent objects that are easy for xuiObject to use, then sends a paint event to the bottommost xuiObject object, and finally pushes the screen that has received all drawing information to the output device.

## 📖Usage Tutorial
### Examples
#### Draw a Line (./example/DrawALine)
```c++
//文件: ./main.cpp
//在Visual Studio 2022 + easyx上编译

#include "../../include/Device/xScreen.h"
#include "../../include/Device/xPainter.h"
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
```
---
#### Desktop Alarm Clock (./example/alarm)(Todo)
```c++
#include "../../include/Object/xuiObject.h"
```
## 📰Update Log
### August 9, 2023 - Wednesday

- Changes to xBaseObject
- Merged xBaseObject and xuiObject
- Deprecated xBaseObject
- Implemented basic drawing functions of xPainter
- Added GetReal series functions in xuiObject for updating drawing area
- Added comments in xuiObject.h
- Added xuiObject::SetChangeChildrensAttributeOnSetAttribute() function to set whether to change the same attribute of child objects when the object attribute is set or updated
- Added xuiObject::GetFocus() and xuiObject::LostFocus, and added corresponding secondary processing functions: xuiObject::onGetFocusEvent() and xuiObject::onLostFocusEvent() 