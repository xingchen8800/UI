#ifndef __XSCREEN_H_
#define __XSCREEN_H_

#include "../Std/types.h"
#include "../Object/xuiObject.h"
#include "xInputDevice.h"

namespace xc {
    class xScreen {
        //                          x         y         
        typedef void (*DrawPixel_t)(uint64_t, uint64_t, Colour);
    public:
        xScreen(DrawPixel_t func, Rectangle size);

        void DrawPixel(uint64_t x, uint64_t y, Colour c);

        int16_t loop(ui::xuiObject* baseObj);
        void Push();
    private:

        Colour *m_buffer;
        Rectangle m_size;
        xPainter *m_painter;
    };
}

#endif