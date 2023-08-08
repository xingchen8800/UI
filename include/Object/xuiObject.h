#ifndef __XUIOBJECT_H_
#define __XUIOBJECT_H_

#include "xBaseObject.h"
#include "../Std/types.h"
#include "../Std/Vector.hpp"
#include "../Std/Map.hpp"
#include "../Std/String.hpp"
#include "../Std/Function.hpp"
#include "../Device/xPainter.hpp"
#include "../Event/xuiEvent.hpp"

using namespace xc::Std;

namespace xc {
    namespace ui {
        //xuiObject 适用于GUI的xBaseObject类
        class xuiObject {
            friend xScreen; //可以让xScreen(屏幕类)访问本类中的private(私有)内容(指各个事件函数)
        public:
            //构造和析构
            xuiObject(xuiObject* parent = nullptr);
            ~xuiObject();
                
            //事件相关
            static void SendEvent(xuiObject* obj, xEvent* event); //给对象(obj)发送一个事件(event)  
            void RegisterCallBack(String eventName, Std::Function<void(const char*)> cb); //注册事件：当事件(eventName)发生时，调用回调函数(cb)

            //有关显示区域的函数
            void Resize(Rectangle rect);        //更改尺寸
            void Move(Coordinate coordinate);   //更改坐标(相对于parent)
            const Area& GetArea();              //获取区域信息(m_area[Area])

            //Todo:
            //void SetFont(xFont font, uint8_t size);
            //xFont& GetFont();
            //uint8_t GetFontSize();
            //
            //void SetContextMenu(xContextMenu* menu);
            //xContextMenu* GetContextMenu();
            //

            //可视相关的函数(visible)
            void Hidden();                  //隐藏
            void Show();                    //显示
            void SetVisible(bool visible);  //设置是(true)否(false)可视
            const bool& GetVisible();       //获取是(true)否(false)可视

            //启用和停用
            void Enabled();     //启用
            void Disabled();    //停用

            //设置是否可以获取焦点
            void SetCanGetFocus();  //是
            void SetCantGetFocus(); //否

            //设置是否可以接受事件
            void SetCanAcceptKeyPressEvent(bool);   //键盘
            void SetCanAcceptTouchEvent(bool);      //触摸
            void SetCanAcceptPointerEvent(bool);    //指针

            //获取
            xuiObject* GetParent();
        protected:
            //[虚函数]事件的第二次处理
            virtual void onPaintEvent(xPainter* painter) = 0;   
            virtual void onPointerMoveEvent(Coordinate coordinate) = 0;
            virtual void onPointerClickStartEvent(bool button) = 0;
            virtual void onPointerClickStopEvent(bool button) = 0;
            virtual void onTouchMoveEvent(Coordinate coordiante) = 0;
            virtual void onTouchStartEvent(Coordinate coordinate) = 0;
            virtual void onTouchStopEvent(Coordinate coordinate) = 0;
            virtual void onKeyPressDownEvent(uint32_t keyValue) = 0;
            virtual void onKeyPressUpEvent(uint32_t keyValue) = 0;
            virtual void onGetFocusEvent(xPainter* painter) = 0;
            virtual void onLostFocusEvent(xPainter* painter) = 0;
        private:
            //事件的第一次处理
            void PaintEvent(const char* data); //xPaintEvent
            void PointerEvent(const char* data); //xPointerEvent
            void TouchEvent(const char* data); //xTouchEvent
            void KeyPressEvent(const char* data); //xKeyPressEvent
            void GetFocusEvent(const char* data); //xPaintEvent
            void LostFocusEvent(const char* data); //xPaintEvent

            void Notify(xEvent* event); //接受事件的内部实现

            //成员对象
            xuiObject* m_focusObj;                                          //当前有焦点的对象[xuiObject]
            Area m_area;                                                    //当前的显示区域[Area]
            bool m_focused = false;                                         //当前是(true)否(false)被聚焦[bool]
            xuiObject* m_parent;                                            //父对象[xuiObject*]
            Vector<xuiObject*> m_children;                                  //子对象[Vector<xuiObjet*>]
            Map<String, Std::Function<void(const char*)> > m_callbacks;     //回调函数[Map<String, Function<void(const char*)> >]

            //配置型选项
            bool m_visible = true;                  //当前是(true)否(false)可视[bool]
            bool m_enabled = true;                  //当前是(true)否(false)可用[bool]
            bool m_can_get_focus = true;            //是(true)否(false)可以被聚焦[bool]
            bool m_accept_key_press_event = true;   //是(true)否(false)可以接受键盘事件[bool]
            bool m_accept_touch_event = true;       //是(true)否(false)可以接受触摸事件[bool]
            bool m_accept_pointer_event = true;     //是(true)否(false)可以接受指针事件[bool]

            //不可(不要)在类外更改的成员对象
            bool mhide_on_get_focus_event = false;
            bool mhide_on_lost_focus_event = false;
            //Todo:
            //xFont font;
            //uint8_t font_size;
        };
    }
}

#endif