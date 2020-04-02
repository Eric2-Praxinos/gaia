#include <functional>

namespace nGaia {

template<typename T>
class cComponentComputedData
{
private:
	typedef cComponentComputedData<T> tSelfType;

private:
    const ::std::function<T ()> mFunction;
	T mCachedValue;

public:
    // default constructor
    cComponentComputedData()
	{
		throw "Error !"
	}

    // assignment constructor
    cComponentComputedData(::std::function<T ()> iFunction) :
		mFunction(iFunction),
		mCachedValue(iFunction())
	{

	}

	const T& Value() const
	{
		return mCachedValue;
	}

    // property get
    operator T() const
	{
		return mCachedValue;
	}

	void RefreshValue() {
		mCachedValue = mFunction();
	}
};

}