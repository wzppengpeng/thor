#ifndef THOR_META_LIST11_ALGORITHM_FILTER_H_
#define THOR_META_LIST11_ALGORITHM_FILTER_H_

#include "push.h"

#include "thor/meta/base/utils.h"

/**
 * filter not ok types in TYpeList
 * input a TL and a MetaFunc, filter when return True
 */

TM_NS_BEGIN

template<typename TL, template<typename> class BoolMetaFunc> struct ListFilter;

template<template<typename> class BoolMetaFunc>
struct ListFilter<TypeList<>, BoolMetaFunc> {
    using type = TypeList<>;
};

template<class First, class... Types, template<typename> class BoolMetaFunc>
struct ListFilter<TypeList<First, Types...>, BoolMetaFunc> {
    using type = typename IfThenElse
        <
            typename BoolMetaFunc<First>::type,
            typename ListPushFront<typename ListFilter<TypeList<Types...>, BoolMetaFunc>::type, First>::type,
            typename ListFilter<TypeList<Types...>, BoolMetaFunc>::type
        >::type;
};

TM_NS_END

// help macro
#define __tl_filter__(...) typename TM_NS::ListFilter<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_FILTER_H_*/