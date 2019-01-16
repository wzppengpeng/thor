#include <array>

#include "thor/functional/invoke.h"

#include "../../help_function.h"


using namespace std;
using namespace thor;

void foo0() {
    RUN_HERE();
}

int foo1(int a) {
    return ++a;
}

double sum(double a, double b) {
    return a + b;
}

struct C {
int a_;

int get(int b) {
    return a_ + b;
}

};

constexpr int const_add_1(int i) { return i + 1; }

int main()
{
    TEST_BEGIN(Invoke);
    TF_NS::Invoke(foo0); // no params
    std::array<int, TF_NS::Invoke(const_add_1, 1)> a; a[0] = 1; //test the constexpr function of invoke
    ASSERT_EQ(TF_NS::Invoke([](int a) { return foo1(a); }, 0), 1);
    ASSERT_EQ(TF_NS::Invoke([](double a, double b) { return sum(a, b); }, 1, 1.2), 2.2);
    C c; c.a_ = 1;
    ASSERT_EQ(TF_NS::Invoke([&](int b) {return c.get(b);}, 3), 4);
    ASSERT_EQ(TF_NS::Invoke(&C::get, &c, 3), 4); // test member function
    TEST_SUCCESS(Invoke);
    return 0;
}