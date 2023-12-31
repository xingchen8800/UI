#include "../../include/Object/xuiObject.h"
using namespace xc::ui;

xuiObject::xuiObject(xuiObject* parent) 
    : m_parent(parent) {    
    if(m_parent != nullptr) m_parent->m_children.push(this);
    //注册事件
    RegisterCallBack("paint", PaintEvent);
    RegisterCallBack("pointer", PointerEvent);
    RegisterCallBack("touch", TouchEvent);
    RegisterCallBack("keyPress", KeyPressEvent);
    RegisterCallBack("getFocus", GetFocusEvent);
    RegisterCallBack("lostFocus", GetFocusEvent);
}

xuiObject::~xuiObject() { 
    if(m_parent != nullptr) {
        int64_t index = m_parent->m_children.find(this);
        if(index != -1) {
            m_parent->m_children.deleteAt(index);
        }
    }
    for(xuiObject* child : m_children) {
        delete child;
        child = nullptr;
    }
    if(!m_children.empty()) m_children.clear(); 
}

void xuiObject::SendEvent(xuiObject* obj, xEvent* event) {
    obj->Notify(event);
}
void xuiObject::RegisterCallBack(String eventName, Std::Function<void(const char*)> cb) {
    m_callbacks.insert(eventName, cb);
}

void xuiObject::Notify(xEvent* event) {
    Std::Function<void(const char*)> find = m_callbacks.get(event->GetName());
    try { find((const char*)event); }
    catch(int error) {
        event->Ignore();
    }
}

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
    painter->SetArea(GetArea());                   //先更改可以绘图的区域(this->m_area[Area])
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
    for(xuiObject* child : m_children) {
        child->Notify(event);
    }
    event->Accept();                        //最后返回accept(成功)
}

void xuiObject::PointerEvent(const char* data) {
    xPointerEvent* event = (xPointerEvent*)data;
    if(!m_accept_pointer_event) {
        event->Ignore();
        return;
    }
    Coordinate& coordinate = event->GetCoordinate();
    coordinate -= this->m_area.GetCoordinate();
    
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

    for(xuiObject* child : m_children) {
        if(Area::IsPointInArea(child->m_area, coordinate)) {
            child->Notify(event);
        }                    
    }

    event->Accept();
}

void xuiObject::TouchEvent(const char* data) {
    xTouchEvent* event = (xTouchEvent*)data;
    if(!m_accept_touch_event) {
        event->Ignore();
        return;
    }
    Coordinate& coordinate = event->GetCoordinate();
    coordinate -= this->m_area.GetCoordinate();
    
    switch (event->GetType()) {
        case xTouchEvent::TouchMove: onTouchMoveEvent(coordinate); break;
        case xTouchEvent::TouchStart: onTouchStartEvent(coordinate); break;
        case xTouchEvent::TouchStop: onTouchStopEvent(coordinate); break;
    }

    for(xuiObject* child : m_children) {
        if(Area::IsPointInArea(child->m_area, coordinate)) {
            child->Notify(event);
        }                    
    }
    event->Accept();
}

void xuiObject::KeyPressEvent(const char* data) {
    xKeyPressEvent* event = (xKeyPressEvent*)data;
    if(!m_accept_key_press_event) {
        event->Ignore();
        return;
    }

    switch (event->GetType()) {
    case xKeyPressEvent::KeyPressDown:
        onKeyPressDownEvent(event->GetKeyValue());
        break;
    
    case xKeyPressEvent::KeyPressUp:
        onKeyPressUpEvent(event->GetKeyValue());
        break;
    }    

    event->Accept();
}

void xuiObject::GetFocusEvent(const char* data) {
    xEvent* event = (xEvent*)data;
    if(m_can_get_focus) {
        event->Accept();
        mhide_on_get_focus_event = true;
        m_focused = true;
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
    m_focused = false;
}


void xuiObject::Hidden() { m_visible = false; }
void xuiObject::Show() { m_visible = true; }
void xuiObject::SetVisible(bool visible) { m_visible = visible; }
const bool& xuiObject::GetVisible() { return m_visible; }

void xuiObject::Enabled() { m_enabled = true; }
void xuiObject::Disabled() { m_enabled = true; }

void xuiObject::SetCanGetFocus() { m_can_get_focus = true; }
void xuiObject::SetCantGetFocus() { m_can_get_focus = false; }

xuiObject* xuiObject::GetParent() { return m_parent; }

void xuiObject::SetCanAcceptKeyPressEvent(bool x) { m_accept_key_press_event = x; }
void xuiObject::SetCanAcceptTouchEvent(bool x) { m_accept_touch_event = x; }
void xuiObject::SetCanAcceptPointerEvent(bool x) { m_accept_pointer_event = x; }

void xuiObject::SetChangeChildrensAttributeOnSetAttribute(bool x) { m_change_childrens_attribute_on_set_attribute = x; }

void xuiObject::onPaintEvent(xPainter* painter) { }
void xuiObject::onPointerMoveEvent(Coordinate coordinate) { }
void xuiObject::onPointerClickStartEvent(bool button) { }
void xuiObject::onPointerClickStopEvent(bool button) { }
void xuiObject::onTouchMoveEvent(Coordinate coordiante) { }
void xuiObject::onTouchStartEvent(Coordinate coordinate) { }
void xuiObject::onTouchStopEvent(Coordinate coordinate) { }
void xuiObject::onKeyPressDownEvent(uint32_t keyValue) { }
void xuiObject::onKeyPressUpEvent(uint32_t keyValue) { }
void xuiObject::onGetFocusEvent(xPainter* painter) { }
void xuiObject::onLostFocusEvent(xPainter* painter) { }

int64_t xuiObject::GetRealX() {
    if(m_parent != nullptr) return m_area.GetX() + m_parent->GetRealX();
    else return m_area.GetX(); 
}
int64_t xuiObject::GetRealY() {
    if(m_parent != nullptr) return m_area.GetY() + m_parent->GetRealY();
    else return m_area.GetX(); 
}
Coordinate xuiObject::GetRealCoordinate() {
    return Coordinate(GetRealX(), GetRealY());
}
Area xuiObject::GetRealArea() {
    return Area(GetRealX(), GetRealY(), m_area.GetWidth(), m_area.GetHeight());
}
Rectangle xuiObject::GetRectangle() { return m_area.GetRectangle(); }

void xuiObject::SetAttribute(String attributeName, const char* attributeData) {
    m_attributes.insert(attributeName, attributeData);
    if(m_change_childrens_attribute_on_set_attribute) {
        for(xuiObject* child : m_children) {
            child->SetAttribute(attributeName, attributeData);
        }
    }
}
const char* xuiObject::GetAttribute(String attributeName) { 
    try {
        const char* data = m_attributes.get(attributeName);
        return data;
    } catch (int error) {
        return "\0";
    }

}