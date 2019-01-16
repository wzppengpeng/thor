#ifndef THOR_META_LIST11_ALGORITHM_IS_INCLUDED_H_
#define THOR_META_LIST11_ALGORITHM_IS_INCLUDED_H_

#include "index_of.h"

/**
 * check if type A is included in type list
 */

TM_NS_BEGIN

template<typename TL, typename A> struct ListIsIncluded;

template<class... Types, typename A>
struct ListIsIncluded<TypeList<Types...>, A> {
    using type = typename IsValid
        <
            typename ListIndexOf<TypeList<Types...>, A>::type
        >::type;
};

TM_NS_END

#define __tl_is_included__(...) typename TM_NS::ListIsIncluded<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_IS_INCLUDED_H_*/