#pragma once

#include "Dependency.h"
#include <functional>
#include <list>

namespace nGaia {

template<typename T>
class cComponentData : public cDependency
{
public:
    // default constructor
    ~cComponentData()
	{
	}

    // assignment constructor
    cComponentData()
	{
	}

	virtual const T& Value() const = 0;
};

class cDataManager
{
public:
	static cDataManager* Instance()
	{
		static cDataManager* instance = 0;
		if( !instance )
		{
			instance = new cDataManager();
		}
		return instance;
	}

public:
	~cDataManager()
	{

	}

	cDataManager() :
		mBeforeGet(),
		mAfterGet()
	{

	}
public:
	void BeforeGet(cDependency* iDependency)
	{
		::std::for_each(mBeforeGet.begin(), mBeforeGet.end(), [iDependency](const ::std::function<void (cDependency*)>* iFunction) { (*iFunction)(iDependency); });
    }

	void AfterGet(cDependency* iDependency)
	{
		::std::for_each(mAfterGet.begin(), mAfterGet.end(), [iDependency](const ::std::function<void (cDependency*)>* iFunction) { (*iFunction)(iDependency); });
    }

	void AddBeforeGetListener(::std::function<void (cDependency*)>* iFunction)
	{
		mBeforeGet.push_back(iFunction);
	}

	void AddAfterGetListener(::std::function<void (cDependency*)>* iFunction)
	{
		mAfterGet.push_back(iFunction);
	}

	void RemoveBeforeGetListener(::std::function< void (cDependency*) >* iFunction)
	{
		mBeforeGet.remove(iFunction);
	}

	void RemoveAfterGetListener(::std::function< void (cDependency*) >* iFunction)
	{
		mAfterGet.remove(iFunction);
	}

private:
	::std::list<::std::function<void (cDependency*)>*> mBeforeGet;
	::std::list<::std::function<void (cDependency*)>*> mAfterGet;
};

}