#ifndef THOR_META_LIST_ALGORITHM_ANY_H_
#define THOR_META_LIST_ALGORITHM_ANY_H_

#include "thor/meta/list/type_list.h"

#include "thor/meta/base/utils.h"

/**
 * Check if there is some type in TypeList which match the bool meta function
 */

TM_NS_BEGIN

template<typename TL, template<typename> class BoolMetaFun> struct ListAny;

template<template<typename> class BoolMetaFun>
struct ListAny<NullType, BoolMetaFun> {
    using type = FalseType;
};

template<typename Head, typename Tail, template<typename> class BoolMetaFun>
struct ListAny<TypeElem<Head, Tail>, BoolMetaFun> {
    using type = typename IfThenElse<
                 typename BoolMetaFun<Head>::type,
                 TrueType,
                 typename ListAny<Tail, BoolMetaFun>::type
                 >::type;
};

TM_NS_END

// help macro function
#define __tl_any__(...) typename TM_NS::ListAny<__VA_ARGS__>::type


#endif /*THOR_META_LIST_ALGORITHM_ANY_H_*/