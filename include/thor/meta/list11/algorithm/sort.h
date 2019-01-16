#ifndef THOR_META_LIST11_ALGORITHM_SORT_H_
#define THOR_META_LIST11_ALGORITHM_SORT_H_

#include "reduce.h"
#include "replace.h"
#include "push.h"

#include "thor/meta/base/meta_function.h"

/**
 * sort the type list by a bool type compare function
 * use insert sort~
 */

TM_NS_BEGIN

template<typename TL, template<typename T, typename U> class Comp = LT> struct ListSort;

template<template<typename T, typename U> class Comp>
struct ListSort<TypeList<>, Comp> {
    using type = TypeList<>;
};

template<class First, class... Types, template<typename T, typename U> class Comp>
struct ListSort<TypeList<First, Types...>, Comp> {

private:
    using Target = typename ListReduce<
                   TypeList<First, Types...>,
                   First,
                   CompareToType<Comp>::template Call
                   >::type;
    using ListAfterReplace = typename ListReplaceFirst<TypeList<Types...>, Target, First>::type;

public:
    using type = typename ListPushFront
        <
            typename ListSort<ListAfterReplace, Comp>::type,
            Target
        >::type;

};

TM_NS_END

// help macro
#define __tl_sort__(...) typename TM_NS::ListSort<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_SORT_H_*/