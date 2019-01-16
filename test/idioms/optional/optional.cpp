#include <map>
#include <unordered_map>

#include "thor/idioms/optional.h"

#include "../../help_function.h"


using namespace std;
using TI_NS::Optional;

void Testoptional() {
    Optional<int> op;
    ASSERT_FALSE(op.IsInit());
    Optional<int> op1 = 1;
    ASSERT_TRUE(op1.IsInit());
    ASSERT_EQ(*op1, 1);

    Optional<string> a("ok");
    Optional<string> b("ok");
    Optional<string> c("not ok");
    ASSERT_TRUE(bool(a));
    ASSERT_LT(c, a);
    c = a;
    ASSERT_EQ(c, a);
    map<Optional<string>, int> mymap; // based on operator <
    mymap.emplace(a, 1);
    ASSERT_TRUE(mymap.count(a) > 0);

    unordered_map<Optional<string>, int> my_umap;
    my_umap.emplace(a, 1);
    ASSERT_TRUE(my_umap.count(a) > 0);
}


int main()
{
    TEST_BEGIN(Optional);
    Testoptional();
    TEST_SUCCESS(Optional);
    return 0;
}