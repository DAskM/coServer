#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

/**
 *  基于Epoll的IO协程调度器
*/
#include "scheduler.h"
#include "timer.h"

namespace coServer{

class IOManager : public Scheduler, public TimerManager{
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;
    
    // IO事件
    enum Event{
        NONE = 0x0,
        READ = 0x1,
        WRITE = 0x4
    };

private:
    // 事件上下文类(与一个文件描述符 fd 一一对应)
    struct FdContext{
        typedef Mutex MutexType;
        // 事件上下文
        struct EventContext{
            Scheduler* scheduler = nullptr; // 事件执行的调度器
            Fiber::ptr fiber;               // 事件协程
            std::function<void()> cb;       // 事件回调函数
        };

        // 获取事件上下文
        EventContext& getContext(Event event);
        
        // 重置事件上下文
        void resetContext(EventContext& ctx);

        // 触发事件
        void triggerEvent(Event event);

        // 读事件上下文
        EventContext read;
        // 写事件上下文
        EventContext write;
        // 事件关联的句柄（文件描述符）
        int fd = 0;
        // 已经注册的事件
        Event events = NONE;
        // 事件的锁
        MutexType mutex;
    };

public:
    IOManager(size_t threads = 1, bool use_caller = true, const std::string& name = "");

    ~IOManager();

    /**
     *  添加事件
     * fd ：socket句柄（文件描述符句柄）
     * event ： 事件类型
     * cb ： 事件回调函数
    */
    int addEvent(int fd, Event event, std::function<void()> cb=nullptr);

    bool delEvent(int fd, Event event);

    bool cancelEvent(int fd, Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();

protected:
    void tickle() override;

    bool stopping() override;

    void idle() override;

    // 重置socket句柄上下文的容器大小
    void contextResize(size_t size);

    bool stopping(uint64_t& timeout);

    void onTimerInsertedAtFront() override;
private:
    int m_epfd = 0;         // epoll 文件句柄
    int m_tickleFds[2];     // pipe 文件句柄
    std::atomic<size_t> m_pendingEventCount = {0};      // 当前等待执行的事件数量
    RWMutexType m_mutex;    // IOManager 的读写锁
    std::vector<FdContext*> m_fdContexts;               // 调度器监听的socket事件上下文数组
};

}

#endif