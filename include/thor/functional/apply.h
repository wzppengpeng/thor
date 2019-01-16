#ifndef THOR_FUNCTIONAL_APPLY_H_
#define THOR_FUNCTIONAL_APPLY_H_

#include <tuple>

#include "invoke.h"

/**
 * input a function object and a tuple params
 * invoke the function
 * F f;
 * Tuple t;
 * auto x = Apply(f, t);
 */

TF_NS_BEGIN

namespace details {

template<int I>
struct ApplyHelper {
    template<typename F, typename T, typename... Args>
    static auto Call(F&& f, T&& t, Args&&... args)
        -> decltype(ApplyHelper<I - 1>::Call(std::forward<F>(f),
                std::forward<T>(t), std::get<I - 1>(std::forward<T>(t)),
                std::forward<Args>(args)...)) {
        return ApplyHelper<I - 1>::Call(std::forward<F>(f),
                std::forward<T>(t), std::get<I - 1>(std::forward<T>(t)),
                std::forward<Args>(args)...);
    }
};

template<>
struct ApplyHelper<0> {
    template<typename F, typename T, typename... Args>
    static auto Call(F&& f, T&& t, Args&&... args)
        -> decltype(TF_NS::Invoke(std::forward<F>(f), std::forward<Args>(args)...)) {
        return TF_NS::Invoke(std::forward<F>(f), std::forward<Args>(args)...);
    }
};

} //details

template<typename F, typename T>
constexpr auto Apply(F&& f, T&& t)
    -> decltype(details::ApplyHelper<std::tuple_size<typename std::decay<T>::type>::value>::Call(
        std::forward<F>(f), std::forward<T>(t))) {
    return details::ApplyHelper<std::tuple_size<typename std::decay<T>::type>::value>::Call(
        std::forward<F>(f), std::forward<T>(t));
} // can support constexpr since C++14

TF_NS_END

#endif /*THOR_FUNCTIONAL_APPLY_H_*/