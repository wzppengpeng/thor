#ifndef THOR_META_BASE_BOOL_TYPE_H_
#define THOR_META_BASE_BOOL_TYPE_H_

#include <type_traits>

#include "thor/meta/common.h"

TM_NS_BEGIN

/**
 * the bool type, has type and value in it, type is BoolType, value_type is bool, value is true or false
 */
template<bool val>
using BoolType = std::integral_constant<bool, val>;

// true type and false type
using TrueType = BoolType<true>;
using FalseType = BoolType<false>;

// the bool operations
// and (&&) for two bool type
template<typename A, typename B> struct And;
// only receive the BoolType
template<bool a, bool b>
struct And<BoolType<a>, BoolType<b>> : BoolType<(a && b)> {};

// or (||) for two bool type
template<typename A, typename B> struct Or;
// only receive the BoolType
template<bool a, bool b>
struct Or<BoolType<a>, BoolType<b>> : BoolType<(a || b)> {};

// not (!) for one bool type
template<typename T> struct Not;

template<bool val>
struct Not<BoolType<val>> : BoolType<!val> {};

TM_NS_END

// the meta function define of bool types
#define __bool__(...) typename TM_NS::BoolType<__VA_ARGS__>::type
#define __true__() typename TM_NS::TrueType::type
#define __false__() typename TM_NS::FalseType::type

// the meta function of bool operations
#define __and__(...) typename TM_NS::And<__VA_ARGS__>::type
#define __or__(...) typename TM_NS::Or<__VA_ARGS__>::type
#define __not__(...) typename TM_NS::Not<__VA_ARGS__>::type

#endif /*THOR_META_BASE_BOOL_TYPE_H_*/