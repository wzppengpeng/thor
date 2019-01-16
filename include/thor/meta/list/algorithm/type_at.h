#ifndef THOR_META_LIST_ALGORITHM_TYPE_AT_H_
#define THOR_META_LIST_ALGORITHM_TYPE_AT_H_

#include "thor/meta/list/type_list.h"

#include "length.h"

/**
 * get the type at index I, can input both IntType and int value
 */

TM_NS_BEGIN

// the declaration of normal types
template<typename TL, int index> struct ListTypeAtByVal;

template<typename Head, typename Tail, int index>
struct ListTypeAtByVal<TypeElem<Head, Tail>, index> {
private:
    constexpr static int real_index
        = std::conditional<
        index >= 0,
        IntType<index>,
        typename Add<typename ListLength<TypeElem<Head, Tail>>::type, IntType<index>>::type
        >::type::value;

public:
    using type = typename ListTypeAtByVal<Tail, real_index - 1>::type;
};

// the loc of begin
template<typename Head, typename Tail>
struct ListTypeAtByVal<TypeElem<Head, Tail>, 0> {
    using type = Head;
};

// the loc for overflow
template<int index>
struct ListTypeAtByVal<NullType, index> {
    using type = NullType;
};

// get the type at loc by IntType
template<typename TL, typename Index>
struct ListTypeAt : ListTypeAtByVal<TL, Index::value> {};

TM_NS_END

// the meta function to get type by value
#define __tl_type_at_by_val__(...) typename TM_NS::ListTypeAtByVal<__VA_ARGS__>::type
#define __tl_type_at__(...) typename TM_NS::ListTypeAt<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_TYPE_AT_H_*/