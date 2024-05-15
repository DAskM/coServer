#include <iostream>
#include "../src/log.h"

int main(){
    coServer::Logger::ptr logger(new coServer::Logger);
    logger->addAppender(coServer::LogAppender::ptr(new coServer::StdoutLogAppender));

    coServer::LogEvent::ptr event(new coServer::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));

    logger->log(coServer::LogLevel::DEBUG, event);

    std::cout << "this is new log!" << std::endl;
    return 0;
}
