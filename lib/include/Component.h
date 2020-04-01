namespace nGaia {

class cComponent {
public:
	~cComponent();
	cComponent();
};

template<typename T>
class cObserve
{
    T mValue;

public:
    // default constructor
    cObserve()
	{
		throw "Error !"
	}

    // assignment constructor
    cObserve(const T& iValue) : mValue(iValue) {

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
    cObserve<T>& operator=(const T& iValue)
    {
        mValue = iValue;
        return *this;
    }

	cObserve<T>& operator++()
	{
		mValue++;
		return *this;
	}

	cObserve<T> operator++(int)
	{
		Observe<T> old = Observe<T>(*this)
		mValue++;
		return old;
	}

	cObserve<T>& operator--()
	{
		mValue--;
		return *this;
	}

	cObserve<T> operator--(int)
	{
		Observe<T> old = Observe<T>(*this)
		mValue--;
		return old;
	}

	/* bool operator->*(T a, T b)
	bool operator->(T a, T b)
	*/

	cObserve<T>& operator+=(T& iValue)
	{
		mValue += iValue;
		return *this;
	}

	cObserve<T>& operator-=(T& iValue)
	{
		mValue -= iValue;
		return *this;
	}

	cObserve<T>& operator*=(T& iValue)
	{
		mValue *= iValue;
		return *this;
	}

	cObserve<T>& operator/=(T& iValue)
	{
		mValue /= iValue;
		return *this;
	}

	cObserve<T>& operator%=(T& iValue)
	{
		mValue %= iValue;
		return *this;
	}

	cObserve<T>& operator^=(T& iValue)
	{
		mValue ^= iValue;
		return *this;
	}

	cObserve<T>& operator&=(T& iValue)
	{
		mValue &= iValue;
		return *this;
	}

	cObserve<T>& operator|=(T& iValue)
	{
		mValue |= iValue;
		return *this;
	}

	cObserve<T>& operator<<(T& iValue)
	{
		mValue << iValue;
		return *this;
	}

	cObserve<T>& operator>>(T& iValue)
	{
		mValue >> iValue;
		return *this;
	}

	cObserve<T>& operator>>=(T& iValue)
	{
		mValue >>= iValue;
		return *this;
	}

	cObserve<T>& operator<<=(T& iValue)
	{
		mValue <<= iValue;
		return *this;
	}

};

// special behavior for the assignment of doubles
/* template<> observe<double>& observe<double>::operator =(const double& value)
{
    _value = value;
    cout << "new double value is " << _value << endl;
    return *this;
} */

}