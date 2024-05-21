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

int main(){
    coServer::Fiber::GetThis();
    COSERVER_LOG_INFO(g_logger) << "main begin";
    coServer::Fiber::ptr fiber(new coServer::Fiber(run_in_fiber));
    fiber->swapIn();
    COSERVER_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
    COSERVER_LOG_INFO(g_logger) << "main after ed";
    return 0;
}