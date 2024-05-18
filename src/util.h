#ifndef __UTIL_H__
#define __UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <cxxabi.h>

namespace coServer{
pid_t GetThreadId();

uint32_t GetFiberId();

template<class T>
const char* TypeToName() {
    static const char* s_name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    return s_name;
}
}

#endif