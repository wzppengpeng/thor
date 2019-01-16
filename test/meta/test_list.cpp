#include "thor/meta/list/list.h"

#include "thor/meta/mtest/mtest.h"


FIXTURE(TEST_TYPE_LIST_AND_BASIC_FUNC) {

    SETUP() {
        using List = __type_list__(int, char, double, float);
    };

    TEST("test value list list") {
        ASSERT_EQ(__value_list__(1, 2, 3), __type_list__(__int__(1), __int__(2), __int__(3)));
    };

    TEST("test the length of type list") {
        ASSERT_EQ(__tl_length__(List), __int__(4));
        ASSERT_EQ(__tl_length__(__type_list__(bool, bool, bool)), __int__(3));
    };

    TEST("test the at function at locations") {
        ASSERT_EQ(__tl_type_at_by_val__(List, 0), int);
        ASSERT_EQ(__tl_type_at__(List, __int__(2)), double);
        ASSERT_INVALID(__tl_type_at_by_val__(List, 5));
        ASSERT_EQ(__tl_type_at_by_val__(List, -1), float);
    };

    TEST("test the index of function") {
        ASSERT_EQ(__tl_index_of__(List, char), __int__(1));
        ASSERT_INVALID(__tl_index_of__(List, long));
    };

    TEST("test the included of type") {
        ASSERT_TRUE(__tl_is_included__(List, int));
        ASSERT_FALSE(__tl_is_included__(List, long));
    };
};


FIXTURE(TEST_TYPE_LIST_NORMAL_FUNCTIONS) {
    SETUP() {
        using List = __type_list__(int, char, double, float);
        using EmptyList = __empty_list__();
        using TempList = __type_list__(int, char, float, char, double);
    };

    TEST("test push back to a list") {
        ASSERT_EQ(__tl_push_back__(EmptyList, int), __type_list__(int));
        ASSERT_EQ(__tl_push_back__(List, long), __type_list__(int, char, double, float, long));
        ASSERT_EQ(__tl_length__(__tl_push_back__(List, unsigned)), __int__(5));
        ASSERT_TRUE(__tl_is_included__(__tl_push_back__(List, long), long));
    };

    TEST("test pop back and pop front") {
        ASSERT_EQ(__tl_pop_front(EmptyList), EmptyList);
        ASSERT_EQ(__tl_pop_back(EmptyList), EmptyList);
        ASSERT_EQ(__tl_pop_back(List), __type_list__(int, char, double));
        ASSERT_EQ(__tl_pop_front(List), __type_list__(char, double, float));
    };

    TEST("test push front to a list") {
        ASSERT_EQ(__tl_push_front__(EmptyList, int), __type_list__(int));
        ASSERT_EQ(__tl_push_front__(List, long), __type_list__(long, int, char, double, float));
        ASSERT_EQ(__tl_length__(__tl_push_front__(List, unsigned)), __int__(5));
        ASSERT_TRUE(__tl_is_included__(__tl_push_front__(List, long), long));
    };

    TEST("erase first type in list") {
        ASSERT_EQ(__tl_erase__(List, char), __type_list__(int, double, float));
        ASSERT_EQ(__tl_erase__(List, long), List);
        ASSERT_EQ(__tl_erase__(__tl_erase__(__tl_erase__(List, int), char), float), __type_list__(double));
    };

    TEST("erase all types in list") {
        ASSERT_EQ(__tl_erase_all__(TempList, char), __type_list__(int, float, double));
        ASSERT_EQ(__tl_length__(__tl_erase_all__(TempList, char)), __int__(3));
    };

    TEST("get the unique list") {
        ASSERT_EQ(__tl_unique__(TempList), __type_list__(int, float, char, double));
        ASSERT_EQ(__tl_length__(__tl_unique__(TempList)), __int__(4));
    };

    TEST("test replace the first type A to B in typelist") {
        ASSERT_EQ(__tl_replace__(List, char, std::string), __type_list__(int, std::string, double, float));
        ASSERT_EQ(__tl_replace__(TempList, char, long), __type_list__(int, long, float, char, double));
    };

    TEST("test replace all type A to B in typelist") {
        ASSERT_EQ(__tl_replace_all__(TempList, char, long), __type_list__(int, long, float, long, double));
    };

    TEST("test tl subset") {
        ASSERT_TRUE(__tl_is_subset__(EmptyList, List));
        ASSERT_TRUE(__tl_is_subset__(List, TempList));
        ASSERT_TRUE(__tl_is_subset__(__type_list__(int, char), List));
        ASSERT_FALSE(__tl_is_subset__(__type_list__(int, long), List));
    };

    TEST("test tl belong") {
        using MixSets = __type_list__(List, TempList, EmptyList, __type_list__(unsigned, long long));
        ASSERT_TRUE(__tl_is_belong__(EmptyList, MixSets));
        ASSERT_FALSE(__tl_is_belong__(__type_list__(std::string, long), MixSets));
        ASSERT_TRUE(__tl_is_belong__(__type_list__(double, char), MixSets));
    };
};


FIXTURE(TEST_TYPE_LIST_HIGH_ORDER_FUNCTIONS) {
    SETUP() {
        template<typename T>
        using IsLargerThanTwo = TM_NS::BoolType<(sizeof(T) > 2)>;

        template<typename T>
        using ToSize = __int__(sizeof(T));

        using List = __type_list__(int, char, double, float);
        using EmptyList = __empty_list__();
        using TempList = __type_list__(int, long, float, long, double);
    };

    TEST("test list any") {
        ASSERT_TRUE(__tl_any__(List, IsLargerThanTwo));
        ASSERT_FALSE(__tl_any__(EmptyList, IsLargerThanTwo));
    };

    TEST("test list all") {
        ASSERT_TRUE(__tl_all__(TempList, IsLargerThanTwo));
        ASSERT_TRUE(__tl_all__(EmptyList, IsLargerThanTwo));
    };

    TEST("test map operation") {
        ASSERT_EQ(__tl_map__(List, ToSize), __type_list__(__int__(4), __int__(1), __int__(8), __int__(4)));
    };

    TEST("test transform operation") {
        using A = __value_list__(1, 2, 3);
        using B = __value_list__(2, 3, 4);
        using C = __tl_transform__(A, B, TM_NS::Add);
        ASSERT_EQ(__tl_map__(C, TM_NS::Inc), __type_list__(__int__(4), __int__(6), __int__(8)));
    };

    TEST("filter list") {
        ASSERT_EQ(__tl_filter__(List, IsLargerThanTwo), __type_list__(int, double, float));
        ASSERT_EQ(__tl_filter__(TempList, IsLargerThanTwo), TempList);
    };

    TEST("test list reduce") {
        using V = __value_list__(1, 2, 3);
        ASSERT_EQ(__tl_reduce__(V), __int__(6));
        ASSERT_EQ(__tl_reduce__(V, __int__(1), TM_NS::Mul), __int__(6));
    };

    TEST("test sort list") {
        using V = __value_list__(3, 2, 1);
        ASSERT_EQ(__tl_sort__(V), __value_list__(1, 2, 3));
        ASSERT_EQ(__tl_sort__(EmptyList), EmptyList);
        ASSERT_EQ(__tl_sort__(__value_list__(1, 2, 2)), __value_list__(1, 2, 2));
        template<typename A, typename B>
        using Comp = TM_NS::BoolType<sizeof(A) < sizeof(B)>;
        using TypeV = __type_list__(char, short, int, double);
        using ShuffleV = __type_list__(double, int, short, char);
        ASSERT_EQ(__tl_sort__(ShuffleV, Comp), TypeV);
    };

    TEST("test joint using") {
        using TL = __type_list__(char, short, int, long, char*, short*, int*, long*);
        using Res = __tl_reduce__(__tl_sort__(__tl_map__(__tl_filter__(TL, IsLargerThanTwo), ToSize)));
        ASSERT_EQ(Res, __int__(44)); // short, int, long -> 4, poiner -> 8
    };
};