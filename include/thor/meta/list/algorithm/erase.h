#ifndef THOR_META_LIST_ALGORITHM_ERASE_H_
#define THOR_META_LIST_ALGORITHM_ERASE_H_

#include "thor/meta/list/type_list.h"

/**
 * erase the type A in type list if matched
 */
TM_NS_BEGIN

// erase the first type of A in TypeList
// /////////////////////////////////////
template<typename TL, typename A> struct ListEraseFirst;

template<typename Head, typename Tail, typename A>
struct ListEraseFirst<TypeElem<Head, Tail>, A> {
    using type = TypeElem<Head, typename ListEraseFirst<Tail, A>::type>;
};

template<typename Head, typename Tail>
struct ListEraseFirst<TypeElem<Head, Tail>, Head> {
    using type = Tail;
};

template<typename A>
struct ListEraseFirst<NullType, A> {
    using type = NullType;
};

// erase all the type of A in TypeList
// /////////////////////////////////////
template<typename TL, typename A> struct ListEraseAll;

template<typename Head, typename Tail, typename A>
struct ListEraseAll<TypeElem<Head, Tail>, A> {
    using type = TypeElem<Head, typename ListEraseAll<Tail, A>::type>;
};

template<typename Head, typename Tail>
struct ListEraseAll<TypeElem<Head, Tail>, Head> {
    using type = typename ListEraseAll<Tail, Head>::type;
};

template<typename A>
struct ListEraseAll<NullType, A> {
    using type = NullType;
};

TM_NS_END

// help macro functions
#define __tl_erase__(...) typename TM_NS::ListEraseFirst<__VA_ARGS__>::type
#define __tl_erase_all__(...) typename TM_NS::ListEraseAll<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_ERASE_H_*/