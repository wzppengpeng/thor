#include "thor/idioms/any.h"

#include "../../help_function.h"


void TestAny() {
    TI_NS::Any a(5);
    ASSERT_FALSE(a.Is<float>());
    ASSERT_TRUE(a.Is<int>());
    a.cast<int>() = 6;
    ASSERT_EQ(a.cast<int>(), 6);

    a = 0.6;
    ASSERT_TRUE(a.Is<double>());
    ASSERT_FALSE(a.IsNull());

    a = std::vector<int> {1, 2, 3};
    ASSERT_TRUE(a.Is<std::vector<int>>());
    ASSERT_EQ_ARRAY(a.cast<std::vector<int>>(), (std::vector<int> {1, 2, 3}));
}


int main(int argc, char const *argv[])
{
    TEST_BEGIN(Any);
    TestAny();
    TEST_SUCCESS(Any);
    return 0;
}