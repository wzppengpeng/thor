#ifndef THOR_META_LIST11_ALGORITHM_REDUCE_H_
#define THOR_META_LIST11_ALGORITHM_REDUCE_H_

#include "thor/meta/list11/type_list.h"

#include "thor/meta/base/int_type.h"

/**
 * reduce(fold) the list into a value by meta function with two inputs
 */

TM_NS_BEGIN

template<typename TL, typename Init = IntType<0>, template<typename T, typename U> class TwoInputFun = Add>
struct ListReduce;

template<typename Init, template<typename T, typename U> class TwoInputFun>
struct ListReduce<TypeList<>, Init, TwoInputFun> {
    using type = Init;
};

template<class First, class... Types, typename Init, template<typename T, typename U> class TwoInputFun>
struct ListReduce<TypeList<First, Types...>, Init, TwoInputFun> {
    using type = typename ListReduce
        <
            TypeList<Types...>,
            typename TwoInputFun<Init, First>::type,
            TwoInputFun
        >::type;
};

TM_NS_END

// help function macro
#define __tl_reduce__(...) typename TM_NS::ListReduce<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_REDUCE_H_*/