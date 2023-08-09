#include "../../include/Widget/xPage.h"
using namespace xc::ui;

xPage::xPage(xuiObject* parent) : xuiObject(parent) {

}
xPage::~xPage() { }

void xPage::SetBackgroundColor(Color c) {
    SetAttribute("background-color", (const char*)&c);
}
Color* xPage::GetBackgroundColor() {
    return (Color*)GetAttribute("background-color");
}

void xPage::onPaintEvent(xPainter* painter) {
    Color* color = GetBackgroundColor();
    if((const char*)color == "\0") {
        painter->FillRectangle(Area(Coordinate(0, 0), GetRectangle()), {0, 0, 0});
    } else {
        painter->FillRectangle(Area(Coordinate(0, 0), GetRectangle()), *color);
    }
}