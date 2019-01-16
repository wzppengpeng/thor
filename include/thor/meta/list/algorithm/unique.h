#ifndef THOR_META_LIST_ALGORITHM_UNIQUE_H_
#define THOR_META_LIST_ALGORITHM_UNIQUE_H_

#include "thor/meta/list/type_list.h"

#include "is_included.h"

/**
 * erase the recuplcated types in Type List
 */
TM_NS_BEGIN

template<typename TL> struct ListUnique;

template<typename Head, typename Tail>
struct ListUnique<TypeElem<Head, Tail>> {
    using type = __if__(typename ListIsIncluded<Tail, Head>::type,
                 typename ListUnique<Tail>::type,
                 TypeElem<Head, typename ListUnique<Tail>::type>);
};

template<>
struct ListUnique<NullType> {
    using type = NullType;
};

TM_NS_END

// help macro functions
#define __tl_unique__(...) typename TM_NS::ListUnique<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_UNIQUE_H_*/