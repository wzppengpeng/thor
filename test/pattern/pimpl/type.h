#ifndef TEST_PATTERN_PIMPL_TYPE_H_
#define TEST_PATTERN_PIMPL_TYPE_H_

#include "thor/pattern/pimpl.h"
#include "thor/idioms/smart_ptr.h"

class A {

public:
    A(int a, int b);
    ~A(); // the de-constructor is necessary to be decared!!
    void foo();

private:
    TP_NS::PImplOf<A>::Type impl_; // a pointer wrapper

};

class B {

public:
    B(char c);
    ~B();
    void foo();

private:
    TP_NS::PImplOf<B, TI_NS::UniquePtr>::Type impl_;

};


class C : TP_NS::PImplOf<C>::Owner {

public:
    C();
    ~C();
    void foo();
};

class D : TP_NS::PImplOf<D>::Owner {

public:
    D(int d);
    ~D();
    int foo();
};

#endif /*TEST_PATTERN_PIMPL_TYPE_H_*/

