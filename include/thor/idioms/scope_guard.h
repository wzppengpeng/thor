#ifndef THOR_IDIOMS_SCOPE_GUARD_H_
#define THOR_IDIOMS_SCOPE_GUARD_H_

#include <functional>

#include "uncopyable.h"
#include "thor/functional/apply.h"


/**
 * the scope guard
 * input a function object to handle the miss resource
 * automaticall call this function to handle the dismmiss
 * the input only support function object and normal function pointer,
 * but not std::bind or member function pointer
 */

TI_NS_BEGIN

// obtain a function object
DECLARE_LAMBDA_FUNCTION_TEMPLATE(ScopeGuard)

template<typename R, typename... Args>
class ScopeGuard<R(Args...)> : Uncopyable {
public:
    ScopeGuard() = default;

    template<typename F, typename... A>
    void Register(F&& f, A&&... args) {
        fn_ = std::forward<F>(f);
        args_ = std::move(std::make_tuple(std::forward<A>(args)...));
    }

    ~ScopeGuard() {
        if(!is_dismiss_) {
            TF_NS::Apply(fn_, args_);
        }
    }

    void Dismiss() {
        is_dismiss_ = true;
    }

    ScopeGuard(ScopeGuard&& other)
        : is_dismiss_(other.is_dismiss_), fn_(std::move(other.fn_)),
        args_(std::move(other.args_)) {
        other.Dismiss();
    }

private:
    bool is_dismiss_ = false;
    std::function<R(Args...)> fn_;
    std::tuple<Args...> args_;
};

// member function pointer
DECLARE_MEMBER_FUNCTION_POINTER_TEMPLATE(ScopeGuard)

// the help function to get the scope guard
template<typename F, typename... Args>
ScopeGuard<typename std::decay<F>::type> MakeGuard(F&& f, Args&&... args) {
    ScopeGuard<typename std::decay<F>::type> sg;
    sg.Register(std::forward<F>(f), std::forward<Args>(args)...);
    return std::move(sg);
}


TI_NS_END

#endif /*THOR_IDIOMS_SCOPE_GUARD_H_*/