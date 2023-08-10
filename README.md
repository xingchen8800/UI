
<style>
    .title {
        text-align: center;
        font-color: white;
        font-family: Consolas;
    }
</style>
<h1 class="title">xcUI - 跨平台的UI库</h1>

## ✨概述
<p style="font-family:Consolas">这是一个跨平台的UI库，使用纯C++编写，没有使用std库。你只需要提供输出像素的函数[void(uint64_t, uint64_t, Color)]和输入设备的函数[const char*()]就可以在设备上使用了。</p>
<h3 style="font-family:Consolas">xcUI的实现逻辑</h3>
<img src="xcUI.png" alt="xcUI的运行流程图(作图不好，请见谅)"/>
<p style="font-family:Consolas">xcUI主要结构如上图：在一个循环中，不停地调用获取输入设备信息的函数，再对接受到的数据进行处理，使这些数据变成易于xuiObject使用的xEvent对象，然后向最底层的xuiObject对象发送paint事件，最后将已经接收到所有绘图信息的屏幕推送到输出设备上。</p>

## 📖使用教程
### 示例
#### 画一条直线(./example/DrawALine)
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
#### 桌面闹钟(./example/alarm)(Todo)
```c++
#include "../../include/Object/xuiObject.h"
```
## 📰更新日志
<h3 style="font-family:Consolas">2023.08.09 - 周三</h3>
<ul style="font-family:Consolas">
    <li>对于xBaseObject的更改</li> 
    <ul>
        <li>合并了xBaseObject和xuiObject</li>
        <li>废弃xBaseObject</li>
    </ul>
    <li>实现了xPainter的基本绘图函数</li>
    <li>添加了xuiObject中的GetReal系列函数，用于更新绘图区域</li>
    <li>添加了xuiObject.h中的注释</li>
    <li>添加了xuiObject::SetChangeChildrensAttributeOnSetAttribute()函数，用于设置是否在对象属性被设置或更新时更改子对象的相同属性</li>
    <li>添加了xuiObject::GetFocus()和xuiObject::LostFocus，并添加对应的二次处理函数:xuiObject::onGetFocusEvent()和xuiObject::onLostFocusEvent()</li>
</ul>