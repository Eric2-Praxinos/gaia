#pragma once

#include "ComponentData.h"
#include <functional>

#define COMPUTED ::nGaia::cComponentComputedData
namespace nGaia {

template<typename T>
class cComponentComputedData : public cComponentData
{
private:
    const ::std::function<T ()> mFunction;
	mutable T mValue;
	bool mIsDirty;
	long mGetCBRefCount;
	::std::vector<const cComponentData*> mDependencies;

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
		mValue(),
		mIsDirty(true),
		mGetCBRefCount(0),
		mDependencies()
	{
	}

public:

	void OnComponentDataGetAfter(const cComponentData* iDependency)
	{
		mGetCBRefCount--;
	}

	void OnDependencyChanged(const cComponentData* iDependency)
	{
		mIsDirty = true;
		Emit(EventChanged);
	}

	void OnComponentDataGetBefore(const cComponentData* iDependency)
	{
		if (mGetCBRefCount == 0) {
			mDependencies.push_back(iDependency);
			ADD_EVENT_LISTENER(iDependency, EventChanged, this, &cComponentComputedData<T>::OnDependencyChanged);
		}
		mGetCBRefCount++;
	}

    // property get
    operator const T&() const
	{
		Emit(EventGetBefore);
		const_cast<cComponentComputedData<T>*>(this)->RefreshValue();
		Emit(EventGetAfter);
		return mValue;
	}

    // property get
    const T& operator ()() const
	{
		Emit(EventGetBefore);
		const_cast<cComponentComputedData<T>*>(this)->RefreshValue();
		Emit(EventGetAfter);
		return mValue;
	}

	void RefreshValue() {
		//TODO: Mutex Lock
		//For this object, the refresh function must not be called by anyone other than this thread
		if (mIsDirty) {
			//TODO: Lock all Data Edition Globally and in every threads
			//TODO: Wait for all data edition to be done
			/* if (mIsRefreshing) {
				throw "Infinite dependency loop in dependencies !";
			} */
			for (auto it = mDependencies.begin(); it != mDependencies.end(); ++it)
			{
				REMOVE_EVENT_LISTENER(*it, EventChanged, this, &cComponentComputedData<T>::OnDependencyChanged);
			}
			mDependencies.clear();

			ADD_GLOBAL_EVENT_LISTENER(cComponentData, EventGetBefore, this, &cComponentComputedData<T>::OnComponentDataGetBefore);
			ADD_GLOBAL_EVENT_LISTENER(cComponentData, EventGetAfter, this, &cComponentComputedData<T>::OnComponentDataGetAfter);
			mValue =  mFunction();
			REMOVE_GLOBAL_EVENT_LISTENER(cComponentData, EventGetBefore, this, &cComponentComputedData<T>::OnComponentDataGetBefore);
			REMOVE_GLOBAL_EVENT_LISTENER(cComponentData, EventGetAfter, this, &cComponentComputedData<T>::OnComponentDataGetAfter);
			mIsDirty = false;
		}
	}
};

}