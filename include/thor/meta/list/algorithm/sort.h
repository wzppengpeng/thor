#ifndef THOR_META_LIST_ALGORITHM_SORT_H_
#define THOR_META_LIST_ALGORITHM_SORT_H_

#include "reduce.h"
#include "replace.h"

#include "thor/meta/base/meta_function.h"

/**
 * sort the type list by a bool type compare function
 * use insert sort~
 */
TM_NS_BEGIN

template<typename TL, template<typename T, typename U> class Comp = LT> struct ListSort;

template<template<typename T, typename U> class Comp>
struct ListSort<NullType, Comp> {
    using type = NullType;
};

template<typename Head, typename Tail, template<typename T, typename U> class Comp>
struct ListSort<TypeElem<Head, Tail>, Comp> {
private:
    using Target = typename ListReduce<
                   TypeElem<Head, Tail>,
                   Head,
                   CompareToType<Comp>::template Call
                   >::type;
    using ListAfterReplace = typename ListReplaceFirst<Tail, Target, Head>::type;

public:
    using type = TypeElem<Target, typename ListSort<ListAfterReplace, Comp>::type>;

};

TM_NS_END

// help macro
#define __tl_sort__(...) typename TM_NS::ListSort<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_SORT_H_*/