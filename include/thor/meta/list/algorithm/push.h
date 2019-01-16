#ifndef THOR_META_LIST_ALGORITHM_PUSH_H_
#define THOR_META_LIST_ALGORITHM_PUSH_H_

#include "thor/meta/list/type_list.h"

/**
 * push_back a type to a list
 * push_front a type to a list
 */

TM_NS_BEGIN

// push back operation
// //////////////////////////
template<typename TL, typename A> struct ListPushBack;

template<>
struct ListPushBack<NullType, NullType> {
    using type = NullType;
};

template<typename A>
struct ListPushBack<NullType, A> {
    using type = TypeElem<A, NullType>;
};

template<typename Head, typename Tail, typename A>
struct ListPushBack<TypeElem<Head, Tail>, A> {
    using type = TypeElem<Head, typename ListPushBack<Tail, A>::type>;
};

// push front operation
// //////////////////////////
template<typename TL, typename A> struct ListPushFront;

template<>
struct ListPushFront<NullType, NullType> {
    using type = NullType;
};

template<typename A>
struct ListPushFront<NullType, A> {
    using type = TypeElem<A, NullType>;
};

template<typename Head, typename Tail, typename A>
struct ListPushFront<TypeElem<Head, Tail>, A> {
    using type = TypeElem<A, TypeElem<Head, Tail>>;
};

TM_NS_END

// meta macro help function
#define __tl_push_back__(...) typename TM_NS::ListPushBack<__VA_ARGS__>::type
#define __tl_push_front__(...) typename TM_NS::ListPushFront<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_PUSH_H_*/