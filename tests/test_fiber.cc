#include "log.h"
#include "fiber.h"
#include "util.h"
#include "macro.h"
#include "config.h"

coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();


void run_in_fiber(){
    COSERVER_LOG_INFO(g_logger) << "run_in_fiber begin";
    coServer::Fiber::GetThis()->YieldToHold();
    COSERVER_LOG_INFO(g_logger) << "run_in_fiber end";
    coServer::Fiber::GetThis()->YieldToHold();
}

void test_fiber(){
    COSERVER_LOG_INFO(g_logger) << "main begin -1";
    {
        coServer::Fiber::GetThis();
        COSERVER_LOG_INFO(g_logger) << "main begin";
        coServer::Fiber::ptr fiber(new coServer::Fiber(run_in_fiber));
        fiber->swapIn();
        COSERVER_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        COSERVER_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    COSERVER_LOG_INFO(g_logger) << "main after end2";
}

int main(){
    coServer::Thread::SetName("main");
    std::vector<coServer::Thread::ptr> thrs;
    for(int i=0; i<3; ++i){
        thrs.push_back(coServer::Thread::ptr(
            new coServer::Thread(&test_fiber, "name_"+std::to_string(i))));
    }
    for(auto i : thrs){
        i->join();
    }
    return 0;
}