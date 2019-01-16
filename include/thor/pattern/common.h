#ifndef THOR_PATTERN_COMMON_H_
#define THOR_PATTERN_COMMON_H_

/**
 * the macro of pattern namespace
 */

#define TP_NS thor::pattern

#define TP_NS_BEGIN namespace thor { \
    namespace pattern {

#define TP_NS_END } \
    }

// delete pointers
#define DELETE_POINTER(T) if(T != nullptr) { \
    delete T; \
    T = nullptr; \
}

#endif /*THOR_PATTERN_COMMON_H_*/