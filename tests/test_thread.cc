#include "../src/config.h"
#include "../src/log.h"
#include "../src/singleton.h"
#include "../src/util.h"
#include "../src/thread.h"
#include "../src/mutex.h"

coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();

void fun1(){
    COSERVER_LOG_INFO(g_logger) << "name: " << coServer::Thread::GetName()
        << " this.name: " << coServer::Thread::GetThis()->getName()
        << " id: " << coServer::GetThreadId()
        << " this.id: " << coServer::Thread::GetThis()->getId();
}

int main(int argc, char** argv){
    COSERVER_LOG_INFO(g_logger) << "thread test begin";
    std::vector<coServer::Thread::ptr> thrs;
    for(int i=0; i<5; i++){
        coServer::Thread::ptr thr(new coServer::Thread(&fun1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }
    for(int i=0; i<5; i++){
        thrs[i]->join();
    }
    COSERVER_LOG_INFO(g_logger) << "thread test end";
    return 0;
}