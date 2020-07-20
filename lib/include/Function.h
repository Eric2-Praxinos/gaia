#pragma once

/**
 * Base Abstract Function class
 */

template<typename tReturnType, typename ... tArguments>
class cFunctionA {
public:
    virtual bool isEqualTo(const cFunctionA<tReturnType, tArguments ...>* iFunction) const = 0;
    virtual tReturnType Call(tArguments ... iArgs) = 0;
    friend bool operator ==(const cFunctionA<tReturnType, tArguments ...>& iLHS, const cFunctionA<tReturnType, tArguments ...>& iRHS) {
        return iLHS.isEqualTo(&iRHS);
    }
};


/**
 * Function Class
 */

template <typename tReturnType, typename ... tArguments>
class cFunction : public cFunctionA<tReturnType, tArguments ...> {
public:
    typedef cFunctionA<tReturnType, tArguments ...> tBaseType;
    typedef cFunction<tReturnType, tArguments ...> tSelfType;
    typedef tReturnType (*tFunction)(tArguments ...);

public:
    cFunction(tFunction iFunction) :
        mFunction(iFunction)
    {

    }

public:
    virtual tReturnType Call (tArguments ... iArgs) {
        return mFunction(iArgs ...);
    }

    virtual bool isEqualTo(const tBaseType* iFunction) const
    {
        const tSelfType* converted = dynamic_cast<const tSelfType*>(iFunction);
        if (!converted)
        {
            return false;
        }

        return mFunction == converted->mFunction;
    }

public:
    tFunction mFunction;
};

/**
 * Method Class
 */

template <typename tCaller, typename tReturnType, typename ... tArguments>
class cMethod : public cFunctionA<tReturnType, tArguments ...> {
public:
    typedef cFunctionA<tReturnType, tArguments ...> tBaseType;
    typedef cMethod<tCaller, tReturnType, tArguments ...> tSelfType;
    typedef tReturnType (tCaller::*tMethod)(tArguments ...);

public:
    cMethod(tCaller* iCaller, tMethod iMethod) :
        mCaller(iCaller),
        mMethod(iMethod)
    {

    }

public:
    virtual tReturnType Call (tArguments ... iArgs) {
        return (mCaller->*mMethod)(iArgs ...);
    }

    virtual bool isEqualTo(const tBaseType* iFunction) const
    {
        const tSelfType* converted = dynamic_cast<const tSelfType*>(iFunction);
        if (!converted)
        {
            return false;
        }

        return mCaller == converted->mCaller && mMethod == converted->mMethod;
    }

public:
    tCaller* mCaller;
    tMethod mMethod;
};



//======

/**
 * Function Without First argument
 */

template <typename tReturnType, typename tIgnore, typename ... tArguments>
class cFunctionIgnore : public cFunctionA<tReturnType, tIgnore, tArguments ...> {
public:
    typedef cFunctionA<tReturnType, tIgnore, tArguments ...> tBaseType;
    typedef cFunctionIgnore<tReturnType, tIgnore, tArguments ...> tSelfType;
    typedef tReturnType (*tFunction)(tArguments ...);

public:
    cFunctionIgnore(tFunction iFunction) :
        mFunction(iFunction)
    {
    }

public:
    virtual tReturnType Call (tIgnore, tArguments ... iArgs) {
        return mFunction(iArgs ...);
    }

    virtual bool isEqualTo(const tBaseType* iFunction) const
    {
        const tSelfType* converted = dynamic_cast<const tSelfType*>(iFunction);
        if (!converted)
        {
            return false;
        }

        return mFunction == converted->mFunction;
    }

public:
    tFunction mFunction;
};

//======

/**
 * Method Without First argument
 */

template <typename tCaller, typename tReturnType, typename tIgnore, typename ... tArguments>
class cMethodIgnore : public cFunctionA<tReturnType, tIgnore, tArguments ...> {
public:
    typedef cFunctionA<tReturnType, tIgnore, tArguments ...> tBaseType;
    typedef cMethodIgnore<tCaller, tReturnType, tIgnore, tArguments ...> tSelfType;
    typedef tReturnType (tCaller::*tMethod)(tArguments ...);

public:
    cMethodIgnore(tCaller* iCaller, tMethod iMethod) :
        mCaller(iCaller),
        mMethod(iMethod)
    {

    }

public:
    virtual tReturnType Call (tIgnore, tArguments ... iArgs) {
        return (mCaller->*mMethod)(iArgs ...);
    }

    virtual bool isEqualTo(const tBaseType* iFunction) const
    {
        const tSelfType* converted = dynamic_cast<const tSelfType*>(iFunction);
        if (!converted)
        {
            return false;
        }

        return mCaller == converted->mCaller && mMethod == converted->mMethod;
    }

public:
    tCaller* mCaller;
    tMethod mMethod;
};
