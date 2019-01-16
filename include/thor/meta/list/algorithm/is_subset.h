#ifndef THOR_META_LIST_ALGORITHM_IS_SUBSET_H_
#define THOR_META_LIST_ALGORITHM_IS_SUBSET_H_

#include "is_included.h"

/**
 * input two list, check if the first list is the second sub-set
 * check there are same types for first one in second one
 * return bool_type
 */

TM_NS_BEGIN

template<typename TLA, typename TLB> struct ListIsSubset;

template<typename BH, typename BT>
struct ListIsSubset<NullType, TypeElem<BH, BT>> {
    using type = TrueType;
};

template<>
struct ListIsSubset<NullType, NullType> {
    using type = TrueType;
};

template<typename AH, typename AT>
struct ListIsSubset<TypeElem<AH, AT>, NullType> {
    using type = FalseType;
};

template<typename AH, typename AT, typename BH, typename BT>
struct ListIsSubset<TypeElem<AH, AT>, TypeElem<BH, BT>> {
    using type = typename And<
                 typename ListIsIncluded<TypeElem<BH, BT>, AH>::type,
                 typename ListIsSubset<AT, TypeElem<BH, BT>>::type
                 >::type;
};

TM_NS_END

// help macro function
#define __tl_is_subset__(...) typename TM_NS::ListIsSubset<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_IS_SUBSET_H_*/