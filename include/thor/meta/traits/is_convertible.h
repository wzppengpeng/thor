#ifndef THOR_META_TRAITS_IS_CONVERTIBLE_H_
#define THOR_META_TRAITS_IS_CONVERTIBLE_H_

#include "thor/meta/base/utils.h"

/**
 * judge the two input type T, U
 * return if T -> can convert to U
 */
TM_NS_BEGIN

template<typename T, typename U>
struct IsConvertible {

private:
    using Yes = char;
    using No = int;

    static Yes convert(U);
    static No convert(...);
    static T self();

public:
    using type = typename IsSame<decltype(convert(self())), Yes>::type;
};

TM_NS_END

// help macro
#define __is_convertible__(...) typename TM_NS::IsConvertible<__VA_ARGS__>::type
#define __is_both_convertible__(T, U) __and__(__is_convertible__(T, U), __is_convertible__(U, T))

#endif /*THOR_META_TRAITS_IS_CONVERTIBLE_H_*/