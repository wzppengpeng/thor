#ifndef THOR_META_LIST11_ALGORITHM_REPLACE_H_
#define THOR_META_LIST11_ALGORITHM_REPLACE_H_

#include "concat.h"

/**
 * replace type a to b
 */

TM_NS_BEGIN

// replace the first A to B
// ////////////////////////
template<typename TL, typename A, typename B> struct ListReplaceFirst;

template<class First, class... Types, typename A, typename B>
struct ListReplaceFirst<TypeList<First, Types...>, A, B> {
    using type = typename ListConcat
        <
            TypeList<First>,
            typename ListReplaceFirst<TypeList<Types...>, A, B>::type
        >::type;
};

template<class... Types, typename A, typename B>
struct ListReplaceFirst<TypeList<A, Types...>, A, B> {
    using type = TypeList<B, Types...>;
};

template<typename A, typename B>
struct ListReplaceFirst<TypeList<>, A, B> {
    using type = TypeList<>;
};


// replace all A to B
// ////////////////////////
template<typename TL, typename A, typename B> struct ListReplaceAll;

template<class First, class... Types, typename A, typename B>
struct ListReplaceAll<TypeList<First, Types...>, A, B> {
    using type = typename ListConcat
        <
            TypeList<First>,
            typename ListReplaceAll<TypeList<Types...>, A, B>::type
        >::type;
};

template<class... Types, typename A, typename B>
struct ListReplaceAll<TypeList<A, Types...>, A, B> {
    using type = typename ListConcat
        <
            TypeList<B>,
            typename ListReplaceAll<TypeList<Types...>, A, B>::type
        >::type;
};

template<typename A, typename B>
struct ListReplaceAll<TypeList<>, A, B> {
    using type = TypeList<>;
};

TM_NS_END

// help macro functions
#define __tl_replace__(...) typename TM_NS::ListReplaceFirst<__VA_ARGS__>::type
#define __tl_replace_all__(...) typename TM_NS::ListReplaceAll<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_REPLACE_H_*/