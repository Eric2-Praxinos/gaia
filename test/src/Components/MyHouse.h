#include "Gaia.h"
#include <vector>

class cRoom {
	DATA<int> mWidth;
	DATA<int> mLength;
};

BEGIN_COMPONENT(cMyHouse)

	// DECLARE DATA
	DATA<int> mWidth = 40;
	DATA<double> mHeight = 50;
	DATA<long> mLength = 60;

	// DECLARE COMPUTED DATA
	COMPUTED<double> mArea = [this]() {
		return this->mWidth * this->mHeight;
	};

	// DECLARE COMPUTED DATA
	COMPUTED<double> mVolume = [this]() {
		return this->mArea * this->mLength;
	};

END_COMPONENT()
