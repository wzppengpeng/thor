#ifndef THOR_META_MTEST_ASSERT_H_
#define THOR_META_MTEST_ASSERT_H_

#include "thor/meta/base/utils.h"
#include "thor/meta/base/int_type.h"

/**
 * some macro to run static assert
 */
#define ASSERT_TRUE(T)                  \
static_assert(__value__(T), "Assert Failed: expect "#T" be true, but be false!")

#define ASSERT_FALSE(T)                 \
static_assert(!(__value__(T)), "Assert Failed: expect "#T" be false, but be true!")

#define ASSERT_VALID(T)                 \
static_assert(__value__(__is_valid__(T)), "Assert Failed: expect "#T" be valid, but be invalid!")

#define ASSERT_INVALID(T)               \
static_assert(!(__value__(__is_valid__(T))), "Assert Failed: expect "#T" be invalid, but be valid!")

#define ASSERT_EQ(T, Expected)          \
static_assert(__value__(__is_same__(T, Expected)), "Assert Failed: expect "#T" be equal to "#Expected"!")

#define ASSERT_NE(T, Expected)          \
static_assert(!(__value__(__is_same__(T, Expected))), "Assert Failed: expect "#T" be not equal to "#Expected"!")

#define ASSERT_LT(T, Other)             \
static_assert(__value__(__lt__(T, Other)), "Assert Failed: expect "#T" be less to "#Other"!")

#define ASSERT_GT(T, Other)             \
static_assert(__value__(__gt__(T, Other)), "Assert Failed: expect "#T" be greater to "#Other"!")

#endif /*THOR_META_MTEST_ASSERT_H_*/