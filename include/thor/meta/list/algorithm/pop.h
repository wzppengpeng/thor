#ifndef THOR_META_LIST_ALGORITHM_POP_H
#define THOR_META_LIST_ALGORITHM_POP_H

#include "thor/meta/list/type_list.h"

/**
 * pop_back a type from the type list
 * pop_front a type from the type list
 */

TM_NS_BEGIN

// pop back operation
// //////////////////
template<typename TL> struct ListPopBack;

template<typename Head, typename Tail>
struct ListPopBack<TypeElem<Head, Tail>> {
    using type = TypeElem<Head, typename ListPopBack<Tail>::type>;
};

template<typename Head>
struct ListPopBack<TypeElem<Head, NullType>> {
    using type = NullType;
};

template<>
struct ListPopBack<NullType> {
    using type = NullType;
};

// pop front operation
// ///////////////////
template<typename TL> struct ListPopFront;

template<typename Head, typename Tail>
struct ListPopFront<TypeElem<Head, Tail>> {
    using type = Tail;
};

template<>
struct ListPopFront<NullType> {
    using type = NullType;
};

TM_NS_END

// help function
#define __tl_pop_back(...) typename TM_NS::ListPopBack<__VA_ARGS__>::type
#define __tl_pop_front(...) typename TM_NS::ListPopFront<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_POP_H*/