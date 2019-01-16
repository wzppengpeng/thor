#ifndef THOR_META_BASE_UTILS_H_
#define THOR_META_BASE_UTILS_H_

#include "null_type.h"
#include "empty_type.h"
#include "bool_type.h"

TM_NS_BEGIN

// some help types in utility
template<typename L, typename R>
struct Pair {
    using Left = L;
    using Right = R;
};

/**
 * This class is the type help functions for programming
 */
// judge if it is null for a null type
template<typename T>
struct IsNull {
    using type = FalseType;
};

template<>
struct IsNull<NullType> {
    using type = TrueType;
};

// judge if it is valid, just not from IsNull
template<typename T>
struct IsValid {
    using type = TrueType;
};

template<>
struct IsValid<NullType> {
    using type = FalseType;
};

// get the value from type
template<typename T>
struct GetValue {
    using value_type = typename T::value_type;
    constexpr static value_type value = T::value;
};

template<>
struct GetValue<EmptyType> {
    constexpr static int value = 0xFFFFFFFF;
};

template<>
struct GetValue<NullType> {
    constexpr static int value = 0;
};

// check two type if equal
template<typename T, typename U>
struct IsSame : FalseType {};

template<typename T>
struct IsSame<T, T> : TrueType {};

// conditional use type
template<typename Bool, typename T, typename U>
struct IfThenElse : std::conditional<Bool::value, T, U> {};

TM_NS_END

// function of null and valid
#define __is_valid__(...) typename TM_NS::IsValid<__VA_ARGS__>::type
#define __is_null__(...) typename TM_NS::IsNull<__VA_ARGS__>::type
// function to get the value in type
#define __value__(...) TM_NS::GetValue<__VA_ARGS__>::value
// judge if two types are equal
#define __is_same__(...) typename TM_NS::IsSame<__VA_ARGS__>::type
#define __eq__(...) __is_same__(__VA_ARGS__)
// if condictional
#define __if__(...) typename TM_NS::IfThenElse<__VA_ARGS__>::type

#endif /*THOR_META_BASE_UTILS_H_*/