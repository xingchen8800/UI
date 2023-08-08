#ifndef __TYPES_H_
#define __TYPES_H_
#define __USE_STDINT__
/*
    头文件:types.h
    简介:定义基本的数据类型
*/

/*
                      //         baseObject           //
    xScreen.loop() -> xuiObject.paint(xPainter(xScreen)) -> xScreen.push();
*/
namespace xc {
    namespace Std {
        class Area;
        class Rectangle;
        class Coordinate;
    }
}
namespace xc {
    namespace Std {
        class String;
    }
}


#ifdef __USE_STDINT__
#include <stdint.h>
#else
//8位整型
typedef unsigned char uint8_t;
typedef unsigned char u8t;
typedef char int8_t;
typedef char i8t;

//16位整型
typedef unsigned short uint16_t;
typedef unsigned short u16t;
typedef short int16_t;
typedef short i16t;

//32位整型
typedef unsigned long int uint32_t;
typedef unsigned long int u32t;
typedef long int int32_t;
typedef long int i32t;

//64位整型
typedef unsigned long long int uint64_t;
typedef unsigned long long int u64t;
typedef long long int int64_t;
typedef long long int i64t;
#endif

//函数
//数学
namespace xc {
    namespace Std {
        namespace Maths {
            constexpr double PI = 3.1415926;
            float floorf(float x);
            double floor(double x);
            long double floorl(long double x);
            template<class num_t>
            num_t abs(num_t x);
            double sqrt(double x);
            
            double sin(double x);
            double cos(double x);
            double tan(double x);
        }
    }
}

namespace xc {
    namespace Std {
        //颜色
        struct Colour {
            uint16_t r, g, b;
        };

        //坐标
        class Coordinate {
            friend Area;
        public:
            //构造函数
            Coordinate();
            Coordinate(int64_t x, int64_t y);
            Coordinate(const Coordinate&);

            //析构
            ~Coordinate();

            //相对坐标和绝对坐标的转换
            static Coordinate ToRelativeCoordinate(Coordinate& parent, Coordinate& child);
            static Coordinate ToAbsoluteCoordinate(Coordinate& parent, Coordinate& child);

            //移动
            void MoveTo(int64_t x, int64_t y);
            void MoveTo(Coordinate&);
            void SetX(int64_t);
            void SetY(int64_t);

            //获取
            const int64_t& GetX();
            const int64_t& GetY();

            //运算符
            Coordinate& operator=(Coordinate& _right); //赋值
            Coordinate operator-(Coordinate& _right);
            Coordinate operator+(Coordinate& _right);
            Coordinate& operator-=(Coordinate& _right);
            Coordinate& operator+=(Coordinate& _right);
            bool operator==(Coordinate& _right);

        private:
            int64_t m_x, m_y;
        };

        //矩形
        class Rectangle {
            friend Area;
        public:
            //构造函数
            Rectangle();
            Rectangle(uint64_t width, uint64_t height);
            Rectangle(const Rectangle&);

            //析构函数
            ~Rectangle();

            //设置大小
            void Resize(uint64_t width, uint64_t height);
            void Resize(Rectangle&);
            void SetWidth(uint64_t);
            void SetHeight(uint64_t);

            //获取
            const uint64_t& GetWidth();
            const uint64_t& GetHeight();
            const uint64_t& GetSize();

            //运算符
            Rectangle& operator=(Rectangle& _right);
            bool operator>(Rectangle& _right);
            bool operator<(Rectangle& _right);
            bool operator>=(Rectangle& _right);
            bool operator<=(Rectangle& _right);
            bool operator==(Rectangle& _right);

        private:
            uint64_t m_width, m_height;
        };

        //区域
        class Area : public Rectangle, public Coordinate {
        public:
            Area();
            Area(int64_t x, int64_t y, uint64_t w, uint64_t h);
            Area(const Area&);

            ~Area();

            static bool IsOverlap(Area& a, Area& b);
            static bool IsPointInArea(Area& a, Coordinate& point);

            Coordinate& GetCoordinate() { return *this; }
            Rectangle& GetRectangle() { return *this; }

            Area& operator=(Area& _right);
            bool operator==(Area& _right);
        };
    }
}

#endif