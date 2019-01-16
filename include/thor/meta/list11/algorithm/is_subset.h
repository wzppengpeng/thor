#ifndef THOR_META_LIST11_ALGORITHM_IS_SUBSET_H_
#define THOR_META_LIST11_ALGORITHM_IS_SUBSET_H_

#include "is_included.h"

/**
 * input two list, check if the first list is the second sub-set
 * check there are same types for first one in second one
 * return bool_type
 */

TM_NS_BEGIN

template<typename TLA, typename TLB> struct ListIsSubset;

// some empty list cases
template<class... BTypes>
struct ListIsSubset<TypeList<>, TypeList<BTypes...>> {
    using type = TrueType;
};

template<class AFirst, class... ATypes>
struct ListIsSubset<TypeList<AFirst, ATypes...>, TypeList<>> {
    using type = FalseType;
};

template<class AFirst, class... ATypes, class... BTypes>
struct ListIsSubset<TypeList<AFirst, ATypes...>, TypeList<BTypes...>> {
    using type = typename And
        <
            typename ListIsIncluded<TypeList<BTypes...>, AFirst>::type,
            typename ListIsSubset<TypeList<ATypes...>, TypeList<BTypes...>>::type
        >::type;
};

TM_NS_END

// help macro function
#define __tl_is_subset__(...) typename TM_NS::ListIsSubset<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_IS_SUBSET_H_*/