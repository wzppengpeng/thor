#ifndef THOR_META_MTEST_PRINT_H_
#define THOR_META_MTEST_PRINT_H_

#include "thor/meta/common.h"

#include "./utils/unique_name.h"

/**
 * This file is to print mata information based on warning
 */

TM_NS_BEGIN

template<typename T>
struct Print {
    using type = typename T::not_have_this;
};

TM_NS_END

#define __print__(...) typename TM_NS::Print<__VA_ARGS__>::type

#endif /*THOR_META_MTEST_PRINT_H_*/