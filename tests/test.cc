#include <iostream>
#include "../src/log.h"

int main(){
    coServer::Logger::ptr logger(new coServer::Logger);
    logger->addAppender(coServer::LogAppender::ptr(new coServer::StdoutLogAppender));

    coServer::FileLogAppender::ptr file_appender(new coServer::FileLogAppender("./log.txt"));
    coServer::LogFormatter::ptr fmt(new coServer::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(coServer::LogLevel::ERROR);

    logger->addAppender(file_appender);


    std::cout << "this is new log!" << std::endl;
    return 0;
}
