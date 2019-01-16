#ifndef THOR_META_TRAITS_FUNCTION_TRAITS_H_
#define THOR_META_TRAITS_FUNCTION_TRAITS_H_

#include <tuple>

#include "thor/meta/common.h"
#include "thor/meta/list/type_list.h"

/**
 * defined function triaits
 * input a function type (lambda, function pointer, function object)
 * return the types of params and return value
 */

TM_NS_BEGIN

// the basic type of function object
template<typename F>
struct FunctionTraits : FunctionTraits<decltype(&F::operator())> {};

// function pointer
template<typename R, typename... Args>
struct FunctionTraits<R(*)(Args...)> : FunctionTraits<R(Args...)> {};

template<typename R, typename... Args>
struct FunctionTraits<R(Args...)> {
    using return_type = R;
    constexpr static int arity = sizeof...(Args);
    // get the param type
    template<int N>
    struct Arg {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

// member function pointer
template<typename C, typename R, typename... Args>
struct FunctionTraits<R(C::*)(Args...)> : FunctionTraits<R(Args...)> {};

template<typename C, typename R, typename... Args>
struct FunctionTraits<R(C::*)(Args...) const> : FunctionTraits<R(Args...)> {};

// member object pointer
template<typename C, typename R>
struct FunctionTraits<R(C::*)> : FunctionTraits <R()> {};

// reference to function objects
template<typename F>
struct FunctionTraits<F&> : FunctionTraits <F> {};

template<typename F>
struct FunctionTraits<const F&> : FunctionTraits<F> {};

template<typename F>
struct FunctionTraits<F&&> : FunctionTraits <F> {};

TM_NS_END

// help macro
// get the return type
#define __fun_return_type__(...) typename TM_NS::FunctionTraits<__VA_ARGS__>::return_type
// get the functions args number
#define __fun_args_number__(...) TM_NS::FunctionTraits<__VA_ARGS__>::arity
// function input param
#define __fun_args_type__(F, N) typename TM_NS::FunctionTraits<F>::template Arg<N>::type
#endif /*THOR_META_TRAITS_FUNCTION_TRAITS_H_*/