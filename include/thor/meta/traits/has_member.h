#ifndef THOR_META_TRAITS_HAS_MEMBER_H_
#define THOR_META_TRAITS_HAS_MEMBER_H_

#include "thor/meta/base/bool_type.h"
#include "thor/meta/base/void_t.h"

/**
 * some macro to define check if a class has member x
 * or has member function y
 */

// the macro the to define a meta function to check if has member type in class T
#define HAS_MEMBER(FOO) template<typename T, class = TM_NS::void_t<>> \
                struct HasMember##FOO : TM_NS::FalseType {}; \
                                                         \
                template<typename T>                   \
                struct HasMember##FOO<T, TM_NS::void_t<decltype(std::declval<T>().FOO)>> \
                : TM_NS::TrueType {};

// the called meta function to check if class A has member, used after HAS_MEMBER defined
#define __check_has_member__(T, FOO) typename HasMember##FOO<T>::type

// the macro to define a meta function to check if has member function in class T
#define HAS_MEMBER_FUNCTION(FOO) template<typename T, class = TM_NS::void_t<>> \
                         struct HasMemberFunction##FOO : TM_NS::FalseType {}; \
                                                                               \
                         template<typename T> \
                         struct HasMemberFunction##FOO<T, TM_NS::void_t<decltype(&T::FOO)>> \
                         : TM_NS::BoolType<std::is_member_function_pointer<decltype(&T::FOO)>::value> \
                         {};

// the called meta function to check if class A has member function, used after HAS_MEMBER_FUNCTION defined
#define __check_has_member_function__(T, FOO) typename HasMemberFunction##FOO<T>::type

#endif /*THOR_META_TRAITS_HAS_MEMBER_H_*/