#ifndef THOR_META_LIST11_ALGORITHM_TRANSFORM_H_
#define THOR_META_LIST11_ALGORITHM_TRANSFORM_H_

#include "thor/meta/list11/type_list.h"

/**
 * transform the ziped list into a new list
 */

TM_NS_BEGIN

template<typename TLA, typename TLB, template<typename A, typename B> class Func>
struct ListsTransform;

template<class... ATypes, class... BTypes, template<typename A, typename B> class Func>
struct ListsTransform<TypeList<ATypes...>, TypeList<BTypes...>, Func> {
    using type = TypeList<typename Func<ATypes, BTypes>::type...>;
};

TM_NS_END

#define __tl_transform__(...) typename TM_NS::ListsTransform<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_TRANSFORM_H_*/