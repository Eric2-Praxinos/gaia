#include "Gaia.h"
#include <vector>

#define DATA ::nGaia::cComponentFixedData
#define COMPUTED ::nGaia::cComponentComputedData
template<typename T, typename S>
class cTest {

};

BEGIN_COMPONENT(cMyButton)

	// DECLARE DATA
	DATA<int> mWidth = 50;
	DATA<double> mHeight = 50;
	DATA<long> mLength = 50;
	DATA<cTest<int, double>> mVector1 = cTest<int, double>();

	// DECLARE COMPUTED DATA
	COMPUTED<double> mArea = [this]() {
		return this->mWidth * this->mHeight;
	};

	// DECLARE COMPUTED DATA
	COMPUTED<double> mVolume = [this]() {
		return this->mArea * this->mLength;
	};



END_COMPONENT()