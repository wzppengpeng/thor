#ifndef THOR_META_LIST11_ALGORITHM_INDEX_OF_H_
#define THOR_META_LIST11_ALGORITHM_INDEX_OF_H_

#include "thor/meta/list11/type_list.h"

#include "thor/meta/base/null_type.h"

#include "thor/meta/base/utils.h"

/**
 * get the index of some type
 */

TM_NS_BEGIN

template<typename TL, typename A> struct ListIndexOf;

template<class First, class... Types, class A>
struct ListIndexOf<TypeList<First, Types...>, A> {
private:
    using Temp = typename ListIndexOf<TypeList<Types...>, A>::type;

public:
    using type = typename IfThenElse
        <
            typename IsValid<Temp>::type,
            IntType<GetValue<Temp>::value + 1>,
            NullType
        >::type;
};

template<class A, class... After>
struct ListIndexOf<TypeList<A, After...>, A> {
    using type = IntType<0>;
};

template<class A>
struct ListIndexOf<TypeList<>, A> {
    using type = NullType;
};

TM_NS_END

// meta macro function to get the index of some type in TypeList
#define __tl_index_of__(...) typename TM_NS::ListIndexOf<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_INDEX_OF_H_*/