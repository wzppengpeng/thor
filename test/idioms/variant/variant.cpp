
#include "thor/idioms/variant.h"

#include "../../help_function.h"

using namespace std;

void TestVariant() {
    // test construct
    typedef TI_NS::Variant<int, double, string, vector<int>> CV;
    CV v1 = vector<int> {1, 3, 5};
    ASSERT_FALSE(v1.Empty());
    ASSERT_TRUE(v1.Is<std::vector<int>>());
    ASSERT_FALSE(v1.Is<string>());
    ASSERT_EQ(v1.Get<vector<int>>()[0], 1);
    v1.Get<vector<int>>().push_back(6);
    ASSERT_EQ(v1.Get<vector<int>>(), (vector<int> {1, 3, 5, 6}));
    v1 = string("temp");
    v1 = 0.01;
    v1 = string("temp");
    ASSERT_EQ(v1.Index(), 2);
    v1.Visit([](int i) { ASSERT_EQ(i, 5); },
             [](string& s) { ASSERT_EQ(s, string("temp")); s = "tmp"; },
             [](double j) { ASSERT_EQ(j, 6.0); } );
    ASSERT_EQ(v1.Get<string>(), "tmp");
}


int main()
{
    TEST_BEGIN(Variant);
    TestVariant();
    TEST_SUCCESS(Variant);
    return 0;
}