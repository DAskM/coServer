#include "../src/config.h"
#include "../src/log.h"
#include "../src/singleton.h"
#include "../src/util.h"
#include "../src/thread.h"
#include "../src/mutex.h"

#include <iostream>

coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();

int count = 0;
coServer::Mutex s_mutex;

void func1(){
    COSERVER_LOG_INFO(g_logger) << "name: " << coServer::Thread::GetName()
        << " this.name: " << coServer::Thread::GetThis()->getName()
        << " id: " << coServer::GetThreadId()
        << " this.id: " << coServer::Thread::GetThis()->getId();
    
    for(int i=0; i<1000; ++i){
        coServer::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void func2(){
    while(true){
        COSERVER_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void func3(){
    while(true) {
        COSERVER_LOG_INFO(g_logger) << "-----------------------";
    }
}

int main(int argc, char** argv){
    COSERVER_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/leedong/Desktop/Project/conServer/tests/log.yml");
    coServer::Config::LoadFromYaml(root);

    std::vector<coServer::Thread::ptr> thrs;
    for(int i=0; i<5; ++i){
        coServer::Thread::ptr thr(new coServer::Thread(&func1, "name_"+std::to_string(i*2)));
        thrs.push_back(thr);
    }

    for(int i=0; i<5; ++i){
        thrs[i]->join();
    }

    COSERVER_LOG_INFO(g_logger) << "thread test end";
    COSERVER_LOG_INFO(g_logger) << "count=" << count;

    
    return 0;
}