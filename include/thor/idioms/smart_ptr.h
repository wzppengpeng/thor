#ifndef THOR_IDIOMS_SMART_PTRS_H_
#define THOR_IDIOMS_SMART_PTRS_H_

#include <memory>

#include "common.h"

/**
 * alias of unique_ptr and share_ptr in std
 * using the STL smart ptrs
 */
TI_NS_BEGIN

// the alias of unique_ptr
template<typename T>
using UniquePtr = std::unique_ptr<T>;

// the alias of SharedPtr
template<typename T>
using SharedPtr = std::shared_ptr<T>;

// the alias of weak ptr
template<typename T>
using WeakPtr = std::weak_ptr<T>;

TI_NS_END

#endif /*THOR_IDIOMS_SMART_PTRS_H_*/