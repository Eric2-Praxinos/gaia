#include <tuple>

namespace nGaia {

template<class ... Types>
class cComponentFixedDataEditionHandler {
private:
    typedef

public:
    ~cComponentFixedDataEditionHandler()
    {
        Unlock();
    }

    cComponentFixedDataEditionHandler(Types& ... iData) :
        mData(::std::make_tuple(iData...))
    {
        Lock();
    }

private:
    void Lock() {
        for(int i = 0; i < ::std::tuple_size<Types...>::value; i++) {
            auto data = ::std::get<i>(mData);
            data.Lock();
        }
    }

    void Unlock() {
        for(int i = 0; i < ::std::tuple_size<Types...>::value; i++) {
            auto data = ::std::get<i>(mData);*
            data.Unlock();
        }
    }

private:
    ::std::tuple<Types...> mData;
}