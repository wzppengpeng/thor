#include "thor/functional/functor.h"

#include "../../help_function.h"

using namespace std;
using namespace thor;

void TestFunctor1() {
    // test the chain
    auto fun1 = TF_NS::MakeFunctor([](int i) { return i + 1; });
    ASSERT_EQ(2, fun1(1));
    auto fun2 = fun1.Then([](int i) {return i + 2;}).Then([](int i) { return i * 5;});
    ASSERT_EQ(fun2(1), 20);
    TF_NS::MakeFunctor([]{ RUN_HERE(); }).Then([]{RUN_HERE();}).Then([]{RUN_HERE();}).Run();
    // test |
    auto fun3 = TF_NS::MakeFunctor([](int i) { return i + 1; }) | [](int i) { return i * 2; }
                                                                | [](int i) { return i - 5; };
    ASSERT_EQ(fun3(1), -1);
}

void TestVector() {
    std::vector<int> v {1,2,3,4,5,6,7,8,9,10};
    auto fun = TF_NS::MakeFunctor([](vector<int>* v) ->vector<int>* { v->push_back(11); return v; })
            | [](vector<int>* v) ->vector<int>* { for(auto& i : *v) { ++i;}; return v; }
            | [](vector<int>* v) { v->pop_back(); };
    fun(&v);
    ASSERT_EQ_ARRAY(v, (vector<int> {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    auto void_fun = TF_NS::MakeFunctor([&]{ v.push_back(5); })
            | [&] {v.push_back(10);} | [&] {v.push_back(15);};
    void_fun();
    ASSERT_EQ_ARRAY(v, (vector<int> {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 5, 10, 15}));
}

void TestCurry() {
    auto fun = TF_NS::MakeFunctor([](int i, double j, char c, float d) {
        return i + j + c + d;
    }).Curry();
    auto fun1 = fun.CurryBefore(1).CurryBefore(4.5).CurryAfter(4.5);
    ASSERT_EQ(fun1(0), 10);
    auto chain_fun = TF_NS::MakeFunctor([](int i, double j, char c, float d) {
        return i + j + c + d;
    }) | [](double j) { return j + 4; }
       | [](double j) { return j + 7; }
       | [](double j) { return j * 2; };
    auto fun2 = chain_fun.Curry().CurryBefore(1, 4).CurryAfter(4);
    ASSERT_EQ(fun2(1), 42);
}

int main()
{
    TEST_BEGIN(Functor);
    TestFunctor1();
    TestVector();
    TestCurry();
    TEST_SUCCESS(Functor);
    return 0;
}