#ifndef THOR_META_LIST_TYPE_ELEMENT_H_
#define THOR_META_LIST_TYPE_ELEMENT_H_

#include "thor/meta/common.h"

TM_NS_BEGIN

/**
 * This file is defined the type element, Head is now type node, Tail is next node
 * the structure of type list in functional language is often recursive
 */
template<typename H, typename T>
struct TypeElem {
    using Head = H;
    using Tail = T;
};

TM_NS_END

#define __type_elem__(...) TM_NS::TypeElem<__VA_ARGS__>

#endif /*THOR_META_LIST_TYPE_ELEMENT_H_*/