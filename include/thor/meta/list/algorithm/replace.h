#ifndef THOR_META_LIST_ALGORITHM_REPLACE_H_
#define THOR_META_LIST_ALGORITHM_REPLACE_H_

#include "thor/meta/list/type_list.h"

/**
 * replace the type A to be type B in TypeList
 */
TM_NS_BEGIN

// replace the first A to B
// ////////////////////////
template<typename TL, typename A, typename B> struct ListReplaceFirst;

template<typename Head, typename Tail, typename A, typename B>
struct ListReplaceFirst<TypeElem<Head, Tail>, A, B> {
    using type = TypeElem<Head, typename ListReplaceFirst<Tail, A, B>::type>;
};

template<typename Head, typename Tail, typename B>
struct ListReplaceFirst<TypeElem<Head, Tail>, Head, B> {
    using type = TypeElem<B, Tail>;
};

template<typename A, typename B>
struct ListReplaceFirst<NullType, A, B> {
    using type = NullType;
};

// replace all A to B
// ////////////////////////
template<typename TL, typename A, typename B> struct ListReplaceAll;

template<typename Head, typename Tail, typename A, typename B>
struct ListReplaceAll<TypeElem<Head, Tail>, A, B> {
    using type = TypeElem<Head, typename ListReplaceAll<Tail, A, B>::type>;
};

template<typename Head, typename Tail, typename B>
struct ListReplaceAll<TypeElem<Head, Tail>, Head, B> {
    using type = TypeElem<B, typename ListReplaceAll<Tail, Head, B>::type>;
};

template<typename A, typename B>
struct ListReplaceAll<NullType, A, B> {
    using type = NullType;
};

TM_NS_END

// help macro functions
#define __tl_replace__(...) typename TM_NS::ListReplaceFirst<__VA_ARGS__>::type
#define __tl_replace_all__(...) typename TM_NS::ListReplaceAll<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_REPLACE_H_*/