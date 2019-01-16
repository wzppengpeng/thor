#ifndef THOR_PATTERN_OBSERVER_H_
#define THOR_PATTERN_OBSERVER_H_

#include <vector>
#include <map>
#include <unordered_map>

#include "common.h"

#include "thor/idioms/uncopyable.h"

/**
 * the observer pattern // delegate pattern
 * register a number of functors
 * notify all when called broadcast~
 *  TP_NS::Observer<TF_NS::Functor<void(int, int)>> observer;
    // add the delegate
    auto key1 = observer.Connect([](int i, int j) { print(i + j); });
    auto key2 = observer.Connect([](int i, int j) { print(i * j); });
    auto fun = TF_NS::MakeFunctor([](int i, int j) { return (i + j); })
                | [](int x) { return x * 2; }
                | [](int x) { print(x); };
    auto key3 = observer.Connect(fun);
    print(observer.Size(), "the size of observer delegate");
    // notify
    observer.Notify(1, 2);
    // erase the delegate
    observer.DisConnect(key1);
    observer.DisConnect(key2);
    observer.DisConnect(key3);
 */

TP_NS_BEGIN

template
<
    typename Func, // the functor type
    typename Id = size_t, // the id for each functor
    template<typename...> class Manager = std::map
>
class Observer : TI_NS::Uncopyable {

public:
    // the constructor
    Observer() = default;
    ~Observer() {}

    // the clear operation
    void Clear() {
        next_key_ = Id(0);
        connections_.clear();
    }

    // get the size of registered functors
    inline size_t Size() const {
        return connections_.size();
    }

    // connect function
    template<typename F>
    Id Connect(F&& f) {
        return Assign(std::forward<F>(f));
    }

    // erase the connected functors
    void DisConnect(Id fun_id) {
        connections_.erase(fun_id);
    }

    // erase a list of ids
    void DisConnect(const std::vector<Id>& ids) {
        for(auto fun_id : ids) {
            connections_.erase(fun_id);
        }
    }

    // notify all registered functors
    template<typename... Args>
    void Notify(Args&&... args) {
        for(auto& p : connections_) {
            p.second(std::forward<Args>(args)...);
        }
    }

private:
    // help function for push in different types of functors
    template<typename F>
    void Push(Id index, F&& fun) {
        connections_.emplace(index, std::forward<F>(fun));
    }

    template<typename F>
    Id Assign(F&& f) {
        auto index = next_key_++;
        Push(index, std::forward<F>(f));
        return index;
    }

private:
    Id next_key_ = 0;
    Manager<Id, Func> connections_;
};

// the specialize of Map Observer and Unordermap Observer
template<typename Func>
using MapObserver = Observer<Func, size_t, std::map>;

// the specialize of unordered_map
template<typename Func>
using UnorderMapObServer = Observer<Func, size_t, std::unordered_map>;

TP_NS_END

#endif /*THOR_PATTERN_OBSERVER_H_*/