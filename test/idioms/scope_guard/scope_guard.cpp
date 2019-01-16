#include "thor/idioms/scope_guard.h"

#include "../../help_function.h"


using namespace std;
using namespace thor;


void TestNoParam() {
    std::function < void()> f = [] { print("clean up");};
    {
        print("call dismiss...");
        auto sg = TI_NS::MakeGuard(f);
        //...
        sg.Dismiss();
        print("call dismiss done...");
    }
    {
        print("no call dismiss");
        auto sg = TI_NS::MakeGuard(f);
        print("no call dismiss done...");
    }
    try {
        print("throw");
        auto sg = TI_NS::MakeGuard(f);
        throw 1;
        sg.Dismiss();
        print("throw done...");
    } catch(...) {}
}

void TestParam(int i) {
    auto f = [](int i) { print("now i is ", i); };
    try{
        print("Has value throw");
        auto sg = TI_NS::MakeGuard(f, i);
        //
        throw 1;
    } catch(...) {}
}

int main(int argc, char const *argv[])
{
    TEST_BEGIN(ScopeGuard);
    TestNoParam();
    TestParam(5);
    TEST_SUCCESS(ScopeGuard);
    return 0;
}