#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <sstream>
#include <memory>
#include <stdint.h>
#include <list>
#include <vector>
#include <stdarg.h>

namespace coServer {
class Logger;
class LoggerManager;

// 日志级别
class LogLevel{
public:
    enum Level{
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    // 将日志级别信息转成文本输出
    static const char* ToString(LogLevel::Level level);

    static LogLevel::Level FromString(const std::string& str);
};

// 日志事件
class LogEvent {
public:
    // 对外提供类的智能指针
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level m_level
        ,const char* file, int32_t line, uint32_t m_elapse
        ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
        ,const std::string& thread_name);
    
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

    // 接受可变数量的参数
    void format(const char* fmt, ...);

    // 接受可变参列表
    void format(const char* fmt, va_list al);

private:
    const char* m_file = nullptr;   // 文件名
    int32_t m_line = 0;             // 行号
    uint32_t m_elapse = 0;          // 程序启动到现在的毫秒数
    uint32_t m_threadId = 0;        // 线程ID
    uint32_t m_fiberId = 0;         // 协程ID
    uint64_t m_time = 0;            // 时间戳
    std::string m_threadName;       // 线程名
    std::stringstream m_ss;         // 日志流
    std::shared_ptr<Logger> m_logger;   // 日志器
    LogLevel::Level m_level;        // 日志级别      
};

// 日志事件封装器
class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr e);

    ~LogEventWrap();

    // 获取日志事件
    LogEvent::ptr getEvent() const {return m_event;}

    // 获取日志内容流
    std::stringstream& getSS();
private:
    // 日志事件的指针
    LogEvent::ptr m_event;
};

class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    /**
     *  %m 消息
     *  %p 日志级别
     *  %r 累计毫秒数
     *  %c 日志名称
     *  %t 线程id
     *  %n 换行
     *  %d 时间
     *  %f 文件名
     *  %l 行号
     *  %T 制表符
     *  %F 协程id
     *  %N 线程名称
     *
     *  默认格式 "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"
     */
    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        
        // 析构函数定义为虚函数，避免继承对象无法释放资源
        virtual ~FormatItem(){}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> Logger
            ,LogLevel::Level level, LogEvent::ptr event) = 0;
    };
    // 初始化，解析日志模板
    void init();
    // 判断是否有误
    bool isError() const {return m_error;}
    // 返回日志模板
    const std::string getPattern() const {return m_pattern;}  
private:
    // 日志格式模板
    std::string m_pattern;
    // 日志格式解析后格式
    std::vector<FormatItem::ptr> m_items;
    // 错误标识符
    bool m_error = false;
};

class Logger {

};


}

#endif