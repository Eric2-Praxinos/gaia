#pragma once

#include <string>
#include <vector>

namespace nGaia {

	class cRoute {
	public:
		~cRoute();
		cRoute();

	public:
		const ::std::string& Path() const;
		const ::std::string& Name() const;
		const ::std::string& ComponentId() const;

	private:
		const ::std::string mPath;
		const ::std::string mName;
		const ::std::string mComponentId;

	};

	class cRouter {
	public:
		~cRouter();
		cRouter();

	public:
		const cRoute& Route(const ::std::string& iPath) const;

	public:
		void Push(const cRoute& iRoute);

	private:
		std::vector<cRoute> mRoutes;
	};

}