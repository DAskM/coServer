#include "log.h"
#include "scheduler.h"

static coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();

void test_fiber(){
    static int s_count = 5;
    COSERVER_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;
    sleep(1);

    if(--s_count >= 0){
        coServer::Scheduler::GetThis()->schedule(&test_fiber, coServer::GetThreadId());
    }
}

int main(){
    COSERVER_LOG_INFO(g_logger) << "main";
    coServer::Scheduler sc(3, true, "test");
    sc.start();
    sleep(2);

    COSERVER_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    COSERVER_LOG_INFO(g_logger) << "over";
    return 0;
}