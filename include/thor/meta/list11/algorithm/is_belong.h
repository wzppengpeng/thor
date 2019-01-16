#ifndef THOR_META_LIST11_ALGORITHM_IS_BELONG_H_
#define THOR_META_LIST11_ALGORITHM_IS_BELONG_H_

#include "is_subset.h"

/**
 * input a list A and a list of (list) Sets
 * return if A is subset in Sets
 */

TM_NS_BEGIN

template<typename TL, typename TL_SETS> struct ListIsBelong;

template<class SetsListsFirst, class... SetsLists>
struct ListIsBelong<TypeList<>, TypeList<SetsListsFirst, SetsLists...>> {
    using type = TrueType;
};

template<>
struct ListIsBelong<TypeList<>, TypeList<>> {
    using type = TrueType;
};

template<typename TL>
struct ListIsBelong<TL, TypeList<>> {
    using type = FalseType;
};

template<typename TL, class SetsListsFirst, class... SetsLists>
struct ListIsBelong<TL, TypeList<SetsListsFirst, SetsLists...>> {
    using type = typename Or
        <
            typename ListIsSubset<TL, SetsListsFirst>::type,
            typename ListIsBelong<TL, TypeList<SetsLists...>>::type
        >::type;
};

TM_NS_END

// help macro functions
#define __tl_is_belong__(...) typename TM_NS::ListIsBelong<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_IS_BELONG_H_*/