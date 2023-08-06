#ifndef __XINPUTDEVICE_H_
#define __XINPUTDEVICE_H_

#include "../Std/Function.hpp"

namespace xc {
    class xInputDevice {

    public:
        xInputDevice(Std::Function<void()>);  
    };
}

#endif