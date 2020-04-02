namespace nGaia {

template<typename T>
class cComponentData
{
private:
	typedef cComponentData<T> tSelfType;

private:
    T mValue;

public:
    // default constructor
    cComponentData()
	{
		throw "Error !"
	}

    // assignment constructor
    cComponentData(const T& iValue) :
		mValue(iValue)
	{

	}

	const T& Value() const
	{
		return mValue;
	}

	void Value(const T& iValue) const
	{
		mValue = iValue;
	}

    // property get
    operator T() const
	{
		return mValue;
	}

    // property set
    tSelfType& operator=(const T& iValue)
    {
        mValue = iValue;
        return *this;
    }

	tSelfType& operator++()
	{
		mValue++;
		return *this;
	}

	tSelfType operator++(int)
	{
		tSelfType old = tSelfType(*this)
		mValue++;
		return old;
	}

	tSelfType& operator--()
	{
		mValue--;
		return *this;
	}

	tSelfType operator--(int)
	{
		tSelfType old = tSelfType(*this)
		mValue--;
		return old;
	}

	/* bool operator->*(T a, T b)
	bool operator->(T a, T b)
	*/

	tSelfType& operator+=(T& iValue)
	{
		mValue += iValue;
		return *this;
	}

	tSelfType& operator-=(T& iValue)
	{
		mValue -= iValue;
		return *this;
	}

	tSelfType& operator*=(T& iValue)
	{
		mValue *= iValue;
		return *this;
	}

	tSelfType& operator/=(T& iValue)
	{
		mValue /= iValue;
		return *this;
	}

	tSelfType& operator%=(T& iValue)
	{
		mValue %= iValue;
		return *this;
	}

	tSelfType& operator^=(T& iValue)
	{
		mValue ^= iValue;
		return *this;
	}

	tSelfType& operator&=(T& iValue)
	{
		mValue &= iValue;
		return *this;
	}

	tSelfType& operator|=(T& iValue)
	{
		mValue |= iValue;
		return *this;
	}

	tSelfType& operator>>=(T& iValue)
	{
		mValue >>= iValue;
		return *this;
	}

	tSelfType& operator<<=(T& iValue)
	{
		mValue <<= iValue;
		return *this;
	}

};

}