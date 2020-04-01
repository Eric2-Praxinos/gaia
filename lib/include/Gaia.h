#pragma once

#include "Router.h"
#include "Component.h"

namespace nGaia {
	void init(::nGaia::cRouter* iRouter);
}

// PREPROCESSOR SHORTCUTS

#define BEGIN_COMPONENT(NAME) \
class NAME : public ::nGaia::cComponent { \
public: \
	~NAME() {} \
	NAME() {}

#define END_COMPONENT() \
};