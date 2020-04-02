#include "Gaia.h"
#include <vector>

#define DATA ::nGaia::cComponentData
#define COMPUTED ::nGaia::cComponentComputedData
template<typename T, typename S>
class cTest {

};

BEGIN_COMPONENT(cMyButton)

	// DECLARE DATA
	DATA<int> mWidth = 50;
	DATA<double> mHeight = 50;
	DATA<cTest<int, double>> mVector1 = cTest<int, double>();

	// DECLARE COMPUTED DATA
	COMPUTED<double> mArea = [this]() {
		//TODO: Refresh Cache Value when mWidth or mHeight Changes
		//TODO: Then to the same with a Computed used by another Computed
		return this->mWidth * this->mHeight;
	};



END_COMPONENT()