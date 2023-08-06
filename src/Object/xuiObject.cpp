#include "xuiObject.h"
using namespace xc::ui;

xuiObject::xuiObject(xuiObject* parent) 
    : xBaseObject(parent) { 
    RegisterCallBack("paint", PaintEvent);
    RegisterCallBack("pointer", PointerEvent);
    RegisterCallBack("touch", TouchEvent);
    RegisterCallBack("keyPress", KeyPressEvent);
}
xuiObject::~xuiObject() { xBaseObject::~xBaseObject(); }

void xuiObject::Resize(Rectangle rect) {
    m_area.Resize(rect);
}
void xuiObject::Move(Coordinate coordinate) {
    m_area.MoveTo(coordinate);
}
Area xuiObject::GetArea() {
    return m_area;
}

void xuiObject::PaintEvent(xPaintEvent* event) {
    xPainter* painter = event->GetPainter();
    painter->SetArea(m_area);
    this->onPaintEvent(painter);

    m_focusObj->Notify(event);
    if(m_children.empty()) {
        event->Accept();
        return;
    }
    event->Ignore();
    for(xBaseObject* child : m_children) {
        if(child == m_focusObj) {
            continue;
        } 
        child->Notify(event);
    }
}

void xuiObject::PointerEvent(xPointerEvent* event) {
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

void xuiObject::TouchEvent(xTouchEvent* event) {
    onTouchEvent(event->GetCoordinate());
}

void xuiObject::KeyPressEvent(xKeyPressEvent* event) {
    onKeyPressEvent(event->GetKeyValue());
}

void xuiObject::Hidden() { m_visible = false; }
void xuiObject::Show() { m_visible = true; }
void xuiObject::SetVisible(bool visible) { m_visible = visible; }
bool xuiObject::GetVisible() { return m_visible; }

void xuiObject::Enabled() { m_enabled = true; }
void xuiObject::Disabled() { m_enabled = true; }