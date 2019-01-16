#ifndef THOR_META_MTEST_FIXTURE_H_
#define THOR_META_MTEST_FIXTURE_H_

#include "thor/meta/base/empty_type.h"
#include "./utils/unique_name.h"
#include "./test_regorter.h"

////////////////////////////////////////////////////////////////////////
#define FIXTURE(name)                                   \
TM_NS::AutoFixtureRegister _JOIN(tlp_auto_fixture_register, name)(#name);   \
namespace _JOIN(TlpTestFixture_, name)

////////////////////////////////////////////////////////////////////////
#define TEST_SETUP_NAME   TlpTestSetup
using   TEST_SETUP_NAME = TM_NS::EmptyType;

#define SETUP()           struct TEST_SETUP_NAME
#define SETUP_BEGIN()     SETUP(){
#define SETUP_END()       };

////////////////////////////////////////////////////////////////////////
#define TEST_TEARDOWN_NAME   TlpTestTearDown
template<typename TM_TEST>  struct TEST_TEARDOWN_NAME {};

#define TEARDOWN_BEGIN()                                \
template<typename TM_TEST>  struct TEST_TEARDOWN_NAME  \
{                                                       \
    TEST_TEARDOWN_NAME()                                \
    {                                                   \
        struct TearDown: TM_TEST                       \
        {

#define TEARDOWN_END()                              };}};

#define __test_refer(...)       typename TM_TEST::__VA_ARGS__
#define __test_invoke(op, ...)  typename TM_TEST:: template op<__VA_ARGS__>::Result

////////////////////////////////////////////////////////////////////////
#define __TEST_NAME(id)         _JOIN(tm_test_, id)

#define __DEF_TEST(name, id)                                        \
struct __TEST_NAME(id);                                             \
TEST_TEARDOWN_NAME<__TEST_NAME(id)> _JOIN(tlp_test_teardown_, id);  \
TM_NS::AutoTestRegister _JOIN(tlp_auto_test_register, id)(#name);  \
struct __TEST_NAME(id) : TEST_SETUP_NAME

#define TEST(name)   __DEF_TEST(name, UNIQUE_ID)

#endif /*THOR_META_MTEST_FIXTURE_H_*/
