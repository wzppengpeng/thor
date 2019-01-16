#ifndef THOR_META_BASE_NULL_TYPE_H_
#define THOR_META_BASE_NULL_TYPE_H_

#include "thor/meta/common.h"

TM_NS_BEGIN

/**
 * The null type, only can be declared, but not defined
 */
struct NullType;

TM_NS_END

#define __null__() TM_NS::NullType

#endif /*THOR_META_BASE_NULL_TYPE_H_*/