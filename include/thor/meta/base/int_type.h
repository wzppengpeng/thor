#ifndef THOR_META_BASE_INT_TYPE_H_
#define THOR_META_BASE_INT_TYPE_H_

#include <type_traits>

#include "thor/meta/common.h"

#include "bool_type.h"

TM_NS_BEGIN

/**
 * The Int Type and its operation functions
 */
// the int type
template<int val>
using IntType = std::integral_constant<int, val>;

// increase the value in int type
template<typename T> struct Inc;

template<int val>
struct Inc<IntType<val>> : IntType<val + 1> {};

// decrease value in int type
template<typename T> struct Dec;

template<int val>
struct Dec<IntType<val>> : IntType<val - 1> {};

// add two value in int type
template<typename A, typename B> struct Add;

template<int a, int b>
struct Add<IntType<a>, IntType<b>> : IntType<a + b> {};

// sub two value
template<typename A, typename B> struct Sub;

template<int a, int b>
struct Sub<IntType<a>, IntType<b>> : IntType<a - b> {};

// mul two value
template<typename A, typename B> struct Mul;

template<int a, int b>
struct Mul<IntType<a>, IntType<b>> : IntType<a * b> {};

// div two value
template<typename A, typename B> struct Div;

template<int a, int b>
struct Div<IntType<a>, IntType<b>> : IntType<a / b> {};

// mod two value
template<typename A, typename B> struct Mod;

template<int a, int b>
struct Mod<IntType<a>, IntType<b>> : IntType<a % b> {};

// get the max value
template<typename A, typename B> struct Max;

template<int a, int b>
struct Max<IntType<a>, IntType<b>> : IntType<((a > b) ? a : b)> {};

// get the min value
template<typename A, typename B> struct Min;

template<int a, int b>
struct Min<IntType<a>, IntType<b>> : IntType<((a < b) ? a : b)> {};

// sum a list of ints
template<typename... Nums> struct Sum;

template<typename I, typename... Nums>
struct Sum<I, Nums...> : Add<I, typename Sum<Nums...>::type> {};

template<> struct Sum<> : IntType<0> {};

// check two numbers lt or gt
template<typename A, typename B> struct LT;

template<int a, int b>
struct LT<IntType<a>, IntType<b>> : BoolType<(a < b)> {};

template<typename A, typename B> struct GT;

template<int a, int b>
struct GT<IntType<a>, IntType<b>> : BoolType<(a > b)> {};

TM_NS_END

// the function of int and int operations
#define __int__(...)    typename TM_NS::IntType<__VA_ARGS__>::type

#define __inc__(...)    typename     TM_NS::Inc<__VA_ARGS__>::type
#define __dec__(...)    typename     TM_NS::Dec<__VA_ARGS__>::type
#define __add__(...)    typename     TM_NS::Add<__VA_ARGS__>::type
#define __sub__(...)    typename     TM_NS::Sub<__VA_ARGS__>::type
#define __mul__(...)    typename     TM_NS::Mul<__VA_ARGS__>::type
#define __div__(...)    typename     TM_NS::Div<__VA_ARGS__>::type
#define __mod__(...)    typename     TM_NS::Mod<__VA_ARGS__>::type
#define __sum__(...)    typename     TM_NS::Sum<__VA_ARGS__>::type
#define __lt__(...)     typename      TM_NS::LT<__VA_ARGS__>::type
#define __gt__(...)     typename      TM_NS::GT<__VA_ARGS__>::type
#define __max__(...)    typename     TM_NS::Max<__VA_ARGS__>::type
#define __min__(...)    typename     TM_NS::Min<__VA_ARGS__>::type

#endif /*THOR_META_BASE_INT_TYPE_H_*/