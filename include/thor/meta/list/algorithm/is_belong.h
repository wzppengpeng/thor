#ifndef THOR_META_LIST_ALGORITHM_IS_BELONG_H_
#define THOR_META_LIST_ALGORITHM_IS_BELONG_H_

#include "is_subset.h"

/**
 * input a list A and a list of (list) Sets
 * return if A is subset in Sets
 */

TM_NS_BEGIN

template<typename TL, typename TL_SETS> struct ListIsBelong;

template<typename TL_SETS_Head, typename TL_SETS_Tail>
struct ListIsBelong<NullType, TypeElem<TL_SETS_Head, TL_SETS_Tail>> {
    using type = TrueType;
};

template<>
struct ListIsBelong<NullType, NullType> {
    using type = TrueType;
};

template<typename TL>
struct ListIsBelong<TL, NullType> {
    using type = FalseType;
};

template<typename TL, typename TL_SETS_Head, typename TL_SETS_Tail>
struct ListIsBelong<TL, TypeElem<TL_SETS_Head, TL_SETS_Tail>> {
    using type = typename Or<
                 typename ListIsSubset<TL, TL_SETS_Head>::type,
                 typename ListIsBelong<TL, TL_SETS_Tail>::type
                 >::type;
};

TM_NS_END

// help macro functions
#define __tl_is_belong__(...) typename TM_NS::ListIsBelong<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_IS_BELONG_H_*/