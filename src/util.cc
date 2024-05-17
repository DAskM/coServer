#include <execinfo.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#include "util.h"
#include "log.h"

namespace coServer{
    
pid_t GetThreadId(){
    return 0;
}

uint32_t GetFiberId(){
    return 0;
}

}