#ifndef THOR_META_LIST_ALGORITHM_MAP_H_
#define THOR_META_LIST_ALGORITHM_MAP_H_

#include "thor/meta/list/type_list.h"

/**
 * the map function :
 * input a list and a map meta function (TA -> TB)
 * return a new list after map operation
 */
TM_NS_BEGIN

template<typename TL, template<typename> class MapOperation> struct ListMap;

template<template<typename> class MapOperation>
struct ListMap<NullType, MapOperation> {
    using type = NullType;
};

template<typename Head, typename Tail, template<typename> class MapOperation>
struct ListMap<TypeElem<Head, Tail>, MapOperation> {
    using type = TypeElem<typename MapOperation<Head>::type, typename ListMap<Tail, MapOperation>::type>;
};

TM_NS_END

// help function
#define __tl_map__(...) typename TM_NS::ListMap<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_MAP_H_*/