#ifndef THOR_TEST_HELP_FUNCTION_H_
#define THOR_TEST_HELP_FUNCTION_H_

#include <cassert>
#include <iostream>
#include <vector>

namespace thor {

/*print function like python*/
template<typename T>
void print(T&& t){
    std::cout << std::forward<T>(t) << std::endl;
}

//the any print function
template<typename T, typename... Args>
void print(T&& t, Args&&... args){
    std::cout << std::forward<T>(t) << ' ';
    print(std::forward<Args>(args)...);
}

/**
 * print vector
 */
template<typename T>
void print_vector(const std::vector<T>& v) {
    std::cout << '[';
    for(int i = 0; i < v.size() - 1; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << v.back() << ']' << std::endl;
}

/**
 * [print_err description]
 * @param t any type which can use <<
 */
template<typename T>
void print_err(T&& t) {
    std::cerr << std::forward<T>(t) << std::endl;
}

template<typename T, typename... Args>
void print_err(T&& t, Args&&... args) {
    std::cerr << std::forward<T>(t) << ' ';
    print_err(std::forward<Args>(args)...);
}

} //thor

// some macro assert for test
#define ASSERT_TRUE(FLAG) assert(FLAG)
#define ASSERT_FALSE(FLAG) assert(!(FLAG))
#define ASSERT_EQ(T, U) assert((T) == (U))
#define ASSERT_NE(T, U) assert((T) != (U))
#define ASSERT_LT(T, U) assert((T) < (U))
#define ASSERT_GT(T, U) assert((T) > (U))
#define ASSERT_LE(T, U) assert((T) <= (U))
#define ASSERT_GE(T, U) assert((T) >= (U))

#define ASSERT_EQ_ARRAY(A, B) do { \
    ASSERT_EQ(A.size(), B.size()); \
    for(size_t i = 0; i < A.size(); ++i) { \
        ASSERT_EQ(A[i], B[i]); \
    } \
} while(0)

#define RUN_HERE() assert(true)

// a macro to print succuss sysbol
#define RESET "\033[0m"
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */

#define TEST_BEGIN(MODULE) do { \
    thor::print(GREEN, "[----- Test ", #MODULE, " -----] Begin!", RESET); \
} while(0)

#define TEST_SUCCESS(MODULE) do { \
    thor::print(GREEN, "[----- Test ", #MODULE, " -----] Successful!", RESET); \
} while(0)

#endif /*THOR_TEST_HELP_FUNCTION_H_*/