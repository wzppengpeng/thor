#include "type.h"

#include "../../help_function.h"

int main(int argc, char const *argv[])
{
    TEST_BEGIN(Pimpl);
    A a(1, 2);
    a.foo();
    B('a').foo();
    C().foo();
    ASSERT_EQ(D(2).foo(), 4);
    TEST_SUCCESS(Pimpl);
    return 0;
}