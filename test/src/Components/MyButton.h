#include "Gaia.h"

BEGIN_COMPONENT(cMyButton)
	::nGaia::cObserve<int> mWidth = 50;
	::nGaia::cObserve<double> mHeight = 100;
END_COMPONENT()