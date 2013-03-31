#ifndef __CTHREADS_H__
#define __CTHREADS_H__

#include "ThreadStarter.h"

//线程的状态
enum CThreadState
{
    THREADSTATE_TERMINATE = 0,//终止
    THREADSTATE_PAUSED    = 1,//暂停
    THREADSTATE_SLEEPING  = 2,//睡眠
    THREADSTATE_BUSY      = 3,//忙碌
    THREADSTATE_AWAITING  = 4,//等候
};

//线程基类
class CThread : public ThreadBase
{

public:
    CThread();
    ~CThread();
    virtual bool run();
    virtual void OnShutdown();

    //设置线程的状态
    __forceinline void SetThreadState(CThreadState thread_state)
    { 
        ThreadState = thread_state;
    }
    //返回线程的状态
    __forceinline CThreadState GetThreadState()
    { 
        return ThreadState;
    }
    //返回线程ID
    int GetThreadId()
    { 
        return ThreadId;
    }
    time_t GetStartTime() 
    {
        return start_time;
    }

protected:
    CThreadState ThreadState;//线程的状态
    time_t start_time;
    int ThreadId;//线程ID

};

#endif