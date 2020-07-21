#pragma once

#include "ComponentData.h"

#include <vector>

#define DATA ::nGaia::cComponentFixedData


#define EDIT(...) \
if (::nGaia::cEditionHandles GAIA_DATA_EDITION_HANDLES(__VA_ARGS__); true) \
if (auto GAIA_DATA_EDITION_TUPLE = ::nGaia::GetEditables(__VA_ARGS__); true)

#define AS(...) \
if (auto [__VA_ARGS__] = GAIA_DATA_EDITION_TUPLE; true)

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

private:
    T mValue;
};

template <class ...Types>
auto GetEditables(Types&... iData) {
	//TODO: Add global mutex, for edition lock
	return ::std::forward_as_tuple(iData.GetEditable()...);
}

class cEditionHandle
{
    public:
    virtual void EditStart() {};
    virtual void EditStop() {};
};

template <class T>
class cEditionHandleT : public cEditionHandle
{
    public:
    ~cEditionHandleT()
    {
    }

    cEditionHandleT(::nGaia::cComponentFixedData<T>& iData) :
        mData(iData)
    {
    }

    virtual void EditStart()
    {
        mData.Lock();

    }

    virtual void EditStop()
    {
        mData.Unlock();
    }

    ::nGaia::cComponentFixedData<T>& mData;
};


template <class ... Types>
class cEditionHandles
{
    public:
    ~cEditionHandles()
    {
        for (auto& handle: mHandles)
        {
            handle->EditStop();
            delete handle;
        }
    }

    cEditionHandles(Types& ... iData) :
        mHandles({new cEditionHandleT(iData)...})
    {
        for (auto& handle: mHandles)
            handle->EditStart();
    }

    ::std::vector<cEditionHandle*> mHandles;
};

}