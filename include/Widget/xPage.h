#ifndef __XPAGE_H_
#define __XPAGE_H_

#include "../Object/xuiObject.h"

namespace xc {
    namespace ui  {
        //空白页
        class xPage : public xuiObject {
        public:
            //构造+析构
            xPage(xuiObject* parent);
            ~xPage();
        };
    }
}

#endif
