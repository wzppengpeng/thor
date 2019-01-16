#ifndef THOR_META_LIST11_ALGORITHM_LENGTH_H_
#define THOR_META_LIST11_ALGORITHM_LENGTH_H_

#include "thor/meta/list11/type_list.h"

/**
 * get the length of type list
 */

TM_NS_BEGIN

template<class TL> struct ListLength;

template<class... Types>
struct ListLength<TypeList<Types...>> {
    using type = IntType<sizeof...(Types)>;
};

TM_NS_END

// the help macro
#define __tl_length__(...) typename TM_NS::ListLength<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_LENGTH_H_*/