#include "b.h"

#include "thor/pattern/factory.h"

TP_NS::Registry<Base, B, std::string, __type_list__(const int&, int)> regis_b("b");

B::B(const int& a, int b) : Base(a, b) {}

int B::Run() {
    return a_ * b_;
}