#ifndef THOR_META_LIST11_ALGORITHM_POP_H_
#define THOR_META_LIST11_ALGORITHM_POP_H_

#include "concat.h"

/**
 * pop back and pop front of type list
 */

TM_NS_BEGIN

// pop back operation
// //////////////////
template<typename TL> struct ListPopBack;

template<class First, class... Types>
struct ListPopBack<TypeList<First, Types...>> {
    using type = typename ListConcat<TypeList<First>,
        typename ListPopBack<TypeList<Types...>>::type>::type;
};

template<class Last>
struct ListPopBack<TypeList<Last>> {
    using type = TypeList<>;
};

template<>
struct ListPopBack<TypeList<>> {
    using type = TypeList<>;
};

// pop front operation
// ///////////////////
template<typename TL> struct ListPopFront;

template<class First, class... Types>
struct ListPopFront<TypeList<First, Types...>> {
    using type = TypeList<Types...>;
};

template<>
struct ListPopFront<TypeList<>> {
    using type = TypeList<>;
};

TM_NS_END

// help function
#define __tl_pop_back(...) typename TM_NS::ListPopBack<__VA_ARGS__>::type
#define __tl_pop_front(...) typename TM_NS::ListPopFront<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_POP_H_*/