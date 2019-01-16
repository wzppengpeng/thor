#ifndef THOR_META_LIST_ALGORITHM_IS_INCLUDED_H_
#define THOR_META_LIST_ALGORITHM_IS_INCLUDED_H_

#include "index_of.h"

/**
 * check a type if is in the Type List
 * return BoolType
 */

TM_NS_BEGIN

template<typename TL, typename A> struct ListIsIncluded;

template<typename Head, typename Tail, typename A>
struct ListIsIncluded<TypeElem<Head, Tail>, A> {
    using type = typename IsValid<
                 typename ListIndexOf<TypeElem<Head, Tail>, A>::type
                 >::type;
};

template<typename A>
struct ListIsIncluded<NullType, A> {
    using type = FalseType;
};

TM_NS_END

// meta help function
#define __tl_is_included__(...) typename TM_NS::ListIsIncluded<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_IS_INCLUDED_H_*/