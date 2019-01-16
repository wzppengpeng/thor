#ifndef THOR_META_LIST_ALGORITHM_ALL_H_
#define THOR_META_LIST_ALGORITHM_ALL_H_

#include "any.h"

#include "thor/meta/base/meta_function.h"

/**
 * check if all types in TypeList match the target
 */

TM_NS_BEGIN

template<typename TL, template<typename> class BoolMetaFun>
struct ListAll {
    using type = typename Not<
                 typename ListAny<TL, NegativeOf<BoolMetaFun>::template Call>::type
                 >::type;
};

TM_NS_END

// help funtions
#define __tl_all__(...) typename TM_NS::ListAll<__VA_ARGS__>::type

#endif /*THOR_META_LIST_ALGORITHM_ALL_H_*/