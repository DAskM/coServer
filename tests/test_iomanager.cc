#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>
#include <string.h>

#include "iomanager.h"
#include "log.h"
#include "scheduler.h"

coServer::Logger::ptr g_logger = COSERVER_LOG_ROOT();

int sock = 0;

void test_fiber(){
    COSERVER_LOG_INFO(g_logger) << "test_fiber sock=" << sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    if(!connect(sock, (const sockaddr*)&addr, sizeof(addr))){

    }
    else if(errno == EINPROGRESS){
        COSERVER_LOG_INFO(g_logger) << "add event errno=" << errno << " "
            << strerror(errno);
        coServer::IOManager::GetThis()->addEvent(sock, coServer::IOManager::READ, [](){
            COSERVER_LOG_INFO(g_logger) << "read callback";
        });
        coServer::IOManager::GetThis()->addEvent(sock, coServer::IOManager::WRITE, [](){
            COSERVER_LOG_INFO(g_logger) << "read callback";
            coServer::IOManager::GetThis()->cancelEvent(sock, coServer::IOManager::READ);
            close(sock);
        });
    }
    else{
        COSERVER_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }
}

void test1(){
    std::cout << "EPOLLIN=" << EPOLLIN
        << " EPOLLOUT=" << EPOLLOUT << std::endl;
    coServer::IOManager iom;
    iom.schedule(&test_fiber);
}

int main(){
    test1();
    return 0;
}