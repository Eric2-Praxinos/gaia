#include "GaiaOptions.h"

namespace nGaia {

// =========== GaiaOptions

GaiaOptions::~GaiaOptions()
{
}

GaiaOptions::GaiaOptions() :
	mOptions()
{
	InitWithDefaults();
}

void
GaiaOptions::InitWithDefaults() {
	tOptionMap::iterator it = GaiaOptions::DefaultOptions()->mOptions.begin();
	for (; it != GaiaOptions::DefaultOptions()->mOptions.end(); ++it) {
		mOptions[it->first] = (it->second)->clone();
	}
}

GaiaOptions*
GaiaOptions::DefaultOptions() {
	static GaiaOptions* options = 0;
	if (!options) {
		options = new GaiaOptions();
	}
	return options;
}

}