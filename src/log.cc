#include "log.h"

namespace coServer{

const char* LogLevel::ToString(LogLevel::Level level) {
    switch(level) {
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}

Logger::Logger(const std::string& name)
    :m_name(name){}

void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
    for(auto it = m_appenders.begin(); it != m_appenders.end(); ++it){
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        for(auto& i : m_appenders){
            i->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}
void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}
void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
} 

FileLogAppender::FileLogAppender(const std::string& filename)
    :m_filestream(filename){}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level){
        m_filestream << m_formatter->format(level, event);
    }
}

bool FileLogAppender::reopen(){
    if(m_filestream){
        m_filestream.close();
    }
    // m_filestream.open(m_filestream);
    return !!m_filestream;
}

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level){
        std::cout << m_formatter->format(level, event);
    }
}

LogFormatter::LogFormatter(const std::string& pattern)
    :m_pattern(pattern){}

std::string LogFormatter::format(LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for(auto& i : m_items){
        i->format(ss, level, event);
    }
    return ss.str();
}

void LogFormatter::init() {
    //str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;
    std::string nstr;
    for(size_t i = 0; i < m_pattern.size(); ++i) {
        if(m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }

        if((i + 1) < m_pattern.size()) {
            if(m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while(n < m_pattern.size()) {
            if(!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                    && m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if(fmt_status == 0) {
                if(m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    //std::cout << "*" << str << std::endl;
                    fmt_status = 1; //解析格式
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            } else if(fmt_status == 1) {
                if(m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    //std::cout << "#" << fmt << std::endl;
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if(n == m_pattern.size()) {
                if(str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if(fmt_status == 0) {
            if(!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        } else if(fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
//     static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> > s_format_items = {
// #define XX(str, C) \
//         {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}

//         XX(m, MessageFormatItem),           //m:消息
//         XX(p, LevelFormatItem),             //p:日志级别
//         XX(r, ElapseFormatItem),            //r:累计毫秒数
//         XX(c, NameFormatItem),              //c:日志名称
//         XX(t, ThreadIdFormatItem),          //t:线程id
//         XX(n, NewLineFormatItem),           //n:换行
//         XX(d, DateTimeFormatItem),          //d:时间
//         XX(f, FilenameFormatItem),          //f:文件名
//         XX(l, LineFormatItem),              //l:行号
//         XX(T, TabFormatItem),               //T:Tab
//         XX(F, FiberIdFormatItem),           //F:协程id
//         XX(N, ThreadNameFormatItem),        //N:线程名称
// #undef XX
//     };

//     for(auto& i : vec) {
//         if(std::get<2>(i) == 0) {
//             m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
//         } else {
//             auto it = s_format_items.find(std::get<0>(i));
//             if(it == s_format_items.end()) {
//                 m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
//             } else {
//                 m_items.push_back(it->second(std::get<1>(i)));
//             }
//         }

//         //std::cout << "(" << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;
//     }
    //std::cout << m_items.size() << std::endl;
}

LogFormatter::LogFormatter(const std::string& pattern)
    :m_pattern(pattern){}

class MessageFormatItem : public LogFormatter::FormatItem{
public:
    void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem{
public:
    void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override {
        os << LogLevel::ToString(level);
    }
};

}