#ifndef THOR_META_LIST11_ALGORITHM_ERASE_H_
#define THOR_META_LIST11_ALGORITHM_ERASE_H_

#include "concat.h"

/**
 * erase the type A in type list if matched
 */

TM_NS_BEGIN

// erase the first type of A in TypeList
// /////////////////////////////////////
template<typename TL, typename A> struct ListEraseFirst;

template<class First, class... Types, typename A>
struct ListEraseFirst<TypeList<First, Types...>, A> {
    using type = typename ListConcat<TypeList<First>,
        typename ListEraseFirst<TypeList<Types...>, A>::type>::type;
};

template<class... Types, typename A>
struct ListEraseFirst<TypeList<A, Types...>, A> {
    using type = TypeList<Types...>;
};

template<typename A>
struct ListEraseFirst<TypeList<>, A> {
    using type = TypeList<>;
};

// erase all the type of A in TypeList
// /////////////////////////////////////
template<typename TL, typename A> struct ListEraseAll;

template<class First, class... Types, typename A>
struct ListEraseAll<TypeList<First, Types...>, A> {
    using type = typename ListConcat
        <
            TypeList<First>,
            typename ListEraseAll<TypeList<Types...>, A>::type
        >::type;
};

template<class... Types, typename A>
struct ListEraseAll<TypeList<A, Types...>, A> {
    using type = typename ListEraseAll<TypeList<Types...>, A>::type;
};

template<typename A>
struct ListEraseAll<TypeList<>, A> {
    using type = TypeList<>;
};

TM_NS_END

// help macro functions
#define __tl_erase__(...) typename TM_NS::ListEraseFirst<__VA_ARGS__>::type
#define __tl_erase_all__(...) typename TM_NS::ListEraseAll<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_ERASE_H_*/