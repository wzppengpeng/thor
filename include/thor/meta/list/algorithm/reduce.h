#ifndef THOR_META_LIST_ALGORITHM_REDUCE_H_
#define THOR_META_LIST_ALGORITHM_REDUCE_H_

#include "thor/meta/list/type_list.h"

#include "thor/meta/base/int_type.h"

/**
 * reduce(fold) the list into a value by meta function with two inputs
 */

TM_NS_BEGIN

template<typename TL, typename Init = IntType<0>, template<typename T, typename U> class TwoInputFun = Add>
struct ListReduce;

template<typename Init, template<typename T, typename U> class TwoInputFun>
struct ListReduce<NullType, Init, TwoInputFun> {
    using type = Init;
};

template<typename Head, typename Tail, typename Init, template<typename T, typename U> class TwoInputFun>
struct ListReduce<TypeElem<Head, Tail>, Init, TwoInputFun> {
    using type = typename ListReduce<
                 Tail,
                 typename TwoInputFun<Head, Init>::type,
                 TwoInputFun
                 >::type;
};

TM_NS_END

// help function macro
#define __tl_reduce__(...) typename TM_NS::ListReduce<__VA_ARGS__>::type


#endif /*THOR_META_LIST_ALGORITHM_REDUCE_H_*/