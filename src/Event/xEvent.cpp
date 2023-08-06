#include "../../include/Event/xEvent.hpp"
using namespace xc;

xEvent::xEvent(Std::String name) : m_name(name) { }
xEvent::~xEvent() { }

void xEvent::Accept() { m_accepted = true; } 
void xEvent::Ignore() { m_accepted = false; }

bool xEvent::IsAccepted() { return m_accepted; }
bool xEvent::IsSendByUser() { return m_sendbyuser; }

Std::String xEvent::GetName() { return m_name; } 

void xEvent::SetSendByUser(bool isSendbyuser) { m_sendbyuser = isSendbyuser; }