#include <assert.h>
#include <iostream>

#include "log.h"
#include "macro.h"

coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();

void test_assert(){
    COSERVER_LOG_INFO(g_logger) << coServer::BacktraceToString(10);
    COSERVER_ASSERT(1);
}

int main(int argc, char** argv){

    // assert(0);

    test_assert();
    
    return 0;
}