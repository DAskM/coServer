#ifndef __UTIL_H__
#define __UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <cxxabi.h>
#include <string>
#include <sys/types.h>
#include <sys/syscall.h>
#include <vector>

namespace coServer{
pid_t GetThreadId();

uint32_t GetFiberId();

// 获取调用栈信息
void Backtrace(std::vector<std::string>& bt, int size=64, int skip=1);

std::string BacktraceToString(int size=64, int skip=2, const std::string& prefix="    ");

template<class T>
const char* TypeToName() {
    static const char* s_name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    return s_name;
}
}

#endif