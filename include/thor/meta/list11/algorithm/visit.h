#ifndef THOR_META_LIST11_ALGORITHM_VISIT_H_
#define THOR_META_LIST11_ALGORITHM_VISIT_H_

#include <utility>

#include "type_at.h"

/**
 * visit interface (since c++14)
 * to get the type in type list using runtime index
 * USAGE:

 *  using List = __type_list__(int, char, double);

    void foo(size_t i) {
        TM_NS::ListVisitor<List>::Visit(i, [](auto item) {
            constexpr auto Index = decltype(item)::value;
            using T = __tl_type_at_by_val__(List, Index);
            wzp::print(typeid(T).name());
        });
    }
    // i is the runtime index, I is the compile index
 */

TM_NS_BEGIN

namespace details {

// the switch function
template<typename F, std::size_t... Is>
void compile_switch(const std::size_t i, F&& f, std::index_sequence<Is...>) {
    (void)std::initializer_list<int> {
            (i == Is && (
                    (void)std::forward<F>(f)(std::integral_constant<size_t, Is>{}), 0))...
    };
}

} //details

template<typename TL> struct ListVisitor;

template<class... Types>
struct ListVisitor<TypeList<Types...>> {
    // the visit interface
    template<typename F>
    static void Visit(const std::size_t i, F&& f) {
        constexpr auto N = sizeof...(Types);
        details::compile_switch(i, std::forward<F>(f), std::make_index_sequence<N>{});
    }
};

TM_NS_END

#endif /*THOR_META_LIST11_ALGORITHM_VISIT_H_*/