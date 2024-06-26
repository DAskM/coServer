#ifndef __COSERVER_LOG__
#define __COSERVER_LOG__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include <map>
#include <yaml-cpp/yaml.h>

#include "util.h"
#include "singleton.h"
#include "thread.h"

#define COSERVER_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        coServer::LogEventWrap(coServer::LogEvent::ptr(new coServer::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, coServer::GetThreadId(),\
                coServer::GetFiberId(), time(0), coServer::Thread::GetName()))).getSS()

#define COSERVER_LOG_DEBUG(logger) COSERVER_LOG_LEVEL(logger, coServer::LogLevel::DEBUG)

#define COSERVER_LOG_INFO(logger) COSERVER_LOG_LEVEL(logger, coServer::LogLevel::INFO)

#define COSERVER_LOG_WARN(logger) COSERVER_LOG_LEVEL(logger, coServer::LogLevel::WARN)

#define COSERVER_LOG_ERROR(logger) COSERVER_LOG_LEVEL(logger, coServer::LogLevel::ERROR)

#define COSERVER_LOG_FATAL(logger) COSERVER_LOG_LEVEL(logger, coServer::LogLevel::FATAL)

#define COSERVER_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        coServer::LogEventWrap(coServer::LogEvent::ptr(new coServer::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, coServer::GetThreadId(),\
                coServer::GetFiberId(), time(0), coServer::Thread::GetName()))).getEvent()->format(fmt, __VA_ARGS__)


#define COSERVER_LOG_FMT_DEBUG(logger, fmt, ...) COSERVER_LOG_FMT_LEVEL(logger, coServer::LogLevel::DEBUG, fmt, __VA_ARGS__)

#define COSERVER_LOG_FMT_INFO(logger, fmt, ...)  COSERVER_LOG_FMT_LEVEL(logger, coServer::LogLevel::INFO, fmt, __VA_ARGS__)

#define COSERVER_LOG_FMT_WARN(logger, fmt, ...)  COSERVER_LOG_FMT_LEVEL(logger, coServer::LogLevel::WARN, fmt, __VA_ARGS__)

#define COSERVER_LOG_FMT_ERROR(logger, fmt, ...) COSERVER_LOG_FMT_LEVEL(logger, coServer::LogLevel::ERROR, fmt, __VA_ARGS__)

#define COSERVER_LOG_FMT_FATAL(logger, fmt, ...) COSERVER_LOG_FMT_LEVEL(logger, coServer::LogLevel::FATAL, fmt, __VA_ARGS__)

#define COSERVER_LOG_ROOT() coServer::LoggerMgr::GetInstance()->getRoot()

#define COSERVER_LOG_NAME(name) coServer::LoggerMgr::GetInstance()->getLogger(name)


namespace coServer{

class Logger;
class LoggerManager;

class LogLevel {
public:
    enum Level{
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    // 将日志级别转成文本输出
    static const char* ToString(LogLevel::Level level);
    // 将文本转成日志级别
    static LogLevel::Level FromString(const std::string& str);
};

class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
        ,const char* file, int32_t line, uint32_t elapse
        ,uint32_t thread_id, uint32_t fiber_id
        ,uint64_t time, const std::string& thread_name);
    
    const char* getFile() const {return m_file;}

    int32_t getLine() const {return m_line;}

    uint32_t getElapse() const {return m_elapse;}

    uint32_t getThreadId() const {return m_threadId;}

    uint32_t getFiberId() const {return m_fiberId;}

    uint64_t getTime() const {return m_time;}

    const std::string& getThreadName() const {return m_threadName;}

    std::string getContent() const {return m_ss.str();}

    std::shared_ptr<Logger> getLogger() const {return m_logger;}

    LogLevel::Level getLevel() const {return m_level;}

    std::stringstream& getSS() {return m_ss;}

    void format(const char* fmt, ...);

    void format(const char* fmt, va_list al);
private:
    const char* m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time = 0;
    std::string m_threadName;
    std::stringstream m_ss;
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e);

    ~LogEventWrap();

    LogEvent::ptr getEvent() const {return m_event;}

    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};

class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    void init();

    bool isError() const {return m_error;}

    const std::string getPattern() const {return m_pattern;}

public:
    class FormatItem {
    public: 
        typedef std::shared_ptr<FormatItem> ptr;
    
        virtual ~FormatItem() {}
    
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};

class LogAppender {
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef SpinLock MutexType;

    virtual ~LogAppender() {}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

    virtual std::string toYamlString() = 0;

    void setFormatter(LogFormatter::ptr val);

    LogFormatter::ptr getFormatter();

    LogLevel::Level getLevel() const {return m_level;}

    void setLevel(LogLevel::Level val) {m_level = val;}
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    bool m_hasFormatter = false;
    MutexType m_mutex;
    LogFormatter::ptr m_formatter;
};

class Logger : public std::enable_shared_from_this<Logger>{
friend class LoggerManager;
public:
    typedef std::shared_ptr<Logger> ptr;
    typedef SpinLock MutexType;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);

    void info(LogEvent::ptr event);

    void warn(LogEvent::ptr event);

    void error(LogEvent::ptr event);

    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);

    void delAppender(LogAppender::ptr appender);

    void clearAppenders();

    LogLevel::Level getLevel() const {return m_level;}

    void setLevel(LogLevel::Level val) {m_level = val;}

    const std::string& getName() const {return m_name;}

    void setFormatter(LogFormatter::ptr val);

    void setFormatter(const std::string& val);

    LogFormatter::ptr getFormatter();

    std::string toYamlString();
private:
    std::string m_name;
    LogLevel::Level m_level;
    MutexType m_mutex;
    std::list<LogAppender::ptr> m_appenders;
    LogFormatter::ptr m_formatter;
    Logger::ptr m_root; 
};

class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

    std::string toYamlString() override;
};

class FileLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender(const std::string& filename);

    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

    std::string toYamlString() override;

    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
    uint64_t m_lastTime = 0;
};

class LoggerManager{
public:
    typedef SpinLock MutexType;

    LoggerManager();

    Logger::ptr getLogger(const std::string& name);

    void init();

    Logger::ptr getRoot() const {return m_root;}

    std::string toYamlString();
private:
    MutexType m_mutex;
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

// 日志管理类单例模式
typedef coServer::Singleton<LoggerManager> LoggerMgr;

}

#endif