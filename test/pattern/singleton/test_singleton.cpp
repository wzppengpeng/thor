#include "thor/pattern/singleton.h"

#include "../../help_function.h"

using namespace std;

class Hello {

public:
    Hello(int b) : a(b) {}

    void Set() { ++a; }

    int Run() {
        return a;
    }

private:
    int a = 0;
};

using HelloSingleton = TP_NS::SingletonHolder<Hello>;
using HelloSingletonShared = TP_NS::SingletonHolder<Hello, TP_NS::CreateShared>;

int foo1() {
    HelloSingleton::Instance(5)->Set();
    return HelloSingleton::Instance(1)->Run();
}

int foo2() {
    HelloSingletonShared::Instance(1)->Set();
    return HelloSingletonShared::Instance(100)->Run();
}

int main() {
    TEST_BEGIN(Singleton);
    ASSERT_EQ(foo1(), 6); // first call, init as 5
    ASSERT_EQ(foo1(), 7);
    ASSERT_EQ(foo2(), 2);
    ASSERT_EQ(foo2(), 3);
    TEST_SUCCESS(Singleton);
    return 0;
}