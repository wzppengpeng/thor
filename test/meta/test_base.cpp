
#include "thor/meta/base/base.h"

#include "thor/meta/mtest/mtest.h"


FIXTURE(TESTBOOL) {
    TEST("true type should be true") {
        ASSERT_TRUE(__true__());
        ASSERT_EQ(__true__(), __bool__(true));
        ASSERT_NE(__bool__(false), __true__());
    };

    TEST("false type should be false") {
        ASSERT_FALSE(__false__());
        ASSERT_EQ(__true__(), __bool__(true));
        ASSERT_NE(__bool__(false), __true__());
    };

    TEST("operation not on bool type") {
        ASSERT_TRUE(__not__(__false__()));
        ASSERT_FALSE(__not__(__bool__(true)));
    };

    TEST("operation and on bool type") {
        ASSERT_TRUE(__and__(__true__(), __true__()));
        ASSERT_FALSE(__and__(__true__(), __false__()));
    };

    TEST("operation or on bool type") {
        ASSERT_TRUE(__or__(__true__(), __true__()));
        ASSERT_TRUE(__or__(__true__(), __false__()));
        ASSERT_FALSE(__or__(__false__(), __false__()));
    };
};


FIXTURE(TestInt) {
    TEST("compare int type") {
        ASSERT_EQ(__int__(0), __int__(0));
        ASSERT_NE(__int__(0), __int__(1));
    };

    TEST("operator inc on int type") {
        ASSERT_EQ(__inc__(__int__(0)), __int__(1));
    };

    TEST("operator dec on int type") {
        ASSERT_EQ(__dec__(__int__(0)), __int__(-1));
    };

    TEST("operator add on int type") {
        ASSERT_EQ(__add__(__int__(0), __int__(1)), __int__(1));
    };

    TEST("operator sub on int type") {
        ASSERT_EQ(__sub__(__int__(0), __int__(1)), __int__(-1));
    };

    TEST("operator mul on int type") {
        ASSERT_EQ(__mul__(__int__(0), __int__(1)), __int__(0));
        ASSERT_EQ(__mul__(__int__(1), __int__(10)), __int__(10));
        ASSERT_EQ(__mul__(__int__(10), __int__(11)), __int__(110));
    };

    TEST("operator div on int type") {
        ASSERT_EQ(__div__(__int__(0), __int__(1)), __int__(0));
        ASSERT_EQ(__div__(__int__(10), __int__(2)), __int__(5));
        ASSERT_EQ(__div__(__int__(11), __int__(2)), __int__(5));
    };

    TEST("operator mod on int type") {
        ASSERT_EQ(__mod__(__int__(0), __int__(1)), __int__(0));
        ASSERT_EQ(__mod__(__int__(10), __int__(2)), __int__(0));
        ASSERT_EQ(__mod__(__int__(11), __int__(3)), __int__(2));
    };

    TEST("sum of several numbers") {
        ASSERT_EQ(__sum__(), __int__(0));
        ASSERT_EQ(__sum__(__int__(1), __int__(2), __int__(5)), __int__(8));
    };

    TEST("check the lt") {
        ASSERT_LT(__int__(5), __int__(6));
        ASSERT_LT(__int__(0), __sum__(__int__(5), __int__(4), __dec__(__int__(4))));
    };

    TEST("check the gt") {
        ASSERT_GT(__int__(6), __int__(3));
        ASSERT_GT(__mul__(__int__(3), __inc__(__int__(4))), __int__(14));
    };
};

FIXTURE(TestIf) {
    TEST("test same type") {
        ASSERT_TRUE(__is_same__(int, int));
        ASSERT_TRUE(__is_same__(__int__(5), __inc__(__int__(4))));
        ASSERT_FALSE(__is_same__(const int, int));
        ASSERT_FALSE(__is_same__(__int__(4), __dec__(__int__(4))));
    };

    TEST("test the if else type") {
        ASSERT_TRUE(__is_same__(__if__(__true__(), int, float), int));
        ASSERT_FALSE(__is_same__(__if__(__false__(), int, float), int));
    };
};