#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <atomic>
#include <list>
#include <sstream>

#include "noncopyable.h"

namespace coServer{

class Semaphore : Noncopyable{
public:
    // 初始化信号量
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    // 获取信号量
    void wait();
    // 释放信号量
    void notify();
private:
    sem_t m_semaphore;
};

// 局部锁
template<class T>
struct ScopedLockImpl{
public:
    ScopedLockImpl(T& mutex)
        :m_mutex(mutex){
        m_mutex.lock();
        m_locked = true;
    }
    
    ~ScopedLockImpl(){
        unlock();
    }

    // 加锁
    void lock(){
        if(!m_locked){
            m_mutex.lock();
            m_locked = true;
        }
    }

    // 解锁
    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    // 是否已经上锁
    bool m_locked;
};

// 局部读锁模板
template<class T>
struct ReadScopeLockImpl{
public:
    ReadScopeLockImpl(T& mutex)
        :m_mutex(mutex){
        m_mutex.rdlock();
        m_locked = true;
    }
    ~ReadScopeLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.rdlock();
            m_locked = true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    bool m_locked;
};

// 局部写锁模板
template<class T>
struct WriteScopedLockImpl{
public:
    WriteScopedLockImpl(T& mutex)
        :m_mutex(mutex){
        m_mutex.wrlock();
        m_locked = true;
    }
    ~WriteScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.wrlock();
            m_locked = true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    bool m_locked;
};

// 互斥量
class Mutex : Noncopyable{
public:
    // 局部锁
    typedef ScopedLockImpl<Mutex> Lock;

    Mutex() {
        pthread_mutex_init(& m_mutex, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock(){
        pthread_mutex_lock(&m_mutex);
    }

    void unlock(){
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};

class NullMutex : Noncopyable{
public:
    typedef ScopedLockImpl<NullMutex> Lock;
    NullMutex(){}

    ~NullMutex(){}

    void lock(){}

    void unlock(){}
};

// 读写互斥量
class RWMutex : Noncopyable{
public:
    // 局部读锁
    typedef ReadScopeLockImpl<RWMutex> ReadLock;
    // 局部写锁
    typedef WriteScopedLockImpl<RWMutex> WriteLock;

    RWMutex(){
        pthread_rwlock_init(&m_lock, nullptr);
    }

    ~RWMutex(){
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock(){
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock(){
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock(){
        pthread_rwlock_unlock(&m_lock);
    }
private:
    // 读写锁
    pthread_rwlock_t m_lock;
};

class NullRWMutex : Noncopyable{
public:
    typedef ReadScopeLockImpl<NullMutex> ReadLock;
    typedef WriteScopedLockImpl<NullMutex> WriteLock;

    NullRWMutex(){}

    ~NullRWMutex(){}

    void rdlock(){}

    void wrlock(){}

    void unlock(){}
};

// 自旋锁
class SpinLock : Noncopyable{
public:
    typedef ScopedLockImpl<SpinLock> Lock;

    SpinLock(){
        pthread_spin_init(&m_mutex, 0);
    }
    ~SpinLock(){
        pthread_spin_destroy(&m_mutex);
    }

    void lock(){
        pthread_spin_lock(&m_mutex);
    }

    void unlock(){
        pthread_spin_unlock(&m_mutex);
    }
private:
    pthread_spinlock_t m_mutex;
};

// 原子锁
class CASLock : Noncopyable{
public:
    typedef ScopedLockImpl<CASLock> Lock;

    CASLock(){
        m_mutex.clear();
    }

    ~CASLock(){}

    void lock(){
        while(std::atomic_flag_test_and_set_explicit(&m_mutex, std::memory_order_acquire));
    }
    void unlock(){
        std::atomic_flag_clear_explicit(&m_mutex, std::memory_order_release);
    }
private:
    volatile std::atomic_flag m_mutex;
};



}

#endif