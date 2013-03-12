#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "ThreadStarter.h"
#include "Mutex.h"

#include <windows.h>
#include <assert.h>
#include <set>


typedef unsigned int uint32;
typedef signed __int32 int32;

//线程管理
class ThreadController
{
public:
    HANDLE hThread;
    uint32 thread_id;

    void Setup(HANDLE h)
    {
        hThread = h;
    }
    void Suspend()
    {
        assert(GetCurrentThreadId() == thread_id);
        //当线程做完任务或者现在想暂停线程运行，就需要使用SuspendThread来暂停线程的执行
        SuspendThread(hThread);
        
    }

    //恢复线程的执行就是使用ResumeThread函数了
    void Resume()
    {
        assert(GetCurrentThreadId() != thread_id);
        if(!ResumeThread(hThread))
        {
            DWORD le = GetLastError();
            printf("error: %u/n", le);
        }
    }

    void Join()
    {
        //WaitForSingleObject函数用来检测hHandle事件的信号状态，当函数的执行时间超过dwMilliseconds就返回
        WaitForSingleObject(hThread, INFINITE);
    }

    uint32 GetId()
    {
        return thread_id;
    }

};

struct Thread
{
    ThreadBase* ExecutionTarget;
    ThreadController ControlInterface;
    Mutex SetupMutex;//线程的互斥
    bool DeleteAfterExit;
};

typedef std::set<Thread*> ThreadSet;

//线程池类
class CThreadPool
{
    //uint32 _threadsRequestedSinceLastCheck;
    //uint32 _threadsFreedSinceLastCheck;
    //uint32 _threadsExitedSinceLastCheck;
    uint32 _threadsToExit;
    int32 _threadsEaten;//可用线程数量
    Mutex _mutex;

    ThreadSet m_activeThreads;//正在执行任务线程对列
    ThreadSet m_freeThreads;//可用线程对列

public:
    CThreadPool();

    void IntegrityCheck();

    //创建指定数量的线程并加到线程池
    void Startup();

    //销毁线程
    void Shutdown();
    

    bool ThreadExit(Thread * t);

    Thread* StartThread(ThreadBase * ExecutionTarget);

    //从线程池取得可用线程并执行任务
    void ExecuteTask(ThreadBase * ExecutionTarget);

    void ShowStats();

    
    void KillFreeThreads(uint32 count);

    
    //__forceinline void Gobble(){ 
    //    _threadsEaten=(int32)m_freeThreads.size();
    //}

    __forceinline uint32 GetActiveThreadCount(){
        return (uint32)m_activeThreads.size();
    }

    __forceinline uint32 GetFreeThreadCount(){
        return (uint32)m_freeThreads.size();
    }
};

extern CThreadPool ThreadPool;//线程池

#endif