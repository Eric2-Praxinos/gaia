#pragma once

#include "ComponentData.h"
#include "ComponentFixedDataEditionHandler.h"

#define DATA ::nGaia::cComponentFixedData

#define EDIT(...) \
for(int GAIA_DATA_EDITION_COUNTER = 0; GAIA_DATA_EDITION_COUNTER < 1;) \
for(auto GAIA_DATA_EDITION_TUPLES = ::nGaia::RetainEditables(__VA_ARGS__); GAIA_DATA_EDITION_COUNTER < 1;::nGaia::ReleaseEditables(__VA_ARGS__))

#define AS(...) \
for(auto [__VA_ARGS__] = GAIA_DATA_EDITION_TUPLES;GAIA_DATA_EDITION_COUNTER < 1; GAIA_DATA_EDITION_COUNTER++)

#define EDITASSAME(...) \
EDIT(__VA_ARGS__) \
AS(__VA_ARGS__)

namespace nGaia {

template<typename T>
class cComponentFixedData : public cComponentData
{
private:
	typedef cComponentFixedData<T> tSelfType;

public:
	class cEditionHandler
	{
		public:
		cEditionHandler()
		{
			mData->Unlock();
		}

		cEditionHandler(cComponentFixedData* iData) :
			mData(iData)
		{
			mData->Lock();
		}

		private:
		cComponentFixedData* mData;
	};

public:
    // destructor
    ~cComponentFixedData()
	{
	}

    // default constructor
    cComponentFixedData()
	{
		throw "Error !"
	}

    // assignment constructor
    cComponentFixedData(const T& iValue) :
		mValue(iValue)
	{

	}

public:
	const T& Value() const
	{
		Emit(EventGetBefore);
		Emit(EventGetAfter);
		return mValue;
	}

public:
    T& RetainEditable() {
		//TODO: Add global mutex, for edition lock
		Lock();
        return mValue;
    }

    T& ReleaseEditable() {
		//TODO: Add global mutex, for edition lock
		Unlock();
        return mValue;
    }

	operator const T&() const
	{
		const T& t = Value();
		return t;
	}

	const T& operator ()() const
	{
		const T& t = Value();
		return t;
	}

	virtual void Lock() {
		//Lock Edition
		//Lock Get
	}

	virtual void Unlock() {
		//Lock Edition
		//Lock Get
		Emit(EventChanged);
	}

	// friend cComponentFixedDataEditionHandler;

private:
    T mValue;
};

template <class ...Types>
auto RetainEditables(Types&... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::forward_as_tuple(iData.RetainEditable()...);
}

template <class ... Types>
auto ReleaseEditables(Types&... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::forward_as_tuple(iData.ReleaseEditable()...);
}
/*
auto GetEditionHandlers(::std::vector<cComponentData&> iData) {
	return iData;
	//TODO: Add global mutex, for edition lock
	// return ::std::make_tuple(iData.GetEditionHandler()...);
}*/

/* template <class ...Types>
auto GetEditionHandlers(Types... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::make_tuple(iData.GetEditionHandler()...);
} */

}