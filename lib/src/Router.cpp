#include "Router.h"

namespace nGaia {

cRoute::~cRoute() {

}

cRoute::cRoute() :
	mPath(),
	mName(),
	mComponentId()
{

}

const ::std::string&
cRoute::Path() const {
	return mPath;
}

const ::std::string&
cRoute::Name() const {
	return mName;
}

const ::std::string&
cRoute::ComponentId() const {
	return mComponentId;
}

cRouter::~cRouter() {

}

cRouter::cRouter() :
	mRoutes()
{

}

const cRoute&
cRouter::Route(const ::std::string& iPath) const {
	return mRoutes[0];
}

void
cRouter::Push(const cRoute& iRoute) {
	mRoutes.push_back(iRoute);
}

}