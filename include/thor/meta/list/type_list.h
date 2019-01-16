#ifndef THOR_META_LIST_TYPE_LIST_H_
#define THOR_META_LIST_TYPE_LIST_H_

#include "type_element.h"

#include "thor/meta/base/null_type.h"
#include "thor/meta/base/int_type.h"

/**
 * This file defines the structure of type list
 * use template function loop to get the type list more simple
 */

TM_NS_BEGIN

// define the type of empty list
using EmptyList = NullType;

// the meta function to get the type list
template<typename Head, typename... Tails>
struct TypeList {
    using type = TypeElem<Head, typename TypeList<Tails...>::type>;
};

template<typename Head>
struct TypeList<Head> {
    using type = TypeElem<Head, NullType>;
};

// the help function of value list to get the IntType list
template<int h, int... t>
struct ValueList {
    using type = TypeElem<IntType<h>, typename ValueList<t...>::type>;
};

template<int h>
struct ValueList<h> {
    using type = TypeElem<IntType<h>, NullType>;
};

TM_NS_END

// define the meta functions macro
#define __type_list__(...) typename TM_NS::TypeList<__VA_ARGS__>::type
#define __empty_list__() TM_NS::EmptyList
#define __value_list__(...) typename TM_NS::ValueList<__VA_ARGS__>::type

#endif /*THOR_META_LIST_TYPE_LIST_H_*/