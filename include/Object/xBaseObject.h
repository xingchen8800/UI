#ifndef __XBASEOBJECT_H_
#define __XBASEOBJECT_H_
#include "../Std/types.h"
#include "../Std/Vector.hpp"
#include "../Std/Map.hpp"
#include "../Std/String.hpp"
#include "../Std/Function.hpp"
#include "../Event/xEvent.hpp"

using namespace xc::Std;

namespace xc {
    namespace ui {
        class xuiObject;
    }
    //基础对象类
    class xBaseObject {
        friend ui::xuiObject;
        // //回调函数类型定义
        // typedef void (*CallBack_t)(xBaseObject*, const char*);
    public:
        //构造+析构
        xBaseObject(xBaseObject* parent = nullptr);
        ~xBaseObject();

        //事件相关
        static void SendEvent(xBaseObject* obj, xEvent* event); //给对象(obj)发送一个事件(event)  
        void RegisterCallBack(String eventName, Function<void(xEvent*)>  cb); //注册事件：当事件(eventName)发生时，调用回调函数(cb)
    
    protected:
        virtual void Notify(xEvent* event); //接受事件的内部实现
    private:
        xBaseObject* m_parent;
        Vector<xBaseObject*> m_children;
        Map<String, Function<void(xEvent*)> > m_callbacks;
    };
}

#endif