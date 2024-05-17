#ifndef __UTIL_H__
#define __UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

namespace coServer{
    pid_t GetThreadId();

    uint32_t GetFiberId();
}

#endif