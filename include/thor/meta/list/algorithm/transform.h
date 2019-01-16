#ifndef THOR_META_LIST_ALGORITHM_TRANSFORM_H_
#define THOR_META_LIST_ALGORITHM_TRANSFORM_H_

#include "map.h"

#include "thor/meta/base/meta_function.h"

/**
 * zip two list
 * transform the ziped list into a new list
 */
TM_NS_BEGIN

// zip two different list
template<typename TLA, typename TLB> struct ListZip;

template<>
struct ListZip<NullType, NullType> {
    using type = NullType;
};

template<typename AHead, typename ATail>
struct ListZip<TypeElem<AHead, ATail>, NullType> {
    using type = TypeElem<Pair<AHead, NullType>, typename ListZip<ATail, NullType>::type>;
};

template<typename BHead, typename BTail>
struct ListZip<NullType, TypeElem<BHead, BTail>> {
    using type = TypeElem<Pair<NullType, BHead>, typename ListZip<NullType, BTail>::type>;
};

template<typename AHead, typename ATail, typename BHead, typename BTail>
struct ListZip<TypeElem<AHead, ATail>, TypeElem<BHead, BTail>> {
    using type = TypeElem<Pair<AHead, BHead>, typename ListZip<ATail, BTail>::type>;
};

// transform two list with meta function
template<typename TLA, typename TLB, template<typename A, typename B> class Func>
struct ListsTransform {
    using type = typename ListMap<typename ListZip<TLA, TLB>::type, PackPair<Func>::template Call>::type;
};


TM_NS_END

// help macro function
#define __tl_zip__(...) typename TM_NS::ListZip<__VA_ARGS__>::type
#define __tl_transform__(...) typename TM_NS::ListsTransform<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_TRANSFORM_H_*/