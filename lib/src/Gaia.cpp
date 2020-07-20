#include "Gaia.h"
#include <stdio.h>

namespace nGaia {
	void init(::nGaia::cRouter* iRouter) {
		/*
			initComponents();
			updateGUI();
			bool out = false;
			while(!out)
			{
				bool eventProcessed = processEvents();
				if (!eventProcessed)
				{
					sleep(time) //sleep a bit of time to avoid processor to be to busy doing nothing
				}
			}
		*/
		printf("Gaia Initialized !\n");
	}

	void updateGUI() {
		//Call Refresh on the highest components to be refreshed and refresh only the dirty parts
	}

	bool processEvents() {
		return true;
	}
}