#pragma once

#include "ComponentData.h"
#include <functional>

#define COMPUTED ::nGaia::cComponentComputedData
namespace nGaia {

template<typename T>
class cComponentComputedData : public cComponentData<T>
{
private:
	typedef cComponentComputedData<T> tSelfType;

private:
    const ::std::function<T ()> mFunction;
	mutable T mCachedValue;
	bool mIsDirty;
	long mGetCBRefCount;

private:
	::std::function<void (cDependency*)> mBeforeGetCB;
	::std::function<void (cDependency*)> mAfterGetCB;

public:
    // destructor
    ~cComponentComputedData()
	{
	}

    // default constructor
    cComponentComputedData()
	{
		throw "Error !"
	}

    // assignment constructor
    cComponentComputedData(const ::std::function<T ()>& iFunction) :
		mFunction(iFunction),
		mCachedValue(),
		mIsDirty(true),
		mBeforeGetCB(),
		mAfterGetCB(),
		mGetCBRefCount(0)
	{
		mBeforeGetCB = [this](cDependency* iDependency) {
			if (mGetCBRefCount == 0) {
				AddUpDependency(iDependency);
			}
			mGetCBRefCount++;
		};
		mAfterGetCB = [this](cDependency* iDependency) {
			mGetCBRefCount--;
		};
	}

public:
	virtual const T& Value() const
	{
		cDataManager::Instance()->BeforeGet(const_cast<cComponentComputedData*>(this));
		const_cast<cComponentComputedData<T>*>(this)->RefreshValue();
		cDataManager::Instance()->AfterGet(const_cast<cComponentComputedData*>(this));
		return mCachedValue;
	}

public:
	virtual void OnDependencyBeforeChanged(const cDependency* iDependency)
	{
		mIsDirty = true;
	}

	virtual void OnDependencyAfterChanged(const cDependency* iDependency)
	{
		RefreshValue();
	}

    // property get
    operator T() const
	{
		return Value();
	}

	T GenerateValue() {
		if (mGetCBRefCount != 0) {
			throw "Infinite dependency loop !";
		}
		ClearUpDependencies();
		cDataManager::Instance()->AddBeforeGetListener(&mBeforeGetCB);
		cDataManager::Instance()->AddAfterGetListener(&mAfterGetCB);
		T value =  mFunction();
		cDataManager::Instance()->RemoveBeforeGetListener(&mBeforeGetCB);
		cDataManager::Instance()->RemoveAfterGetListener(&mAfterGetCB);
		return value;
	}

	void RefreshValue() {
		if (mIsDirty) {
			mCachedValue = GenerateValue();
			mIsDirty = false;
		}
	}
};

}