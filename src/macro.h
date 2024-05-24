#ifndef __MACRO_H__
#define __MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define COSERVER_LIKELY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define COSERVER_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define COSERVER_LIKELY(x)      (x)
#   define COSERVER_UNLIKELY(x)      (x)
#endif

#define COSERVER_ASSERT(x)  \
    if(!(x)){   \
        COSERVER_LOG_ERROR(COSERVER_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << coServer::BacktraceToString(100, 2, "    "); \
        assert(x);  \
    }

#define COSERVER_ASSERT2(x, w)  \
    if(!(x)){   \
        COSERVER_LOG_ERROR(COSERVER_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w    \
            << "\nbacktrace:\n" \
            << coServer::BacktraceToString(100, 2, "    "); \
        assert(x);  \
    }
#endif