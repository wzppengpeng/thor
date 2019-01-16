#ifndef THOR_META_BASE_VOID_T_H_
#define THOR_META_BASE_VOID_T_H_

#include "thor/meta/common.h"

/**
 * define the void_t in C++17, for SFINAE coding
 */

TM_NS_BEGIN

// can only be support in C++14
template< class... >
using void_t = void;

TM_NS_END

#endif /*THOR_META_BASE_VOID_T_H_*/