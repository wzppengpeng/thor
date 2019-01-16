#include "thor/pattern/observer.h"
#include "thor/functional/functor.h"

#include "../../help_function.h"

using namespace std;
using namespace thor;

void TestObserver() {
    TP_NS::Observer<TF_NS::Functor<void(int, int)>> observer;
    // add the delegate
    auto key1 = observer.Connect([](int i, int j) { RUN_HERE(); });
    auto key2 = observer.Connect([](int i, int j) { RUN_HERE(); });
    auto fun = TF_NS::MakeFunctor([](int i, int j) { return (i + j); })
                | [](int x) { return x * 2; }
                | [](int x) { ASSERT_EQ(6, x); };
    auto key3 = observer.Connect(fun);
    ASSERT_EQ(observer.Size(), 3);
    // notify
    observer.Notify(1, 2);
    // erase the delegate
    observer.DisConnect(key1);
    observer.DisConnect(key2);
    observer.DisConnect(key3);
    ASSERT_EQ(observer.Size(), 0);
}


int main()
{
    TEST_BEGIN(Observer);
    TestObserver();
    TEST_SUCCESS(Observer);
    return 0;
}