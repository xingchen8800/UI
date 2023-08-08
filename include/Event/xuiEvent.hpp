#ifndef __XUIEVENT_HPP_
#define __XUIEVENT_HPP_
#include "../Device/xPainter.h"
#include "xEvent.hpp"

namespace xc {
    namespace ui {
        //绘图事件
        class xPaintEvent : public xEvent {
        public:
            xPaintEvent(xPainter* painter);
            ~xPaintEvent();

            xPainter* GetPainter();
        private:
            xPainter* m_painter;
        };

        //指针事件
        class xPointerEvent : public xEvent {
        public:
           //指针事件的类型 
            typedef enum {
                PointerMove,                //移动事件
                PointerLeftClickStart,      //左键开始点击事件
                PointerLeftClickStop,       //左键结束点击事件  
                PointerRightClickStart,     //右键开始点击事件
                PointerRightClickStop       //右键结束点击事件
            } xPointerEventType;
        public:
            //构造+析构
            xPointerEvent(xPointerEventType type, Coordinate coordinate);
            ~xPointerEvent();

            //获取类型和坐标
            xPointerEventType& GetType();
            Coordinate& GetCoordinate();
        private:
            xPointerEventType m_type;
            Coordinate m_coordinate;
        };

        class xKeyPressEvent : public xEvent {
        public:
            typedef enum {
                KeyPressDown,
                KeyPressUp
            } xKeyPressEventType;
        public:
            xKeyPressEvent(xKeyPressEventType type, uint32_t keyValue);
            ~xKeyPressEvent();

            const uint32_t& GetKeyValue();
            const xKeyPressEventType& GetType() { return m_type; }
        private:
            uint32_t m_keyValue;
            xKeyPressEventType m_type;
        };
        
        class xTouchEvent : public xEvent { 
        public:
            typedef enum {
                TouchStart,
                TouchStop,
                TouchMove
            } xTouchEventType;
        public:
            xTouchEvent(xTouchEventType type, Coordinate Coordinate);
            ~xTouchEvent();

            xTouchEventType& GetType();
            Coordinate& GetCoordinate();
        private:
            xTouchEventType m_type;
            Coordinate m_coordinate;
        };

        class xTimerEvent : public xEvent {
        public:
            xTimerEvent(uint64_t msec);
            ~xTimerEvent();

            const uint64_t& GetTime();
        private:
            uint64_t m_msec;
        };
    }
}

#endif