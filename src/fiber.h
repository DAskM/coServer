#ifndef __FIBER_H__
#define __FIBER_H__

#include <memory>
#include <functional>
#include <ucontext.h>

namespace coServer{

class Scheduler;

class Fiber : public std::enable_shared_from_this<Fiber>{
friend class Scheduler;
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State{
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };

private:
    // 无参构造函数，每个线程的第一个协程（0号协程，调度协程，主协程）
    Fiber();

public:
    Fiber(std::function<void()> cb, size_t stacksize = 0, bool use_caller = false);
    ~Fiber();

    // 重置协程函数，并重置状态
    void reset(std::function<void()> cb);

    // 由非主协程调用，使线程执行对象协程封装的函数
    void swapIn();

    // 由非主协程调用，使线程执行主协程封装的调度函数
    void swapOut();

    void call();

    void back();

    // 返回协程对象的状态
    State getState() const {return m_state;}

    // 返回协程对象的协程id
    uint64_t getId() const {return m_id;}

    // 返回当前正在执行的协程对象
    static Fiber::ptr GetThis();

    // 设置线程的主协程（0号协程）
    static void SetThis(Fiber* f);

    // 协程切换到后台，并设置为Ready状态
    static void YieldToReady();

    // 协程写换到后台，并设置为Hold状态
    static void YieldToHold();

    // 获取协程总数 
    static uint64_t TotalFibers();

    // 协程执行函数，执行完返回运行该协程的线程中的主协程（0号协程）
    static void MainFunc();

    // 协程执行函数，执行完成返回到调度器所在线程的主协程
    static void CallerMainFunc();

    // 获取当前运行的协程id
    static uint64_t GetFiberId();
private:
    uint64_t m_id = 0;
    // 协程栈空间大小
    uint32_t m_stacksize = 0;
    // 协程状态
    State m_state = INIT;
    // 协程上下文（CPU信息，寄存器信息）
    ucontext_t m_ctx;
    // 函数栈帧
    void* m_stack = nullptr;
    // 协程工作函数
    std::function<void()> m_cb;
};

}


#endif