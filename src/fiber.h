#ifndef __FIBER_H__
#define __FIBER_H__

#include <ucontext.h>
#include <functional>
#include "thread.h"

namespace coServer{

class Fiber : public std::enable_shared_from_this<Fiber>{
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

public:
    Fiber();
    Fiber(std::function<void()> cb, size_t stacksize = 0);
    ~Fiber();

    // 重置协程函数，并重置状态
    void reset(std::function<void()> cb);

    // 切换到当前协程执行
    void swapIn();

    // 切换到后台执行
    void swapOut();

    uint64_t getId() const {return m_id;}

    // 返回当前协程
    static Fiber::ptr GetThis();

    // 设置当前协程
    static void SetThis(Fiber* f);

    // 协程切换到后台，并设置为Ready状态
    static void YieldToReady();

    // 协程写换到后台，并设置为Hold状态
    static void YieldToHold();

    // 获取协程总数 
    static uint64_t TotalFibers();

    static void MainFunc();

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