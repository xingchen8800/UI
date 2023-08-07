// #include "../../include/Object/xBaseObject.h"
// using namespace xc;

// xBaseObject::xBaseObject(xBaseObject* parent) : m_parent(parent) {
//     if(m_parent != nullptr) m_parent->m_children.push(this);
// }

// xBaseObject::~xBaseObject() {
//     if(m_parent != nullptr) {
//         int64_t index = m_parent->m_children.find(this);
//         if(index != -1) {
//             m_parent->m_children.deleteAt(index);
//         }
//     }
//     for(xBaseObject* child : m_children) {
//         delete child;
//         child = nullptr;
//     }
//     if(!m_children.empty()) m_children.clear();
// }

// void xBaseObject::SendEvent(xBaseObject* obj, xEvent* event) {
//     obj->Notify(event);
// }
// void xBaseObject::RegisterCallBack(String eventName, Std::Function<void(const char*)> cb) {
//     m_callbacks.insert(eventName, cb);
// }

// void xBaseObject::Notify(xEvent* event) {
//     Std::Function<void(const char*)> find = m_callbacks.get(event->GetName());
//     try { find((const char*)event); }
//     catch(int error) {
//         event->Ignore();
//     }
// }