#include "thor/pattern/factory.h"

#include "abstract.h"
#include "a.h"
#include "b.h"

#include "../../help_function.h"

int main() {
    using Factory = TP_NS::FactoryHolder<Base, std::string, __type_list__(const int&, int)>;
    TEST_BEGIN(Factory);
    auto a = Factory::Instance()->CreateUnique("a", 1, 2);
    ASSERT_EQ(a->Run(), 3);
    auto b = Factory::Instance()->CreateUnique("b", 1, 2);
    ASSERT_EQ(b->Run(), 2);
    TEST_SUCCESS(Factory);
    return 0;
}