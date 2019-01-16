#include "thor/meta/traits/traits.h"

#include "thor/meta/mtest/mtest.h"

FIXTURE(TEST_TRAITS_OF_NORMAL) {
    TEST("test convertible") {
        ASSERT_FALSE(__is_convertible__(std::string, int));
        ASSERT_TRUE(__is_convertible__(int, char));
        ASSERT_TRUE(__is_both_convertible__(int, size_t));
        ASSERT_TRUE(__is_convertible__(int, long long));
    };

    TEST("test built in") {
        ASSERT_TRUE(__is_built_in__(int));
        ASSERT_FALSE(__is_built_in__(std::string));
        ASSERT_TRUE(__is_built_in__(const char&));
    };
};


FIXTURE(TEST_FUNCTION_TRAITS) {
    TEST("test fucntion traits of lambda") {
        void run() {
            auto f = [](const int* a, char b) { return *a + b; };
            using Fun = decltype(f);
            ASSERT_EQ(__fun_return_type__(Fun), int);
            ASSERT_EQ(__int__(__fun_args_number__(Fun)), __int__(2));
            ASSERT_EQ(__fun_args_type__(Fun, 0), const int*);
            ASSERT_EQ(__fun_args_type__(Fun, 1), char);
        }
    };
};