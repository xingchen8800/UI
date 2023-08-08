#ifndef __XINPUTDEVICE_H_
#define __XINPUTDEVICE_H_

#include "../Std/Function.hpp"

namespace xc {
    class xInputDevice {
    public:
        typedef enum {
            InputDeviceType_Touch,
            InputDeviceType_Pointer,
            InputDeviceType_Key
        } xInputDeviceType;
    public:
        xInputDevice(Std::Function<void()>);  
    };
}

#endif