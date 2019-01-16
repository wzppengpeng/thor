#ifndef THOR_META_BASE_META_FUNCTION_H_
#define THOR_META_BASE_META_FUNCTION_H_

#include "utils.h"

/**
 * This file defines some function tools
 * the input is the meta functions (templates)
 * output is also functions after handling
 */

TM_NS_BEGIN

// get the negative of meta functions, receive any input params
template<template<typename T> class Fun>
struct NegativeOf {
    template<typename U>
    struct Call {
        using type = typename Not<typename Fun<U>::type>::type;
    };

};

// pack the pair parameters into a Pair data structure
// function of input is two params
template<template<typename A, typename B> class TwoInputFun>
struct PackPair {
    template<typename P>
    struct Call {
        using type = typename TwoInputFun<typename P::Left, typename P::Right>::type;
    };
};

// unpack the pair parameters of meta functions
// function of input is handle a pair param
template<template<typename P> class PairFun>
struct UnpackPair {
    template<typename A, typename B>
    struct Call {
        using type = typename PairFun<Pair<A, B>>::type;
    };
};

// transform the bool_type return function to select one input
// if true, select first, else select second
template<template<typename A, typename B> class BoolCompare>
struct CompareToType {
    template<typename L, typename R>
    struct Call {
        using type = typename IfThenElse<
                     typename BoolCompare<L, R>::type,
                     L,
                     R>
                     ::type;
    };
};

TM_NS_END

// help funtions for meta funtions
#define __negative_of__(...) TM_NS::NegativeOf<__VA_ARGS__>::template Call
#define __pack_pair__(...) TM_NS::PackPair<__VA_ARGS__>::template Call
#define __unpack_pair__(...) TM_NS::UnpackPair<__VA_ARGS__>::template Call
#define __compare_to_type__(...) TM_NS::CompareToType<__VA_ARGS__>::template Call

#endif /*THOR_META_BASE_META_FUNCTION_H_*/