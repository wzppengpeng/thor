#include "type.h"

#include "../../help_function.h"

TP_NS_BEGIN

// the define of Imple A
template<>
struct ImplOf<A> {
    ImplOf<A>(int a, int b) : a_(a), b_(b) {}

    void foo() {
        ASSERT_EQ(a_ + b_, 3);
    }

private:
    int a_, b_;
};

// the define of Impl B
template<>
struct ImplOf<B> {
    ImplOf<B>(char c) : c_(c) {}
    void foo() {
        ASSERT_EQ(c_ + 1, 'b');
    }
private:
    char c_;
};

// the define of impl C
template<>
struct ImplOf<C> {
    ImplOf<C>() {}
    void foo() {
        RUN_HERE();
    }
};

// the defien of impl D
template<>
struct ImplOf<D> {
    ImplOf<D>(int d) : d_(d) {}

    int foo() {
        return d_ + 2;
    }

private:
    int d_;
};

TP_NS_END


A::A(int a, int b) : impl_(a, b) {}

void A::foo() {
    impl_->foo();
}

A::~A() {}


B::B(char c) : impl_(c) {}

void B::foo() {
    impl_->foo();
}

B::~B() {}

C::C()  {}

C::~C() {}

void C::foo() {
    THOR_INHERITED_PIMPL_NAME->foo();
}

D::D(int d) : TP_NS::PImplOf<D>::Owner(d) {} // pass forward the params

D::~D() {}

int D::foo() {
    return THOR_INHERITED_PIMPL_NAME->foo();
}