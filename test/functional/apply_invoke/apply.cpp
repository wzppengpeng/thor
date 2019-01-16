#include "thor/functional/apply.h"

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


struct Point {
    Point(int x, int y) : x_(x), y_(y) {}

    int x_, y_;
};

int main()
{
    TEST_BEGIN(Apply);
    TF_NS::Apply(foo0, std::tuple<>());
    ASSERT_EQ(TF_NS::Apply(foo1, std::make_tuple(4)), 5);
    std::tuple<double, double> t(std::make_tuple(0.4, 0.7));
    ASSERT_EQ(TF_NS::Apply([](double a, double b) { return sum(a, b); }, std::move(t)), 1.1);
    ASSERT_EQ(TF_NS::Apply([](int b, char c) { return b + c; }, std::make_tuple(1, 4)), 5);
    ASSERT_EQ(TF_NS::Apply([](Point left, Point right) { return left.x_ + right.x_; },
        std::make_tuple(Point(1, 2), Point(2, 3))), 3);
    TEST_SUCCESS(Apply);
    return 0;
}