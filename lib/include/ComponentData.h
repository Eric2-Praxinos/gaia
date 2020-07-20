#pragma once

#include "EventSender.h"

namespace nGaia {

class cComponentData : public cEventSender<cComponentData>
{
public:
	DECLARE_EVENT<> EventGetBefore;
	DECLARE_EVENT<> EventGetAfter;
	DECLARE_EVENT<> EventChanged;


public:
    // default constructor
    ~cComponentData()
	{
	}

    // assignment constructor
    cComponentData()
	{
	}

public:

};

}