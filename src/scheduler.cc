#include "scheduler.h"
#include "log.h"
#include "macro.h"
#include "config.h"
#include "hook.h"

namespace coServer{
    
static Logger::ptr g_logger = COSERVER_LOG_NAME("system");

// 线程局部变量，记录协程调度器
static thread_local Scheduler* t_scheduler = nullptr;
// 记录协程调度器正在执行的协程
static thread_local Fiber* t_scheduler_fiber = nullptr;

Scheduler::Scheduler(size_t threads, bool use_caller, const std::string& name)
    :m_name(name){
    COSERVER_ASSERT(threads > 0);

    if(use_caller){
        // 为协程调度器创建主协程
        coServer::Fiber::GetThis();
        --threads;

        COSERVER_ASSERT(GetThis() == nullptr);
        t_scheduler = this;

        // 初始化调度器主协程的任务
        m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));
        coServer::Thread::SetName(m_name);
        t_scheduler_fiber = m_rootFiber.get();
        m_rootThread = coServer::GetThreadId();
        m_threadIds.push_back(m_rootThread);
    }else{
        m_rootThread = -1;
    }
    m_threadCount = threads;
}

Scheduler::~Scheduler(){
    COSERVER_ASSERT(m_stopping);
    if(GetThis() == this){
        t_scheduler = nullptr;
    }
}

Scheduler* Scheduler::GetThis(){
    return t_scheduler;
}

Fiber* Scheduler::GetMainFiber(){
    return t_scheduler_fiber;
}

void Scheduler::start(){
    MutexType::Lock lock(m_mutex);
    if(!m_stopping){
        return;
    }
    m_stopping = false;
    COSERVER_ASSERT(m_threads.empty());
    m_threads.resize(m_threadCount);
    
    for(size_t i=0; i<m_threadCount; i++){
        // 创建线程
        m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this), m_name + "_" + std::to_string(i)));
        m_threadIds.push_back(m_threads[i]->getId());
    }
    lock.unlock();
}

void Scheduler::stop(){
    m_autoStop = true;
    if(m_rootFiber
        && m_threadCount == 0
        && (m_rootFiber->getState() == Fiber::TERM
            || m_rootFiber->getState() == Fiber::INIT)){
        COSERVER_LOG_INFO(g_logger) << this << " stopped";
        m_stopping = true;

        if(stopping()){
            return;
        }
    }
    if(m_rootThread != -1){
        COSERVER_ASSERT(GetThis() == this);
    }
    else{
        // 调度器所在线程没有加入到线程池中
        COSERVER_ASSERT(GetThis() != this);
    }

    m_stopping = true;
    for(size_t i=0; i<m_threadCount; ++i){
        tickle();
    }
    if(m_rootFiber){
        tickle();
    }
    if(m_rootFiber){
        // 调度器线程也加入到线程池中的情况下
        if(!stopping()){
            m_rootFiber->call();
        }
    }

    std::vector<Thread::ptr> thrs;
    {
        MutexType::Lock lock(m_mutex);
        thrs.swap(m_threads);
    }

    for(auto& i : thrs){
        i->join();
    }
}

void Scheduler::setThis(){
    t_scheduler = this;
}

void Scheduler::run() {
    COSERVER_LOG_DEBUG(g_logger) << m_name << " run";
    set_hook_enable(true);
    setThis();
    if(coServer::GetThreadId() != m_rootThread) {
        t_scheduler_fiber = Fiber::GetThis().get();
    }

    Fiber::ptr idle_fiber(new Fiber(std::bind(&Scheduler::idle, this)));
    Fiber::ptr cb_fiber;

    FiberAndThread ft;
    while(true) {
        ft.reset();
        bool tickle_me = false;
        bool is_active = false;
        {
            MutexType::Lock lock(m_mutex);
            auto it = m_fibers.begin();
            while(it != m_fibers.end()) {
                if(it->thread != -1 && it->thread != coServer::GetThreadId()) {
                    ++it;
                    tickle_me = true;
                    continue;
                }

                COSERVER_ASSERT(it->fiber || it->cb);
                if(it->fiber && it->fiber->getState() == Fiber::EXEC) {
                    ++it;
                    continue;
                }

                ft = *it;
                m_fibers.erase(it++);
                ++m_activeThreadCount;
                is_active = true;
                break;
            }
            tickle_me |= it != m_fibers.end();
        }

        if(tickle_me) {
            tickle();
        }

        if(ft.fiber && (ft.fiber->getState() != Fiber::TERM
                        && ft.fiber->getState() != Fiber::EXCEPT)) {
            ft.fiber->swapIn();
            --m_activeThreadCount;

            if(ft.fiber->getState() == Fiber::READY) {
                schedule(ft.fiber);
            } else if(ft.fiber->getState() != Fiber::TERM
                    && ft.fiber->getState() != Fiber::EXCEPT) {
                ft.fiber->m_state = Fiber::HOLD;
            }
            ft.reset();
        } else if(ft.cb) {
            if(cb_fiber) {
                cb_fiber->reset(ft.cb);
            } else {
                cb_fiber.reset(new Fiber(ft.cb));
            }
            ft.reset();
            cb_fiber->swapIn();
            --m_activeThreadCount;
            if(cb_fiber->getState() == Fiber::READY) {
                schedule(cb_fiber);
                cb_fiber.reset();
            } else if(cb_fiber->getState() == Fiber::EXCEPT
                    || cb_fiber->getState() == Fiber::TERM) {
                cb_fiber->reset(nullptr);
            } else {//if(cb_fiber->getState() != Fiber::TERM) {
                cb_fiber->m_state = Fiber::HOLD;
                cb_fiber.reset();
            }
        } else {
            if(is_active) {
                --m_activeThreadCount;
                continue;
            }
            if(idle_fiber->getState() == Fiber::TERM) {
                COSERVER_LOG_INFO(g_logger) << "idle fiber term";
                break;
            }

            ++m_idleThreadCount;
            idle_fiber->swapIn();
            --m_idleThreadCount;
            if(idle_fiber->getState() != Fiber::TERM
                    && idle_fiber->getState() != Fiber::EXCEPT) {
                idle_fiber->m_state = Fiber::HOLD;
            }
        }
    }
}

void Scheduler::tickle(){
    COSERVER_LOG_INFO(g_logger) << "tickle";
}

bool Scheduler::stopping(){
    MutexType::Lock lock(m_mutex);
    return m_autoStop && m_stopping && m_fibers.empty() && m_activeThreadCount == 0;
}

void Scheduler::idle(){
    COSERVER_LOG_INFO(g_logger) << "idle";
    // 当协程调度器没有停止时，将当前正在执行的协程设为HOLD状态
    while(!stopping()){
        coServer::Fiber::YieldToHold();
    }
}

}