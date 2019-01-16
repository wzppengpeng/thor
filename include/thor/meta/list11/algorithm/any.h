#ifndef THOR_META_LIST11_ALGORITHM_ANY_H_
#define THOR_META_LIST11_ALGORITHM_ANY_H_

#include "thor/meta/list11/type_list.h"

#include "thor/meta/base/utils.h"

/**
 * Check if there is some type in TypeList which match the bool meta function
 */

TM_NS_BEGIN

template<typename TL, template<typename> class BoolMetaFun> struct ListAny;

template<template<typename> class BoolMetaFun>
struct ListAny<TypeList<>, BoolMetaFun> {
    using type = FalseType;
};

template<class First, class... Types, template<typename> class BoolMetaFun>
struct ListAny<TypeList<First, Types...>, BoolMetaFun> {
    using type = typename IfThenElse
        <
            typename BoolMetaFun<First>::type,
            TrueType,
            typename ListAny<TypeList<Types...>, BoolMetaFun>::type
        >::type;
};

TM_NS_END

// help macro function
#define __tl_any__(...) typename TM_NS::ListAny<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_ANY_H_*/