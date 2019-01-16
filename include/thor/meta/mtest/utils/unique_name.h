#ifndef THOR_META_MTEST_UTILS_UNIQUE_NAME_H_
#define THOR_META_MTEST_UTILS_UNIQUE_NAME_H_

/**
 * This file define some macro to generate unique string names static
 */
#define __DO_STRINGIZE( symbol ) #symbol
#define _STRINGIZE(symbol) __DO_STRINGIZE(symbol)

// join two symbol, just comcat
#define __DO_JOIN(symbol1, symbol2) symbol1##symbol2
#define _JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)

// get a unique id
#ifdef __COUNTER__
# define UNIQUE_ID __COUNTER__
#else
# define UNIQUE_ID __LINE__
#endif

// the macro to get unique names
#define UNIQUE_NAME(prefix) _JOIN(prefix, UNIQUE_ID)

#endif /*THOR_META_MTEST_UTILS_UNIQUE_NAME_H_*/