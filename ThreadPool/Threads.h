#ifndef __CTHREADS_H__
#define __CTHREADS_H__

#include "ThreadStarter.h"

//�̵߳�״̬
enum CThreadState
{
    THREADSTATE_TERMINATE = 0,//��ֹ
    THREADSTATE_PAUSED    = 1,//��ͣ
    THREADSTATE_SLEEPING  = 2,//˯��
    THREADSTATE_BUSY      = 3,//æµ
    THREADSTATE_AWAITING  = 4,//�Ⱥ�
};

//�̻߳���
class CThread : public ThreadBase
{

public:
    CThread();
    ~CThread();
    virtual bool run();
    virtual void OnShutdown();

    //�����̵߳�״̬
    __forceinline void SetThreadState(CThreadState thread_state)
    { 
        ThreadState = thread_state;
    }
    //�����̵߳�״̬
    __forceinline CThreadState GetThreadState()
    { 
        return ThreadState;
    }
    //�����߳�ID
    int GetThreadId()
    { 
        return ThreadId;
    }
    time_t GetStartTime() 
    {
        return start_time;
    }

protected:
    CThreadState ThreadState;//�̵߳�״̬
    time_t start_time;
    int ThreadId;//�߳�ID

};

#endif