#pragma once

#include "ComponentData.h"

#define DATA ::nGaia::cComponentFixedData

#define EDIT(...) \
for(int GAIA_DATA_EDITION_COUNTER = 0; GAIA_DATA_EDITION_COUNTER < 1;) \
for(auto GAIA_DATA_EDITION_HANDLER = ::nGaia::GetEditionHandlers(__VA_ARGS__); GAIA_DATA_EDITION_COUNTER < 1;) \
for(auto GAIA_DATA_EDITION_TUPLES = ::nGaia::GetEditables(__VA_ARGS__); GAIA_DATA_EDITION_COUNTER < 1;)

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
    T& GetEditable() {
		//TODO: Add global mutex, for edition lock
        return mValue;
    }

    T& GetEditionHandler() {
		//TODO: Add global mutex, for edition lock
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

	void Lock() {
		//Lock Edition
		//Lock Get
	}

	void Unlock() {
		//Lock Edition
		//Lock Get
	}

private:
    T mValue;
};

template <class ...Types>
auto GetEditables(Types&... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::forward_as_tuple(iData.GetEditable()...);
}

template <class ...Types>
auto GetEditionHandlers(Types... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::make_tuple(iData.GetEditable()...);
}

}