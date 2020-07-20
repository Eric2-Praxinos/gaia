#pragma once

//#include <vector>
#include "ComponentData.h"

namespace nGaia {

class cComponentFixedDataEditionHandler {

public:
    ~cComponentFixedDataEditionHandler()
    {
        Unlock();
    }

    cComponentFixedDataEditionHandler(/*const ::std::vector<cComponentData*>& iData*/) //:
        //mData(iData)
    {
        Lock();
    }

private:
    void Lock() {
        /* for(int i = 0; i < ::std::tuple_size<::std::tuple<Types...>>::value; i++) {
            auto data = ::std::get<i>(mData);
            data.Lock();
        } */
    }

    void Unlock() {
        /* for(int i = 0; i < ::std::tuple_size<::std::tuple<Types...>>::value; i++) {
            auto data = ::std::get<i>(mData);
            data.Unlock();
        } */
    }

private:
    //::std::vector<cComponentData*> mData;
};

}