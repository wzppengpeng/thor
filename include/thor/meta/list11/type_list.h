#ifndef THOR_META_LIST11_TYPE_LIST_H_
#define THOR_META_LIST11_TYPE_LIST_H_

#include "thor/meta/common.h"

#include "thor/meta/base/int_type.h"

/**
 * the c++11 style type list
 */

TM_NS_BEGIN

template<class... Types>
struct TypeList {};

template<int... Values>
using ValueList = TypeList<IntType<Values>...>;

TM_NS_END

// the help macro
#define __type_list__(...) TM_NS::TypeList<__VA_ARGS__>
#define __value_list__(...) TM_NS::ValueList<__VA_ARGS__>
#define __empty_list__() TM_NS::TypeList<>

#endif /*THOR_META_LIST11_TYPE_LIST_H_*/