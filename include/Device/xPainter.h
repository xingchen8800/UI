#ifndef __XPAINTER_H_
#define __XPAINTER_H_

#include "../Std/types.h"
#include "../Std/String.hpp"
#include "xScreen.h"

namespace xc::ui {
    class xFont;
}

namespace xc {
    //绘图器
    class xPainter {
    private:
        //成员对象
        Area m_area;        //绘图区域[Area]
        xScreen* m_screen;  //绘图输出对象[xScreen*]
    public:
        //构造 + 析构
        xPainter(xScreen* screen, Area area);
        ~xPainter();

        //各种绘图函数
        //在point位置画颜色为c的点
        inline void DrawPixel(Coordinate point, Colour c);                          
        //在point位置填充大小为rect，颜色为c的矩形
        inline void FillRectangle(Coordinate point, Rectangle rect, Colour c);   
        //在区域rectangle中填充颜色为c的矩形   
        inline void FillRectangle(Area rectangle, Colour c);         
        //在point位置画大小为rect，颜色为c的矩形               
        inline void DrawRectangle(Coordinate point, Rectangle rect, Colour c);     
        //在区域rectangle中画颜色为c的矩形 
        inline void DrawRectangle(Area rectangle, Colour c);     
        //画一个以point为圆心，半径为r，颜色为c的圆                   
        inline void DrawCircle(Coordinate point, uint32_t r, Colour c);    
        //画一条从point1到point2，颜色为color的线         
        inline void DrawLine(Coordinate point1, Coordinate point2, Colour color);   
        //画一个左上角坐标为top_left，限制大小为size，字体为font，颜色为color的字符c
        inline void DrawChar(Coordinate top_left, Rectangle size, char c, ui::xFont font, Colour color); 
        //画一个限制区域为area，字体为font，颜色为color的字符c
        inline void DrawChar(Area area, char c, ui::xFont font, Colour color);      

        inline void SetArea(Area area) { m_area = area; }
    };
}

#endif