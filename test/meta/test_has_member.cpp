#include "thor/meta/traits/has_member.h"

#include "thor/meta/mtest/mtest.h"

// define has member
HAS_MEMBER(foo)
HAS_MEMBER(bar)

// define has member function
HAS_MEMBER_FUNCTION(bar)

FIXTURE(TETS_HAS_MEMBERS) {
    SETUP() {
        struct A {
            static float bar;
            int foo;
        };

        struct B {
            int no;
            int bar(int i, int j);
        };
    };

    // TEST("test has members") {
    //     ASSERT_TRUE(__check_has_member__(A, foo));
    //     ASSERT_FALSE(__check_has_member__(B, foo));
    //     ASSERT_TRUE(__check_has_member__(A, bar));
    // };

    TEST("test has member functions") {
        ASSERT_FALSE(__check_has_member_function__(A, bar));
        ASSERT_TRUE(__check_has_member_function__(B, bar));
    };
};

