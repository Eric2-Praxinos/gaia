#pragma once

#include "Event.h"

#define DECLARE_EVENT static cEventType
#define DEFINE_EVENT(CLASS_NAME, EVENT_NAME) decltype(CLASS_NAME::EVENT_NAME) CLASS_NAME::EVENT_NAME

template <typename tCaller>
class cEventSender {
public:
    virtual ~cEventSender()
    {

    }

    template<typename ... tArguments>
    class cEventType : public cEvent<tCaller, tArguments ...> {

    };

    template <typename ... tArguments>
    void Emit(cEvent<tCaller, tArguments ...>& iEvent, tArguments ... iArgs) const {
        iEvent(dynamic_cast<const tCaller*>(this), iArgs...);
    }
};