#include "xuiObject.h"
using namespace xc::ui;

xuiObject::xuiObject(xuiObject* parent) 
    : xBaseObject(parent) { 
    //注册事件
    RegisterCallBack("paint", PaintEvent);
    RegisterCallBack("pointer", PointerEvent);
    RegisterCallBack("touch", TouchEvent);
    RegisterCallBack("keyPress", KeyPressEvent);
    RegisterCallBack("getFocus", GetFocusEvent);
    RegisterCallBack("lostFocus", GetFocusEvent);
}
xuiObject::~xuiObject() { xBaseObject::~xBaseObject(); }

void xuiObject::Resize(Rectangle rect) {
    m_area.Resize(rect);
}
void xuiObject::Move(Coordinate coordinate) {
    m_area.MoveTo(coordinate);
}
const Area& xuiObject::GetArea() {
    return m_area;
}

void xuiObject::PaintEvent(const char* data) {
    xPaintEvent* event = (xPaintEvent*)data;    //获取event[xPaintEvent*]
    xPainter* painter = event->GetPainter();    //获取painter[xPainter*]
    painter->SetArea(m_area);                   //先更改可以绘图的区域(this->m_area[Area])
    if(mhide_on_get_focus_event) {              //再判断是否有getFocus或lostFocus的临时事件
        this->onGetFocusEvent(painter);
        mhide_on_get_focus_event = false;
    } else if(mhide_on_lost_focus_event) {
        this->onLostFocusEvent(painter);
        mhide_on_lost_focus_event = false;
    } else {
        this->onPaintEvent(painter);
    }
    //然后判断m_children[Vector(动态数组)]是否为空
    if(m_children.empty()) {
        event->Accept();
        return;
    }
    //再然后遍历除了m_focusObj[xBaseObject]的所有子对象，并给其发送paint事件
    for(xBaseObject* child : m_children) {
        child->Notify(event);
    }
    event->Accept();                        //最后返回accept(成功)
}

void xuiObject::PointerEvent(const char* data) {
    xPointerEvent* event = (xPointerEvent*)data;
    Coordinate& coordinate = event->GetCoordinate();
    switch (event->GetType()) {
    case xPointerEvent::PointerMove:
        onPointerMoveEvent(coordinate);
        break;
    
    case xPointerEvent::PointerLeftClickStart:
        onPointerClickStartEvent(false);
        break;

    case xPointerEvent::PointerLeftClickStop:
        onPointerClickStopEvent(false);
        break;

    case xPointerEvent::PointerRightClickStart:
        onPointerClickStartEvent(true);
        break;
    
    case xPointerEvent::PointerRightClickStop:
        onPointerClickStopEvent(true);
        break;
    }
    event->Accept();
}

void xuiObject::TouchEvent(const char* data) {
    xTouchEvent* event = (xTouchEvent*)data;
    onTouchEvent(event->GetCoordinate());
}

void xuiObject::KeyPressEvent(const char* data) {
    xKeyPressEvent* event = (xKeyPressEvent*)data;
    onKeyPressEvent(event->GetKeyValue());
}

void xuiObject::GetFocusEvent(const char* data) {
    xEvent* event = (xEvent*)data;
    if(m_can_get_focus) {
        event->Accept();
        mhide_on_get_focus_event = true;
    } else {
        event->Ignore();
    }
}

void xuiObject::LostFocusEvent(const char* data) {
    xEvent* event = (xEvent*)data;
    if(m_focused == false) { 
        event->Ignore(); 
        return;
    }
    event->Accept();
    mhide_on_lost_focus_event = true;
}


void xuiObject::Hidden() { m_visible = false; }
void xuiObject::Show() { m_visible = true; }
void xuiObject::SetVisible(bool visible) { m_visible = visible; }
const bool& xuiObject::GetVisible() { return m_visible; }

void xuiObject::Enabled() { m_enabled = true; }
void xuiObject::Disabled() { m_enabled = true; }

void xuiObject::SetCanGetFocus() { m_can_get_focus = true; }
void xuiObject::SetCantGetFocus() { m_can_get_focus = false; }