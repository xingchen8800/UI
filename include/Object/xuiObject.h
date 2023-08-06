#ifndef __XUIOBJECT_H_
#define __XUIOBJECT_H_

#include "xBaseObject.h"
#include "../Screen/xPainter.hpp"
#include "../Event/xEvent.hpp"
#include "../Event/xuiEvent.hpp"

namespace xc {
    namespace ui {
        class xuiObject : public xBaseObject {
            friend xScreen;
        public:
            xuiObject(xuiObject* parent = nullptr);
            ~xuiObject();

            void Resize(Rectangle rect);
            void Move(Coordinate coordinate);
            Area GetArea();

            //Todo:
            //void SetFont(xFont font, uint8_t size);
            //xFont& GetFont();
            //uint8_t GetFontSize();
            //
            //void SetContextMenu(xContextMenu* menu);
            //xContextMenu* GetContextMenu();
            //
            void Hidden();
            void Show();
            void SetVisible(bool visible);
            bool GetVisible();

            void Enabled();
            void Disabled();

            virtual void onPaintEvent(xPainter* painter) = 0;   
            virtual void onPointerMoveEvent(Coordinate coordinate) = 0;
            virtual void onPointerClickStartEvent(bool button) = 0;
            virtual void onPointerClickStopEvent(bool button) = 0;
            virtual void onTouchEvent(Coordinate coordiante) = 0;
            virtual void onKeyPressEvent(uint32_t keyValue) = 0;
        private:
            void PaintEvent(xPaintEvent* event);
            void PointerEvent(xPointerEvent* event);
            void TouchEvent(xTouchEvent* event);
            void KeyPressEvent(xKeyPressEvent* event);

            xuiObject* m_focusObj;
            Area m_area;
            bool m_visible = true;
            bool m_enabled = true;
            //Todo:
            //xFont font;
            //uint8_t font_size;
        };
    }
}

#endif