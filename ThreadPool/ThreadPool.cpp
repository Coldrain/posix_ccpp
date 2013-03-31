#include "stdafx.h"
#include "ThreadPool.h"
#include <process.h>

CThreadPool ThreadPool;

CThreadPool::CThreadPool()
{
    //_threadsExitedSinceLastCheck = 0;
    //_threadsRequestedSinceLastCheck = 0;
    _threadsEaten = 0;
    //_threadsFreedSinceLastCheck = 0;
}


bool CThreadPool::ThreadExit(Thread * t)
{
    _mutex.Acquire();
    
    m_activeThreads.erase(t);

    if(_threadsToExit > 0)
    {
        --_threadsToExit;
        //++_threadsExitedSinceLastCheck;
        if(t->DeleteAfterExit)
            m_freeThreads.erase(t);

        _mutex.Release();
        delete t;
        return false;
    }


    // enter the "suspended" pool
    //++_threadsExitedSinceLastCheck;
    ++_threadsEaten;
    std::set<Thread*>::iterator itr = m_freeThreads.find(t);

    if(itr != m_freeThreads.end())
    {
        
    }
    m_freeThreads.insert(t);
    
    _mutex.Release();

    return true;


}


void CThreadPool::ExecuteTask(ThreadBase * ExecutionTarget)
{

    Thread * t;
    _mutex.Acquire();
    //++_threadsRequestedSinceLastCheck;
    --_threadsEaten;

    //从线程池夺取一个线程
    if(m_freeThreads.size())//有可用线程
    {    
        //得到一个可用线程
        t = *m_freeThreads.begin();
        //把它从可用线程对列里删掉
        m_freeThreads.erase(m_freeThreads.begin());

        //给这个线程一个任务
        t->ExecutionTarget = ExecutionTarget;
        
        //恢复线程的执行
        t->ControlInterface.Resume();
    }
    else
    {

        //创建一个新的线程并执行任务
        t = StartThread(ExecutionTarget);
    }

    //把线程加到执行任务线程对列
    m_activeThreads.insert(t);
    _mutex.Release();


}

void CThreadPool::Startup()
{
    int i;
    int tcount = 5;

    for(i=0; i < tcount; ++i)
        StartThread(NULL);

}

void CThreadPool::ShowStats()
{
    _mutex.Acquire();

    //在这里输出线程池的状态
    //

    _mutex.Release();
}

void CThreadPool::KillFreeThreads(uint32 count)
{
    _mutex.Acquire();
    Thread * t;
    ThreadSet::iterator itr;
    uint32 i;
    for(i = 0, itr = m_freeThreads.begin(); i < count && itr != m_freeThreads.end(); ++i, ++itr)
    {
        t = *itr;
        t->ExecutionTarget = NULL; 
        t->DeleteAfterExit = true;
        ++_threadsToExit;
        t->ControlInterface.Resume();
    }
    _mutex.Release();
}

void CThreadPool::Shutdown()
{
    _mutex.Acquire();
    size_t tcount = m_activeThreads.size() + m_freeThreads.size();        
    
    KillFreeThreads((uint32)m_freeThreads.size());
    _threadsToExit += (uint32)m_activeThreads.size();

    for(ThreadSet::iterator itr = m_activeThreads.begin(); itr != m_activeThreads.end(); ++itr)
    {
        if((*itr)->ExecutionTarget)
            (*itr)->ExecutionTarget->OnShutdown();
    }
    _mutex.Release();

    for(;;)
    {
        _mutex.Acquire();
        if(m_activeThreads.size() || m_freeThreads.size())
        {
            _mutex.Release();
            Sleep(1000);
            continue;
        }

        break;
    }
}


static unsigned long WINAPI thread_proc(void* param)
{
    Thread * t = (Thread*)param;
    t->SetupMutex.Acquire();
    uint32 tid = t->ControlInterface.GetId();
    bool ht = (t->ExecutionTarget != NULL);
    t->SetupMutex.Release();
    
    for(;;)
    {
        if(t->ExecutionTarget != NULL)
        {
            if(t->ExecutionTarget->run())//执行任务,返回true表示任务完成
                delete t->ExecutionTarget;

            t->ExecutionTarget = NULL;
        }

        if(!ThreadPool.ThreadExit(t))
        {
            //Log.Debug("ThreadPool", "Thread %u exiting.", tid);
            break;
        }
        else
        {
            //if(ht)
            //    printf("ThreadPool:线程%d正在等待新任务.", tid);
            t->ControlInterface.Suspend();//暂停线程运行
        }
    }

    ExitThread(0);

    return 0;
}

Thread * CThreadPool::StartThread(ThreadBase * ExecutionTarget)
{
    HANDLE h;
    Thread * t = new Thread;
    
    t->DeleteAfterExit = false;
    t->ExecutionTarget = ExecutionTarget;
    t->SetupMutex.Acquire();
    /*
    CreateThread(
    lpThreadAttributes是线程的属性,
    dwStackSize是线程的栈大小,
    lpStartAddress是线程函数的开始地址,
    lpParameter是传送给线程函数的参数,
    dwCreationFlags是创建线程标志，比如挂起线程,
    lpThreadId是标识这个线程的ID)
    */
    h = CreateThread(NULL, 0, &thread_proc, (LPVOID)t, 0, (LPDWORD)&t->ControlInterface.thread_id);
    t->ControlInterface.Setup(h);
    t->SetupMutex.Release();
 
    return t;
}