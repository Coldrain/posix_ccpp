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

    //���̳߳ض�ȡһ���߳�
    if(m_freeThreads.size())//�п����߳�
    {    
        //�õ�һ�������߳�
        t = *m_freeThreads.begin();
        //�����ӿ����̶߳�����ɾ��
        m_freeThreads.erase(m_freeThreads.begin());

        //������߳�һ������
        t->ExecutionTarget = ExecutionTarget;
        
        //�ָ��̵߳�ִ��
        t->ControlInterface.Resume();
    }
    else
    {

        //����һ���µ��̲߳�ִ������
        t = StartThread(ExecutionTarget);
    }

    //���̼߳ӵ�ִ�������̶߳���
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

    //����������̳߳ص�״̬
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
            if(t->ExecutionTarget->run())//ִ������,����true��ʾ�������
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
            //    printf("ThreadPool:�߳�%d���ڵȴ�������.", tid);
            t->ControlInterface.Suspend();//��ͣ�߳�����
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
    lpThreadAttributes���̵߳�����,
    dwStackSize���̵߳�ջ��С,
    lpStartAddress���̺߳����Ŀ�ʼ��ַ,
    lpParameter�Ǵ��͸��̺߳����Ĳ���,
    dwCreationFlags�Ǵ����̱߳�־����������߳�,
    lpThreadId�Ǳ�ʶ����̵߳�ID)
    */
    h = CreateThread(NULL, 0, &thread_proc, (LPVOID)t, 0, (LPDWORD)&t->ControlInterface.thread_id);
    t->ControlInterface.Setup(h);
    t->SetupMutex.Release();
 
    return t;
}