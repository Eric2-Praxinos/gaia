#include <Application.h>
#include <windows.h>

namespace nGaia{

cApplication::~cApplication() {
}

cApplication::cApplication() {
	HINSTANCE AppInstance = (HINSTANCE)GetModuleHandle(NULL);
}

}