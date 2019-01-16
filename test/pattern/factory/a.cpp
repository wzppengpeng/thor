#include "a.h"

#include "thor/pattern/factory.h"

TP_NS::Registry<Base, A, std::string, __type_list__(const int&, int)> regis_a("a");

A::A(const int& a, int b) : Base(a, b) {}

int A::Run() {
    return a_ + b_;
}