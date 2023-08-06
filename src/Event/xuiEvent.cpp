#include "../../include/Event/xuiEvent.hpp"
using namespace xc::ui;

//xPaintEvent
xPaintEvent::xPaintEvent(xPainter* painter) : m_painter(painter), xEvent("paint") { }
xPaintEvent::~xPaintEvent() { m_painter = nullptr; }

xc::xPainter* xPaintEvent::GetPainter() { return m_painter; }

//xPointerEvent
xPointerEvent::xPointerEvent(xPointerEventType type, Coordinate coordinate) : m_type(type), m_coordinate(coordinate), xEvent("pointer") { } 
xPointerEvent::~xPointerEvent() { }
 
xPointerEvent::xPointerEventType& xPointerEvent::GetType() { return m_type; }
Coordinate& xPointerEvent::GetCoordinate() { return m_coordinate; }

//xKeyPressEvent
xKeyPressEvent::xKeyPressEvent(uint32_t keyValue) : m_keyValue(keyValue), xEvent("keyPress") { } 
xKeyPressEvent::~xKeyPressEvent() { }

const uint32_t& xKeyPressEvent::GetKeyValue() { return m_keyValue; }

//xTouchEvent
xTouchEvent::xTouchEvent(xTouchEventType type, Coordinate coordinate) : m_type(type), m_coordinate(coordinate), xEvent("touch") { } 
xTouchEvent::~xTouchEvent() { }

xTouchEvent::xTouchEventType& xTouchEvent::GetType() { return m_type; }
Coordinate& xTouchEvent::GetCoordinate() { return m_coordinate; }

