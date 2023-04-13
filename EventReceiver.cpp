#include "EventReceiver.h"

EventReceiver::EventReceiver(sol::table& Rcvr) :
    mSelf(Rcvr)
{
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
    return mSelf["OnEvent"](mSelf, event);
}
