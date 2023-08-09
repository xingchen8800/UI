#ifndef __XPAINTER_H_
#define __XPAINTER_H_

#include "../Std/types.h"
#include "../Std/String.hpp"
#include "xScreen.h"

namespace xc {
    namespace ui {
        class xFont;
    }
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
        //在point位置画颜色为c的点(point是相对坐标)
        inline void DrawPixel(Coordinate point, Color c);                          
        //在point位置填充大小为rect，颜色为c的矩形(point是相对坐标)
        inline void FillRectangle(Coordinate point, Rectangle rect, Color c);   
        //在区域rectangle中填充颜色为c的矩形   
        inline void FillRectangle(Area rectangle, Color c);         
        //在point位置画大小为rect，颜色为c的矩形(point是相对坐标)             
        inline void DrawRectangle(Coordinate point, Rectangle rect, Color c);     
        //在区域rectangle中画颜色为c的矩形 
        inline void DrawRectangle(Area rectangle, Color c);     
        //画一个以point为圆心，半径为r，颜色为c的圆(point是相对坐标)                   
        inline void DrawCircle(Coordinate point, uint32_t r, Color c);    
        //画一条从point1到point2，颜色为color的线(point1和point2是相对坐标)         
        inline void DrawLine(Coordinate point1, Coordinate point2, Color color);   
        //画一个左上角坐标为top_left，限制大小为size，字体为font，颜色为color的字符c(top_left是相对坐标)
        inline void DrawChar(Coordinate top_left, Rectangle size, char c, ui::xFont font, Color color); 
        //画一个限制区域为area，字体为font，颜色为color的字符c
        inline void DrawChar(Area area, char c, ui::xFont font, Color color);      

        inline void SetArea(Area area) { 
            m_area = area;
        }
        inline const Area& GetArea() { return m_area; }
    };
}

#endif