#ifndef THOR_META_TRAITS_IS_BUILT_IN_H_
#define THOR_META_TRAITS_IS_BUILT_IN_H_

#include "thor/meta/list/algorithm/is_included.h"

/**
 * a traits function for type
 * to judge if this type is built in type
 * reference will be decayed
 */

TM_NS_BEGIN

template<typename T>
struct IsBuiltIn {
private:
    using BuiltInTypes
        = typename TypeList<char, wchar_t, char16_t, char32_t, bool, short,
        int, long, long long, float, double, long double>::type;

public:
    using type = typename ListIsIncluded<BuiltInTypes,
                 typename std::decay<T>::type
                 >::type;

};

TM_NS_END

// help function
#define __is_built_in__(...) typename TM_NS::IsBuiltIn<__VA_ARGS__>::type

#endif /*THOR_META_TRAITS_IS_BUILT_IN_H_*/