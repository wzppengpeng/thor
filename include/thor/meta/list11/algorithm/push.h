#ifndef THOR_META_LIST11_ALGORITHM_PUSH_H_
#define THOR_META_LIST11_ALGORITHM_PUSH_H_

#include "thor/meta/list11/type_list.h"

/**
 * push_back a type to a list
 * push_front a type to a list
 */

TM_NS_BEGIN

// push back operation
// //////////////////////////
template<typename TL, typename A> struct ListPushBack;

template<class... Types, typename A>
struct ListPushBack<TypeList<Types...>, A> {
    using type = TypeList<Types..., A>;
};

// push front operation
// //////////////////////////
template<typename TL, typename A> struct ListPushFront;

template<class... Types, typename A>
struct ListPushFront<TypeList<Types...>, A> {
    using type = TypeList<A, Types...>;
};

TM_NS_END

// the help macro
#define __tl_push_back__(...) typename TM_NS::ListPushBack<__VA_ARGS__>::type
#define __tl_push_front__(...) typename TM_NS::ListPushFront<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_PUSH_H_*/