#ifndef THOR_META_BASE_EMPTY_TYPE_H_
#define THOR_META_BASE_EMPTY_TYPE_H_

#include "thor/meta/common.h"

TM_NS_BEGIN

/**
 * the empty type, has no data in this class
 */
struct EmptyType {};

TM_NS_END

#define __emty__() TM_NS::EmptyType

#endif /*THOR_META_BASE_EMPTY_TYPE_H_*/