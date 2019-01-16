#ifndef THOR_META_LIST11_ALGORITHM_UNIQUE_H_
#define THOR_META_LIST11_ALGORITHM_UNIQUE_H_

#include "is_included.h"

#include "concat.h"

/**
 * erase the duplicated types in list
 */

TM_NS_BEGIN

template<typename TL> struct ListUnique;

template<class First, class... Types>
struct ListUnique<TypeList<First, Types...>> {
    using type = typename IfThenElse
        <
            typename ListIsIncluded<TypeList<Types...>, First>::type,
            typename ListUnique<TypeList<Types...>>::type,
            typename ListConcat<TypeList<First>, typename ListUnique<TypeList<Types...>>::type>::type
        >::type;
};

template<>
struct ListUnique<TypeList<>> {
    using type = TypeList<>;
};

TM_NS_END

// help macro functions
#define __tl_unique__(...) typename TM_NS::ListUnique<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_UNIQUE_H_*/