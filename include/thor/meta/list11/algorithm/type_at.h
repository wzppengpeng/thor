#ifndef THOR_META_LIST11_ALGORITHM_TYPE_AT_H_
#define THOR_META_LIST11_ALGORITHM_TYPE_AT_H_

#include <tuple>

#include "thor/meta/list11/type_list.h"

#include "length.h"

/**
 * get the type at index I
 */

TM_NS_BEGIN

template<typename TL, int index> struct ListTypeAtByVal;

template<class... Types, int index>
struct ListTypeAtByVal<TypeList<Types...>, index> {

private:
    constexpr static int real_index
        = std::conditional<
        index >= 0,
        IntType<index>,
        typename Add<typename ListLength<TypeList<Types...>>::type, IntType<index>>::type
        >::type::value;

public:

    using type = typename std::tuple_element<real_index, std::tuple<Types...>>::type;

};

// get the type at loc by IntType
template<typename TL, typename Index>
struct ListTypeAt : ListTypeAtByVal<TL, Index::value> {};

TM_NS_END

// the meta function to get type by value
#define __tl_type_at_by_val__(...) typename TM_NS::ListTypeAtByVal<__VA_ARGS__>::type
#define __tl_type_at__(...) typename TM_NS::ListTypeAt<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_TYPE_AT_H_*/