#include <atomic>

#include "fiber.h"
#include "config.h"
#include "macro.h"

namespace coServer{

static Logger::ptr g_logger = COSERVER_LOG_NAME("system");

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

// 线程局部变量，指向运行协程（ 和线程绑定的那个主协程）
static thread_local Fiber* t_fiber = nullptr;
// 表示当前运行协程
static thread_local Fiber::ptr t_threadFiber = nullptr;
static ConfigVar<uint32_t>::ptr g_fiber_stack_size = 
    Config::Lookup<uint32_t>("fiber.stack_size", 1024*1024, "fiber stack size");

// 内存配置器，在堆上给协程分配栈zhen
class MallocStackAllocator{
public:
    static void* Alloc(size_t size){
        return malloc(size);
    }

    static void Dealloc(void* vp, size_t size){
        return free(vp);
    }
};

using StackAllocator = MallocStackAllocator;

// 主协程构造函数
Fiber::Fiber(){
    m_state = EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)){
        COSERVER_ASSERT2(false, "getcontext");
    }
    ++s_fiber_count;
    COSERVER_LOG_DEBUG(g_logger) << "Fiber::Fiber";
}

Fiber::Fiber(std::function<void()> cb, size_t stacksize)
    :m_id(++s_fiber_id)
    ,m_cb(cb){

    ++s_fiber_count;
    m_stacksize = stacksize ? stacksize : g_fiber_stack_size->getValue();

    m_stack = StackAllocator::Alloc(m_stacksize);
    if(getcontext(&m_ctx)){
        COSERVER_ASSERT2(false, "getcontext");
    }

    // 协程上下文连接（用户可控的调用链）
    m_ctx.uc_link = nullptr;
    // 配置协程的调用栈
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;
    // 设置协程上下文
    makecontext(&m_ctx, &Fiber::MainFunc, 0);

    COSERVER_LOG_DEBUG(g_logger) << "Fiber::Fiber id=" << m_id;
}

Fiber::~Fiber(){
    --s_fiber_count;
    if(m_stack){
        COSERVER_ASSERT(m_state == TERM || m_state == INIT || m_state == EXCEPT);
        StackAllocator::Dealloc(m_stack, m_stacksize);
    }
    else{
        // 当前析构的协程为主协程
        COSERVER_ASSERT(!m_cb);
        COSERVER_ASSERT(m_state == EXEC);
        
        Fiber* cur = t_fiber;
        if(cur == this){
            SetThis(nullptr);
        }
    }
    COSERVER_LOG_DEBUG(g_logger) << "Fiber::~Fiber id=" << m_id;
}

// 资源复用，将存储上下文的内存绑定到另一个协程上
void Fiber::reset(std::function<void()> cb){
    COSERVER_ASSERT(m_stack);
    COSERVER_ASSERT(m_state == TERM || m_state == INIT || m_state == EXCEPT);
    
    m_cb = cb;
    if(getcontext(&m_ctx)){
        COSERVER_ASSERT2(false, "getcontext");
    }
    // 清除栈帧
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    makecontext(&m_ctx, &Fiber::MainFunc, 0);
}

void Fiber::swapIn(){
    SetThis(this);
    COSERVER_ASSERT(m_state != EXEC);
    m_state = EXEC;
    // 将协程对象的栈帧切换到主协程上
    if(swapcontext(&t_threadFiber->m_ctx, &m_ctx)){
        COSERVER_ASSERT2(false, "swapcontext");
    }
}

void Fiber::swapOut(){
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx, &t_threadFiber->m_ctx)){
        COSERVER_ASSERT2(false, "swapcontext");
    }
}

void Fiber::SetThis(Fiber* f){
    t_fiber = f;
}

Fiber::ptr Fiber::GetThis(){
    if(t_fiber){
        return t_fiber->shared_from_this();
    }
    Fiber::ptr main_fiber(new Fiber);
    COSERVER_ASSERT(t_fiber == main_fiber.get());
    t_threadFiber = main_fiber;
    return t_fiber->shared_from_this();
}

void Fiber::YieldToReady(){
    Fiber::ptr cur = GetThis();
    cur->m_state = READY;
    cur->swapOut();
}

void Fiber::YieldToHold(){
    Fiber::ptr cur = GetThis();
    cur->m_state = HOLD;
    cur->swapOut();
}

uint64_t Fiber::TotalFibers(){
    return s_fiber_count;
}

void Fiber::MainFunc(){
    Fiber::ptr cur = GetThis();
    COSERVER_ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb = nullptr;
        cur->m_state = TERM;
    }catch(std::exception ex){
        cur->m_state = EXCEPT;
        COSERVER_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what();
    }catch(...){
        cur->m_state = EXCEPT;
        COSERVER_LOG_ERROR(g_logger) << "Fiber Except";
    }

    // 从智能指针中提取原始指针
    auto raw_ptr = cur.get();
    cur.reset();
    // 使用原始指针切换协程
    raw_ptr->swapOut();
    COSERVER_ASSERT2(false, "never run here");
}

uint64_t Fiber::GetFiberId(){
    if(t_fiber){
        return t_fiber->getId();
    }
    return 0;
}

}