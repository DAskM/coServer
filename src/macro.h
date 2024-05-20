#ifndef __MACRO_H__
#define __MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"

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