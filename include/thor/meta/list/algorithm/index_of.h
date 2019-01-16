#ifndef THOR_META_LIST_ALGORITHM_INDEX_OF_H_
#define THOR_META_LIST_ALGORITHM_INDEX_OF_H_

#include "thor/meta/list/type_list.h"

#include "thor/meta/base/utils.h"

/**
 * get the index of some type in type list
 * input List and the target type, get the first matched index
 */

TM_NS_BEGIN

template<typename TL, typename A> struct ListIndexOf;

template<typename Head, typename Tail, typename A>
struct ListIndexOf<TypeElem<Head, Tail>, A> {

private:
    using Temp = typename ListIndexOf<Tail, A>::type;

public:
    using type = typename IfThenElse<
        typename IsValid<Temp>::type,
        IntType<GetValue<Temp>::value + 1>, // this must write like this to make ok for every condition
        NullType
    >::type;

};

template<typename Head, typename Tail>
struct ListIndexOf<TypeElem<Head, Tail>, Head> {
    using type = IntType<0>;
};

template<typename A>
struct ListIndexOf<NullType, A> {
    using type = NullType;
};

TM_NS_END

// meta macro function to get the index of some type in TypeList
#define __tl_index_of__(...) typename TM_NS::ListIndexOf<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_INDEX_OF_H_*/