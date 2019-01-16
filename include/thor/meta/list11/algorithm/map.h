#ifndef THOR_META_LIST11_ALGORITHM_MAP_H_
#define THOR_META_LIST11_ALGORITHM_MAP_H_

#include "push.h"

/**
 * the map function :
 * input a list and a map meta function (TA -> TB)
 * return a new list after map operation
 */
TM_NS_BEGIN

template<typename TL, template<typename> class MapOperation> struct ListMap;

template<class... Types, template<typename> class MapOperation>
struct ListMap<TypeList<Types...>, MapOperation> {
    using type = TypeList<typename MapOperation<Types>::type...>;
};

TM_NS_END

// help function
#define __tl_map__(...) typename TM_NS::ListMap<__VA_ARGS__>::type

#endif /*THOR_META_LIST11_ALGORITHM_MAP_H_*/