#ifndef THOR_FUNCTIONAL_FUNCTOR_H_
#define THOR_FUNCTIONAL_FUNCTOR_H_

#include <utility>
#include <type_traits>
#include <functional>

#include "common.h"
#include "apply.h"

/**
 * a chain std::function
 * call function as a list
 * please do not use reference return in the chain
 * use pointer instead~
 * also support curry functor
 * !! Usage:
 *  auto chain_fun = TF_NS::MakeFunctor([](int i, double j, char c, float d) {
        return i + j + c + d;
    }) | [](double j) { return j + 4; }
       | [](double j) { return j + 7; }
       | [](double j) { return j * 2; };
    auto fun2 = chain_fun.Curry().CurryBefore(1, 4).CurryAfter(4);
 */

TF_NS_BEGIN

// define the curry functor, can save the parameters as tuple in the functor
// //////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////
template<typename F, typename Before = std::tuple<>, typename After = std::tuple<>>
class CurryFunctor {
    F fun_;
    Before tuple_before_;
    After tuple_after_;

public:
    // constrtor
    CurryFunctor(F&& f) : fun_(std::move(f)) {}
    CurryFunctor(const F& f) : fun_(f) {}

    CurryFunctor(const F& f, const Before& before, const After& after)
        : fun_(f), tuple_before_(before), tuple_after_(after) {}

    template<typename... Args>
    auto operator() (Args&&... args)
        -> decltype(Apply(fun_,
            std::tuple_cat(tuple_before_, std::make_tuple(std::forward<Args>(args)...), tuple_after_))) {
        return Apply(fun_, std::tuple_cat(tuple_before_, std::make_tuple(std::forward<Args>(args)...),
            tuple_after_));
    }

    // curry add params into before tuple
    template<typename... Args>
    auto CurryBefore(Args&&... args)
        -> CurryFunctor<F,
            decltype(std::tuple_cat(tuple_before_,
                std::make_tuple(std::forward<Args>(args)...))), After> {
        return CurryFunctor<F,
            decltype(std::tuple_cat(tuple_before_, std::make_tuple(std::forward<Args>(args)...))), After>
            (fun_, std::tuple_cat(tuple_before_,
                std::make_tuple(std::forward<Args>(args)...)), tuple_after_);
    }

    // curry add params into after tuple
    template<typename... Args>
    auto CurryAfter(Args&&... args)
        -> CurryFunctor<F, Before,
            decltype(std::tuple_cat(tuple_after_, std::make_tuple(std::forward<Args>(args)...)))> {
        return CurryFunctor<F, Before,
            decltype(std::tuple_cat(tuple_after_, std::make_tuple(std::forward<Args>(args)...)))>
            (fun_, tuple_before_,
                std::tuple_cat(tuple_after_, std::make_tuple(std::forward<Args>(args)...)));
    }

    // get the raw functor
    F GetFunctor() const {
        return fun_;
    }
};

// the help function to make functor into curry function
template<typename F>
CurryFunctor<typename std::decay<F>::type> FunctorToCurry(F&& f) {
    return CurryFunctor<typename std::decay<F>::type>(std::forward<F>(f));
}


// obtain a function object, has no parameters
// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////
DECLARE_LAMBDA_FUNCTION_TEMPLATE(Functor)

template<typename R, typename... Args>
class Functor<R(Args...)> {

public:
    using return_type = R;
    // constructor
    Functor() = default;

    // the constructor
    template<typename F>
    Functor(F f) : fn_(std::move(f)) {}

    // copy constructor
    Functor(const Functor& f) = default;
    Functor& operator= (const Functor& f) = default;

    // register
    template<typename F>
    void Register(F&& f) {
        fn_ = std::forward<F>(f);
    }

    // curry this functor to receive params
    CurryFunctor<Functor<R(Args...)>> Curry() {
        return FunctorToCurry(*this);
    }

    ~Functor() {}

    // the run operation
    template<typename... A>
    R Run(A&&... a) {
        return fn_(std::forward<A>(a)...);
    }

    // the operator () to make it as function object
    template<typename... A>
    R operator() (A&&... a) {
        return Run(std::forward<A>(a)...);
    }

    // the then interface to chain functions
    template<typename F>
    typename std::enable_if<!std::is_void<typename std::result_of<F(R)>::type>::value,
        Functor<typename std::result_of<F(R)>::type(Args...)>>::type Then(F f) {
        using ThenReturnType = typename std::result_of<F(R)>::type;
        auto temp_f = fn_;
        Functor<ThenReturnType(Args...)> next_f([temp_f, f](Args&&... args) {
            auto last_r = temp_f(std::forward<Args>(args)...);
            return f(last_r);
        });
        return next_f;
    }

    template<typename F>
    typename std::enable_if<std::is_void<typename std::result_of<F(R)>::type>::value,
        Functor<void(Args...)>>::type Then(F f) {
        auto temp_f = fn_;
        Functor<void(Args...)> next_f([temp_f, f](Args&&... args) {
            auto last_r = temp_f(std::forward<Args>(args)...);
            f(last_r);
        });
        return next_f;
    }

private:
    std::function<R(Args...)> fn_;

};

// the speacial of void return
// ///////////////////////////////////////
template<typename... Args>
class Functor<void(Args...)> {

public:
    using return_type = void;
    // constructor
    Functor() = default;

    // the constructor
    template<typename F>
    Functor(F f) : fn_(std::move(f)) {}

    // copy constructor
    Functor(const Functor& f) = default;
    Functor& operator= (const Functor& f) = default;

    // register
    template<typename F>
    void Register(F&& f) {
        fn_ = std::forward<F>(f);
    }

    // curry this functor to receive params
    CurryFunctor<Functor<void(Args...)>> Curry() {
        return FunctorToCurry(*this);
    }

    ~Functor() {}

    // the run operation
    template<typename... A>
    void Run(A&&... a) {
        fn_(std::forward<A>(a)...);
    }

    // the operator () to make it as function object
    template<typename... A>
    void operator() (A&&... a) {
        Run(std::forward<A>(a)...);
    }

    // the then interface to chain functions
    template<typename F>
    typename std::enable_if<!std::is_void<typename std::result_of<F()>::type>::value,
        Functor<typename std::result_of<F()>::type(Args...)>>::type Then(F f) {
        using ThenReturnType = typename std::result_of<F()>::type;
        auto temp_f = fn_;
        Functor<ThenReturnType(Args...)> next_f([temp_f, f](Args&&... args) {
            temp_f(std::forward<Args>(args)...);
            return f();
        });
        return next_f;
    }

    template<typename F>
    typename std::enable_if<std::is_void<typename std::result_of<F()>::type>::value,
        Functor<void(Args...)>>::type Then(F f) {
        auto temp_f = fn_;
        Functor<void(Args...)> next_f([temp_f, f](Args&&... args) {
            temp_f(std::forward<Args>(args)...);
            f();
        });
        return next_f;
    }

private:
    std::function<void(Args...)> fn_;

};

// member function pointer
DECLARE_MEMBER_FUNCTION_POINTER_TEMPLATE(Functor)

// the help function to make the first Functor
template<typename F>
Functor<typename std::decay<F>::type> MakeFunctor(F&& f) {
    Functor<typename std::decay<F>::type> fun;
    fun.Register(std::forward<F>(f));
    return fun;
}

TF_NS_END

// global overload the opeartor | for easy use
// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////
template<typename Functor, typename F> // function template can not use void_t
auto operator | (Functor&& functor, F f)
    -> decltype(functor.Then(std::move(f))) {
    return functor.Then(std::move(f));
}

// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////
// ////////////////////////////////////////////////////

#endif /*THOR_FUNCTIONAL_FUNCTOR_H_*/