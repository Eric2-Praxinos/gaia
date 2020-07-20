#pragma once

#include "Function.h"
#include <vector>
#include <map>
#include <algorithm>

#define ADD_EVENT_LISTENER(SENDER, EVENT, ...) (SENDER)->EVENT.AddListener(SENDER, __VA_ARGS__)
#define ADD_GLOBAL_EVENT_LISTENER(SENDER_CLASS, EVENT, ...) SENDER_CLASS::EVENT.AddGlobalListener(__VA_ARGS__)
#define REMOVE_EVENT_LISTENER(SENDER, EVENT, ...) (SENDER)->EVENT.RemoveListener(SENDER, __VA_ARGS__)
#define REMOVE_GLOBAL_EVENT_LISTENER(SENDER_CLASS, EVENT, ...) SENDER_CLASS::EVENT.RemoveGlobalListener(__VA_ARGS__)

//======

template <typename tCaller, typename ... tArguments>
class cEvent {
public:
    typedef cFunctionA<void, const tCaller*, tArguments ...> tFunctionA;

    typedef void (*tFunctionPointer)(const tCaller*, tArguments ...);
    typedef void (*tFunctionPointerWithoutCaller)(tArguments ...);
    typedef cFunction<void, const tCaller*, tArguments ...> tFunction;
    typedef cFunctionIgnore<void, const tCaller*, tArguments ...> tFunctionWithoutCaller;

    template <typename T>
    using tMethodPointer = void (T::*)(const tCaller*, tArguments ...);

    template <typename T>
    using tMethodPointerWithoutCaller = void (T::*)(tArguments ...);

    template <typename T>
    using tMethod = cMethod<T, void, const tCaller*, tArguments ...>;

    template <typename T>
    using tMethodWithoutCaller = cMethodIgnore<T, void, const tCaller*, tArguments ...>;

public:
    //Adds Global Callback from a simple function pointer
    void AddGlobalListener(tFunctionPointer iFunction) {
        mGlobalCallbacks.push_back(new tFunction(iFunction));
    }

    //Adds Global Callback from a simple function pointer without caller argument
    void AddGlobalListener(tFunctionPointerWithoutCaller iFunction) {
        mGlobalCallbacks.push_back(new tFunctionWithoutCaller(iFunction));
    }

    //Adds Global Callback from a pointer to member function
    template<typename tReceiver>
    void AddGlobalListener(tReceiver* iReceiver, tMethodPointer<tReceiver> iMethod) {
        mGlobalCallbacks.push_back(new tMethod<tReceiver>(iReceiver, iMethod));
    }

    //Adds Global Callback from a pointer to member function without caller argument
    template<typename tReceiver>
    void AddGlobalListener(tReceiver* iReceiver, tMethodPointerWithoutCaller<tReceiver> iMethod) {
        mGlobalCallbacks.push_back(new tMethodWithoutCaller<tReceiver>(iReceiver, iMethod));
    }

    //Removes Global Callback from a simple function pointer
    void RemoveGlobalListener(tFunctionPointer iFunction) {
        RemoveGlobalListener(new tFunction(iFunction));
    }

    //Removes Global Callback from a simple function pointer without caller argument
    void RemoveGlobalListener(tFunctionPointerWithoutCaller iFunction) {
        RemoveGlobalListener(new tFunctionWithoutCaller(iFunction));
    }

    //Removes Global Callback from a pointer to member function
    template<typename tReceiver>
    void RemoveGlobalListener(tReceiver* iReceiver, tMethodPointer<tReceiver> iMethod) {
        RemoveGlobalListener(new tMethod<tReceiver>(iReceiver, iMethod));
    }

    //Removes Global Callback from a pointer to member function without caller argument
    template<typename tReceiver>
    void RemoveGlobalListener(tReceiver* iReceiver, tMethodPointerWithoutCaller<tReceiver> iMethod) {
        RemoveGlobalListener(new tMethodWithoutCaller<tReceiver>(iReceiver, iMethod));
    }

    //Adds Object Callback from a simple function pointer
    void AddListener(const tCaller* iCaller, tFunctionPointer iFunction) {
        mObjectCallbacks[iCaller].push_back(new tFunction(iFunction));
    }

    //Adds Object Callback from a simple function pointer without caller argument
    void AddListener(const tCaller* iCaller, tFunctionPointerWithoutCaller iFunction) {
        mObjectCallbacks[iCaller].push_back(new tFunctionWithoutCaller(iFunction));
    }

    //Adds Object Callback from a pointer to member function
    template<typename tReceiver>
    void AddListener(const tCaller* iCaller, tReceiver* iReceiver, tMethodPointer<tReceiver> iMethod) {
        mObjectCallbacks[iCaller].push_back(new tMethod<tReceiver>(iReceiver, iMethod));
    }

    //Adds Object Callback from a pointer to member function without caller argument
    template<typename tReceiver>
    void AddListener(const tCaller* iCaller, tReceiver* iReceiver, tMethodPointerWithoutCaller<tReceiver> iMethod) {
        mObjectCallbacks[iCaller].push_back(new tMethodWithoutCaller<tReceiver>(iReceiver, iMethod));
    }

    //Removes Object Callback from a simple function pointer
    void RemoveListener(const tCaller* iCaller, tFunctionPointer iFunction) {
        RemoveListener(iCaller, new tFunction(iFunction));
    }

    //Removes Object Callback from a simple function pointer without caller argument
    void RemoveListener(const tCaller* iCaller, tFunctionPointerWithoutCaller iFunction) {
        RemoveListener(iCaller, new tFunctionWithoutCaller(iFunction));
    }

    //Removes Object Callback from a pointer to member function
    template<typename tReceiver>
    void RemoveListener(const tCaller* iCaller, tReceiver* iReceiver, tMethodPointer<tReceiver> iMethod) {
        RemoveListener(iCaller, new tMethod<tReceiver>(iReceiver, iMethod));
    }

    //Removes Object Callback from a pointer to member function
    template<typename tReceiver>
    void RemoveListener(const tCaller* iCaller, tReceiver* iReceiver, tMethodPointerWithoutCaller<tReceiver> iMethod) {
        RemoveListener(iCaller, new tMethodWithoutCaller<tReceiver>(iReceiver, iMethod));
    }

public:
    void operator ()(const tCaller* iCaller, tArguments ... iArgs) {
        //Call local first
        if (mObjectCallbacks.count(iCaller) > 0) {
            ::std::for_each(mObjectCallbacks[iCaller].begin(), mObjectCallbacks[iCaller].end(), [&](tFunctionA* iFunction) {
                iFunction->Call(iCaller, iArgs ...);
            });
        }

        //Call Global second
        ::std::for_each(mGlobalCallbacks.begin(), mGlobalCallbacks.end(), [&](tFunctionA* iFunction) {
            iFunction->Call(iCaller, iArgs ...);
        });
    }

private:
    void RemoveGlobalListener(const tFunctionA* iFunction) {
        const auto& it = std::find_if(mGlobalCallbacks.begin(), mGlobalCallbacks.end(), [&](const tFunctionA* iFunctionA) -> bool {
            return iFunctionA->isEqualTo(iFunction);
        });
        if (it == mGlobalCallbacks.end())
            return;
        delete (*it);
        mGlobalCallbacks.erase(it);
    }

    void RemoveListener(const tCaller* iCaller, const tFunctionA* iFunction) {
        if (mObjectCallbacks.count(iCaller) <= 0) {
            return;
        }

        const auto& it = std::find_if(mObjectCallbacks[iCaller].begin(), mObjectCallbacks[iCaller].end(), [&](const tFunctionA* iFunctionA) -> bool {
            return iFunctionA->isEqualTo(iFunction);
        });
        if (it == mObjectCallbacks[iCaller].end())
            return;

        delete (*it);
        mObjectCallbacks[iCaller].erase(it);

        if (mObjectCallbacks[iCaller].size() <= 0) {
            mObjectCallbacks.erase(iCaller);
        }
    }

private:
    ::std::vector<tFunctionA*> mGlobalCallbacks;
    ::std::map<const tCaller*, ::std::vector<tFunctionA*>> mObjectCallbacks;
};
