#ifndef __XEVENT_HPP_
#define __XEVENT_HPP_
#include "../Std/String.hpp"
namespace xc {
    //事件基类
    class xObject;
    class xEvent {
        friend xObject;
    public:
        xEvent(Std::String name);
        virtual ~xEvent();

        void Accept();
        void Ignore();

        bool IsAccepted();
        bool IsSendByUser();
        
        Std::String GetName();
    private:
        void SetSendByUser(bool isSendbyuser);

        Std::String m_name;
        bool m_accepted, m_sendbyuser;
    };
}

#endif