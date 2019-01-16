#ifndef THOR_META_LIST_ALGORITHM_FILTER_H_
#define THOR_META_LIST_ALGORITHM_FILTER_H_

#include "thor/meta/list/type_list.h"

#include "thor/meta/base/utils.h"

/**
 * filter not ok types in TYpeList
 * input a TL and a MetaFunc, filter when return True
 */

TM_NS_BEGIN

template<typename TL, template<typename> class BoolMetaFunc> struct ListFilter;

template<template<typename> class BoolMetaFunc>
struct ListFilter<NullType, BoolMetaFunc> {
    using type = NullType;
};

template<typename Head, typename Tail, template<typename> class BoolMetaFunc>
struct ListFilter<TypeElem<Head, Tail>, BoolMetaFunc> {
    using type = typename IfThenElse<typename BoolMetaFunc<Head>::type,
                            TypeElem<Head, typename ListFilter<Tail, BoolMetaFunc>::type>,
                            typename ListFilter<Tail, BoolMetaFunc>::type
                            >::type;
};

TM_NS_END

// help macro
#define __tl_filter__(...) typename TM_NS::ListFilter<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_FILTER_H_*/