#ifndef THOR_META_LIST11_ALGORITHM_CONCAT_H_
#define THOR_META_LIST11_ALGORITHM_CONCAT_H_

#include "thor/meta/list11/type_list.h"

/**
 * concat two type list
 */

TM_NS_BEGIN

template<typename TLA, typename TLB> struct ListConcat;

template<class... ATypes, class... BTypes>
struct ListConcat<TypeList<ATypes...>, TypeList<BTypes...>> {
    using type = TypeList<ATypes..., BTypes...>;
};

TM_NS_END

// the help macro
#define __tl_concat__(...) typename ListConcat<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_CONCAT_H_*/