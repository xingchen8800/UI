#include "../../include/Std/types.h"
#include "../../include/Std/String.hpp"

Coordinate::Coordinate() { }
Coordinate::Coordinate(int64_t x, int64_t y) : m_x(x), m_y(y) { }
Coordinate::Coordinate(const Coordinate& _right) {
    this->m_x = _right.m_x;
    this->m_y = _right.m_x;
}


Coordinate::~Coordinate() { }

//相对坐标和绝对坐标的转换
Coordinate Coordinate::ToRelativeCoordinate(Coordinate &parent, Coordinate &child) {
    Coordinate ret = child - parent;
    return ret;
}
Coordinate Coordinate::ToAbsoluteCoordinate(Coordinate &parent, Coordinate &child) {
    Coordinate ret = child + parent;
    return ret;
}

//移动
void Coordinate::MoveTo(int64_t x, int64_t y) {
    this->m_x = x, this->m_y = y;
}
void Coordinate::MoveTo(Coordinate& _r) {
    this->m_x = _r.m_x, this->m_y = _r.m_y;
}
void Coordinate::SetX(int64_t x) {
    this->m_x = x;
}
void Coordinate::SetY(int64_t y) {
    this->m_y = y;
}

//获取
const int64_t& Coordinate::GetX() { return m_x; }
const int64_t& Coordinate::GetY() { return m_y; }

//运算符
Coordinate& Coordinate::operator=(Coordinate& _right) {
    this->m_x = _right.m_x;
    this->m_y = _right.m_y;
    return *this;
}
Coordinate Coordinate::operator-(Coordinate& _right) {
    Coordinate ret(this->m_x - _right.m_x, this->m_y - _right.m_y);
    return ret;
}
Coordinate Coordinate::operator+(Coordinate& _right) {
    Coordinate ret(this->m_x + _right.m_x, this->m_y + _right.m_y);
    return ret;
}
Coordinate& Coordinate::operator-=(Coordinate& _right) {
    this->m_x -= _right.m_x;
    this->m_y -= _right.m_y;
    return *this;
}
Coordinate& Coordinate::operator+=(Coordinate& _right) {
    this->m_x += _right.m_x;
    this->m_y += _right.m_y;
    return *this;
}
bool Coordinate::operator==(Coordinate& _right) {
    return (this->m_x == _right.m_x) && (this->m_y == _right.m_y);
}


//构造函数
Rectangle::Rectangle() { }
Rectangle::Rectangle(uint64_t width, uint64_t height) : m_width(width), m_height(height) { }
Rectangle::Rectangle(const Rectangle& _r) {
    this->m_height = _r.m_height, this->m_width = _r.m_width;
}

//析构函数
Rectangle::~Rectangle() { }

//设置大小
void Rectangle::Resize(uint64_t width, uint64_t height) { 
    this->m_height = height, this->m_width = width;
}
void Rectangle::Resize(Rectangle& _r) {
    this->m_height = _r.m_height, this->m_width = _r.m_width;
}
void Rectangle::SetWidth(uint64_t w) {
    this->m_width = w;
}
void Rectangle::SetHeight(uint64_t h) {
    this->m_height = h;
}

//获取
const uint64_t& Rectangle::GetWidth() {
    return m_width;
}
const uint64_t& Rectangle::GetHeight() {
    return m_height;
}
const uint64_t& Rectangle::GetSize() {
    return m_height * m_width;
}

//运算符
Rectangle& Rectangle::operator=(Rectangle& _right) {
    this->m_width = _right.m_width;
    this->m_height = _right.m_height;
    return *this;
}
bool Rectangle::operator>(Rectangle& _right) {
    return this->GetSize() > _right.GetSize();
}
bool Rectangle::operator<(Rectangle& _right) {
    return this->GetSize() < _right.GetSize();
}
bool Rectangle::operator>=(Rectangle& _right) {
    return this->GetSize() >= _right.GetSize();
}
bool Rectangle::operator<=(Rectangle& _right) {
    return this->GetSize() <= _right.GetSize();
}
bool Rectangle::operator==(Rectangle& _right) {
    return this->GetSize() == _right.GetSize();
}


Area::Area() : Rectangle(), Coordinate() { }
Area::Area(int64_t x, int64_t y, uint64_t w, uint64_t h) : Rectangle(w, h), Coordinate(x, y) { } 
Area::Area(const Area& _right) {
    this->m_x = _right.m_x;
    this->m_y = _right.m_y;
    this->m_width = _right.m_width;
    this->m_height = _right.m_height;
}

Area::~Area() { }

bool Area::IsOverlap(Area &a, Area &b) {
    if(a.m_x + a.m_width >= b.m_x && a.m_x <= b.m_x) {
        return true;
    } 
    if(a.m_y + a.m_height >= b.m_y && a.m_y <= b.m_y) {
        return true;
    }
    return false;
}

Area& Area::operator=(Area& _right) {
    this->Resize(_right.m_width, _right.m_height);
    this->MoveTo(_right.m_x, _right.m_y);
    return *this;
}
bool Area::operator==(Area& _right) {
    return this->m_x == _right.m_x && this->m_y == _right.m_y &&
           this->m_width == _right.m_width && this->m_height == _right.m_height;
}
