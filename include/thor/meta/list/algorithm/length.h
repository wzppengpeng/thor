#ifndef THOR_META_LIST_ALGORITHM_LENGTH_H_
#define THOR_META_LIST_ALGORITHM_LENGTH_H_

#include "thor/meta/list/type_list.h"


/**
 * compute the length of a Type list by recursive
 */
TM_NS_BEGIN

template<typename TL> struct ListLength;

template<typename Head, typename Tail>
struct ListLength<TypeElem<Head, Tail>> {
    using type = typename Inc<typename ListLength<Tail>::type>::type;
};

template<>
struct ListLength<NullType> {
    using type = IntType<0>;
};

TM_NS_END

// meta function to get list length
#define __tl_length__(...) typename TM_NS::ListLength<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_LENGTH_H_*/