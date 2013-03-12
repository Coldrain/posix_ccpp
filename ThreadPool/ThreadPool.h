#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "ThreadStarter.h"
#include "Mutex.h"

#include <windows.h>
#include <assert.h>
#include <set>


typedef unsigned int uint32;
typedef signed __int32 int32;

//�̹߳���
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
        //���߳��������������������ͣ�߳����У�����Ҫʹ��SuspendThread����ͣ�̵߳�ִ��
        SuspendThread(hThread);
        
    }

    //�ָ��̵߳�ִ�о���ʹ��ResumeThread������
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
        //WaitForSingleObject�����������hHandle�¼����ź�״̬����������ִ��ʱ�䳬��dwMilliseconds�ͷ���
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
    Mutex SetupMutex;//�̵߳Ļ���
    bool DeleteAfterExit;
};

typedef std::set<Thread*> ThreadSet;

//�̳߳���
class CThreadPool
{
    //uint32 _threadsRequestedSinceLastCheck;
    //uint32 _threadsFreedSinceLastCheck;
    //uint32 _threadsExitedSinceLastCheck;
    uint32 _threadsToExit;
    int32 _threadsEaten;//�����߳�����
    Mutex _mutex;

    ThreadSet m_activeThreads;//����ִ�������̶߳���
    ThreadSet m_freeThreads;//�����̶߳���

public:
    CThreadPool();

    void IntegrityCheck();

    //����ָ���������̲߳��ӵ��̳߳�
    void Startup();

    //�����߳�
    void Shutdown();
    

    bool ThreadExit(Thread * t);

    Thread* StartThread(ThreadBase * ExecutionTarget);

    //���̳߳�ȡ�ÿ����̲߳�ִ������
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

extern CThreadPool ThreadPool;//�̳߳�

#endif