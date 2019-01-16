#ifndef THOR_FUNCTIONAL_INVOKE_H_
#define THOR_FUNCTIONAL_INVOKE_H_

#include <type_traits>

#include "common.h"

/**
 * invoke call function
 * invoke(Fun, args...)
 */

TF_NS_BEGIN

// the normal types
template<typename F, typename... Args,
    class = typename std::enable_if
        <!std::is_member_function_pointer
        <typename std::decay<F>::type>::value
        >::type
    >
constexpr auto Invoke(F&& f, Args&&... args)
    -> decltype(std::forward<F>(f)
                (std::forward<Args>(args)...)) {
    return std::forward<F>(f)
                (std::forward<Args>(args)...);
}

// the const member function
template<typename R, typename C, typename... DArgs, typename T, typename... Args>
constexpr auto Invoke(R(C::*f)(DArgs...) const, T&& t, Args&&... args)
    -> decltype((*t.*f)( std::forward<Args>(args)... )) {
    return (*t.*f)( std::forward<Args>(args)... );
}

// the member fucntion non-const
template<typename R, typename C, typename... DArgs, typename T, typename... Args>
constexpr auto Invoke(R(C::*f)(DArgs...), T&& t, Args&&... args)
    -> decltype((*t.*f)( std::forward<Args>(args)... )) {
    return (*t.*f)( std::forward<Args>(args)... );
}

TF_NS_END

#endif /*THOR_FUNCTIONAL_INVOKE_H_*/