#ifndef THOR_PATTERN_PIMPL_H_
#define THOR_PATTERN_PIMPL_H_

#include <utility>

#include "thor/idioms/uncopyable.h"

#include "common.h"

/**
 * the pimpl/bridge pattern
 * *********************************
 * declaration of public interface, use this pattern to declare a private impl class
 * class A : private Pimpof<A>::Owner
 * class B {
 * ~B; // define the deconstructor is necessary!
 * private:
 *     PimpOf<B>::Type impl_;
 * };
 *
 * define the next class to handle the class
 * template<>
 * ImplOf<B> {
 * // xxxxxx
 * };
 */


TP_NS_BEGIN

// the basic const propagating smart pointer
// easier than unique_ptr, only has the simplest functions
// could not be copied or moved
template<typename T>
struct ConstPropPtr : TI_NS::Uncopyable {
    explicit ConstPropPtr(T* p) : ptr_(p) {}
    ~ConstPropPtr() { DELETE_POINTER(ptr_); }
    T* operator->() { return ptr_; }
    T& operator*()  { return *ptr_; }
    const T* operator->() const  { return  ptr_; }
    const T& operator*()  const  { return *ptr_; }

private:
    ConstPropPtr(void);
    T* ptr_;
};

// class of impl handle class
// it's wrapped of the impl class and
// the smart pointer to handle the memory
template
<
    typename T, // the implement class of T
    typename Pointer = ConstPropPtr<T>
>
class Pimpl : TI_NS::Uncopyable {

public:
    using Impl = T;

    // the constructor
    template<typename... Args>
    Pimpl(Args&&... args) : ptr_(new T(std::forward<Args>(args)...)) {}

    ~Pimpl() {}

    T* operator->() {
        return ptr_.operator->();
    }

    T& operator*() {
        return ptr_.operator*();
    }

    const T* operator->() const {
        return ptr_.operator->();
    }

    const T& operator*() const {
        return ptr_.operator*();
    }

    Pointer& wrapped() {
        return ptr_;
    }

    const Pointer& wrapped() const {
        return ptr_;
    }

private:
    // the smart pointer to handle class
    Pointer ptr_;
};

// the basic owner class of pimpl
// users can private inherited this class
template<class T, typename Pointer = ConstPropPtr<T>>
struct PimplOwner {
    // the constructor to get the args
    template<typename... Args>
    PimplOwner(Args&&... args) : THOR_INHERITED_PIMPL_NAME(std::forward<Args>(args)...) {}

    Pimpl<T, Pointer> THOR_INHERITED_PIMPL_NAME;
};

// Convenience template which uses ImplOf
// users should specialized this template
template<typename T>
struct ImplOf;

template<typename T, template<typename> class Ptr = ConstPropPtr>
struct PImplOf {
    using Impl = T; // the declaration of implement class
    using Type = Pimpl<ImplOf<T>, Ptr<ImplOf<T>>>; // the type of Pimpl wrapper
    using Owner = PimplOwner<ImplOf<T>, Ptr<ImplOf<T>>>; // using Owner for inherited

};

TP_NS_END

#endif /*THOR_PATTERN_PIMPL_H_*/