#include "ComponentData.h"
#include "ComponentComputedData.h"

namespace nGaia {

// PREPROCESSOR SHORTCUTS

#define BEGIN_COMPONENT(NAME) \
class NAME : public ::nGaia::cComponent { \
public: \
	~NAME() {} \
	NAME() {}

#define END_COMPONENT() \
};

class cComponent {
public:
	~cComponent();
	cComponent();
};

}