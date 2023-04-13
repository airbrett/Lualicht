#pragma once
#include <irrlicht.h>
#include "sol/sol.hpp"

class EventReceiver : public irr::IEventReceiver
{
private:
    sol::table mSelf;

public:
    EventReceiver(sol::table& Rcvr);

    virtual bool OnEvent(const irr::SEvent& event);
};