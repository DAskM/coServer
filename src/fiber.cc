#include <atomic>

#include "fiber.h"
#include "config.h"
#include "macro.h"
#include "scheduler.h"

namespace coServer{

static Logger::ptr g_logger = COSERVER_LOG_NAME("system");

// 记录当前线程下协程id编号（递增）
static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

// 表示当前线程中所运行的协程
static thread_local Fiber* t_fiber = nullptr;
// 线程局部变量，指向运行协程（ 和线程绑定的那个主协程）
static thread_local Fiber::ptr t_threadFiber = nullptr;
static ConfigVar<uint32_t>::ptr g_fiber_stack_size = 
    Config::Lookup<uint32_t>("fiber.stack_size", 128*1024, "fiber stack size");

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
    // 把构造的新Fiber对象作为该线程的主协程
    SetThis(this);

    if(getcontext(&m_ctx)){
        COSERVER_ASSERT2(false, "getcontext");
    }
    ++s_fiber_count;
    COSERVER_LOG_DEBUG(g_logger) << "Fiber::Fiber";
}

// 暴露给用户的协程构造函数
Fiber::Fiber(std::function<void()> cb, size_t stacksize, bool use_caller)
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

    if(!use_caller){
        makecontext(&m_ctx, &Fiber::MainFunc, 0);
    }
    else{
        makecontext(&m_ctx, &Fiber::CallerMainFunc, 0);
    }
    
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
    m_state = INIT;
}

void Fiber::call(){
    SetThis(this);
    m_state = EXEC;
    if(swapcontext(&t_threadFiber->m_ctx, &m_ctx)){
        COSERVER_ASSERT2(false, "swapcontext");
    }
}

void Fiber::back(){
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx, &t_threadFiber->m_ctx)){
        COSERVER_ASSERT2(false, "swapcontext");
    }
}

void Fiber::swapIn(){
    SetThis(this);
    COSERVER_ASSERT(m_state != EXEC);
    m_state = EXEC;
    // 将调度器主协程对象的栈帧切换到主协程上
    if(swapcontext(&Scheduler::GetMainFiber()->m_ctx, &m_ctx)){
        COSERVER_ASSERT2(false, "swapcontext");
    }
}

void Fiber::swapOut(){
    SetThis(t_threadFiber.get());
    // 切换为调度器主协程对象的栈帧
    if(swapcontext(&m_ctx, &Scheduler::GetMainFiber()->m_ctx)){
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
    }catch(std::exception& ex){
        cur->m_state = EXCEPT;
         COSERVER_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what()
            << " fiber_id=" << cur->getId()
            << std::endl
            << coServer::BacktraceToString();
    }catch(...){
        cur->m_state = EXCEPT;
        COSERVER_LOG_ERROR(g_logger) << "Fiber Except"
            << " fiber_id=" << cur->getId()
            << std::endl
            << coServer::BacktraceToString();
    }

    // 从智能指针中提取原始指针
    auto raw_ptr = cur.get();
    cur.reset();
    // 使用原始指针切换协程
    raw_ptr->swapOut();
    COSERVER_ASSERT2(false, "never reach fiber_id=" + std::to_string(raw_ptr->getId()));
}

uint64_t Fiber::GetFiberId(){
    if(t_fiber){
        return t_fiber->getId();
    }
    return 0;
}

void Fiber::CallerMainFunc(){
    Fiber::ptr cur = GetThis();
    COSERVER_ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb = nullptr;
        cur->m_state = TERM;
    }catch(std::exception& ex){
        cur->m_state = EXCEPT;
        COSERVER_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what()
            << " fiber_id=" << cur->getId()
            << std::endl
            << coServer::BacktraceToString();
    }catch(...){
        cur->m_state = EXCEPT;
        COSERVER_LOG_ERROR(g_logger) << "Fiber Except: "
            << " fiber_id=" << cur->getId()
            << std::endl
            << coServer::BacktraceToString();
    }
    auto raw_ptr = cur.get();
    cur.reset();
    raw_ptr->back();
    COSERVER_ASSERT2(false, "never reach fiber_id=" + std::to_string(raw_ptr->getId()));
}

}