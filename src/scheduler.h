#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <memory>
#include <vector>
#include <list>
#include <iostream>

#include "fiber.h"
#include "thread.h"

namespace coServer{

// 协程调度器，相当于一个协程池
class Scheduler{
public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    /**
     * 调度器构造函数
     * threads：线程数
     * use_caller:调度器协程是否加入协程池
     * name：协程池命名
    */
    Scheduler(size_t threads=1, bool use_caller=true, const std::string& name="");

    virtual ~Scheduler();

    const std::string& getName() const {return m_name;}

    // 获取当前协程调度器
    static Scheduler* GetThis();

    // 获取协程调度器的主协程
    static Fiber* GetMainFiber();

    // 启动协程调度器
    void start();

    // 停止协程调度器
    void stop();

    // 调度函数
    template<class FiberOrCb>
    void schedule(FiberOrCb fc, int thread = -1){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            need_tickle = scheduleNoLock(fc, thread);
        }
        if(need_tickle){
            // 当协程池不为空时，通知线程从任务队列中取任务执行
            tickle();
        }
    }

    template<class InputIterator>
    void schedule(InputIterator begin, InputIterator end){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            while(begin != end){
                need_tickle = scheduleNoLock(&*begin, -1) || need_tickle;
                ++begin;
            }
        }
        if(need_tickle){
            tickle();
        }
    }

protected:
    virtual void tickle();

    void run();
    
    virtual bool stopping();

    virtual void idle();

    void setThis();

    bool hasIdleThreads(){return m_idleThreadCount > 0;}

private:
    // 无锁调度任务：将任务对象添加到任务列表中
    template<class FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc, int thread){
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc, thread);
        if(ft.fiber || ft.cb){
            m_fibers.push_back(ft);
        }
        return need_tickle;
    }

private:
    // 任务类，将协程与执行协程的线程封装在一起
    struct FiberAndThread{
        // 任务可以是协程对象
        Fiber::ptr fiber;
        // 任务可以是函数对象
        std::function<void()> cb;
        int thread;

        FiberAndThread(Fiber::ptr f, int thr)
            :fiber(f), thread(thr){}
        
        FiberAndThread(std::function<void()> f, int thr)
            :cb(f), thread(thr){}

        FiberAndThread(std::function<void()>* f, int thr)
            :thread(thr){
            cb.swap(*f);
        }

        FiberAndThread()
            :thread(-1){}

        // 任务对象重置
        void reset(){
            fiber = nullptr;
            cb = nullptr;
            thread = -1;
        }
    };

private:
    MutexType m_mutex;
    // 线程池：用来执行函数
    std::vector<Thread::ptr> m_threads;
    // 任务池：封装携程对象，记录任务
    std::list<FiberAndThread> m_fibers;
    // 记录调度器的主协程
    Fiber::ptr m_rootFiber;
    std::string m_name;
protected:
    std::vector<int> m_threadIds;
    size_t m_threadCount = 0;
    // 正在工作的线程数
    std::atomic<size_t> m_activeThreadCount = {0};
    // 处于等待的线程数
    std::atomic<size_t> m_idleThreadCount = {0};
    bool m_stopping = true;
    bool m_autoStop = false;
    int m_rootThread = 0;
};

}

#endif