#pragma once

#include "ComponentData.h"

#define DATA ::nGaia::cComponentFixedData
namespace nGaia {

template<typename T>
class cComponentFixedData : public cComponentData<T>
{
private:
	typedef cComponentFixedData<T> tSelfType;

private:
    T mValue;

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
	virtual const T& Value() const
	{
		cDataManager::Instance()->BeforeGet(const_cast<cComponentFixedData*>(this));
		cDataManager::Instance()->AfterGet(const_cast<cComponentFixedData*>(this));
		return mValue;
	}

	void Value(const T& iValue)
	{
		BeforeChange();
		mValue = iValue;
		AfterChange();
	}

public:
	virtual void OnDependencyBeforeChanged(const cDependency* iDependency)
	{
		//Does nothing
	}

	virtual void OnDependencyAfterChanged(const cDependency* iDependency)
	{
		//Does nothing
	}

public:
    // property get
    operator T() const
	{
		return Value();
	}

    // property set
    tSelfType& operator=(const T& iValue)
    {
		BeforeChange();
        mValue = iValue;
		AfterChange();
        return *this;
    }

	tSelfType& operator++()
	{
		BeforeChange();
		mValue++;
		AfterChange();
		return *this;
	}

	tSelfType operator++(int)
	{
		tSelfType old = tSelfType(*this);
		BeforeChange();
		mValue++;
		AfterChange();
		return old;
	}

	tSelfType& operator--()
	{
		BeforeChange();
		mValue--;
		AfterChange();
		return *this;
	}

	tSelfType operator--(int)
	{
		tSelfType old = tSelfType(*this);
		BeforeChange();
		mValue--;
		AfterChange();
		return old;
	}

	/* bool operator->*(T a, T b)
	bool operator->(T a, T b)
	*/

	tSelfType& operator+=(T& iValue)
	{
		BeforeChange();
		mValue += iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator-=(T& iValue)
	{
		BeforeChange();
		mValue -= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator*=(T& iValue)
	{
		BeforeChange();
		mValue *= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator/=(T& iValue)
	{
		BeforeChange();
		mValue /= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator%=(T& iValue)
	{
		BeforeChange();
		mValue %= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator^=(T& iValue)
	{
		BeforeChange();
		mValue ^= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator&=(T& iValue)
	{
		BeforeChange();
		mValue &= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator|=(T& iValue)
	{
		BeforeChange();
		mValue |= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator>>=(T& iValue)
	{
		BeforeChange();
		mValue >>= iValue;
		AfterChange();
		return *this;
	}

	tSelfType& operator<<=(T& iValue)
	{
		BeforeChange();
		mValue <<= iValue;
		AfterChange();
		return *this;
	}

};

}