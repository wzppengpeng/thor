#include "thor/idioms/object_pool.h"

#include "../../help_function.h"


using namespace std;

struct T {
    T() {}

    T(int a, int b) : m_a(a), m_b(b){}

    int Fun() {
        return m_a + m_b;
    }

    int m_a = 0;
    int m_b = 0;
};

void TestObjectPool() {
    TI_NS::ObjectPool<T> t_pool(10, 1, 2);
    ASSERT_EQ(t_pool.Size(), 10);
    ASSERT_FALSE(t_pool.Empty());
    auto ptr = t_pool.Get();
    ASSERT_EQ(ptr->Fun(), 3);
    ASSERT_EQ(t_pool.Size(), 9);
    for(size_t i = 0; i < 9; ++i) {
        auto tmp = t_pool.Get();
    }
    auto tmp = t_pool.Get();
    ASSERT_TRUE(tmp.get() == nullptr);
    tmp = t_pool.Create(1, 2);
    ASSERT_EQ(tmp->Fun(), 3);
    t_pool.Return(std::move(ptr));
    ASSERT_EQ(t_pool.Size(), 1);
    ASSERT_TRUE(ptr.get() == nullptr);
}

int main()
{
    TEST_BEGIN(ObjectPool);
    TestObjectPool();
    TEST_SUCCESS(ObjectPool);
    return 0;
}