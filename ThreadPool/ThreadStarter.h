#ifndef __THREADSTARTER_H__
#define __THREADSTARTER_H__

#include <windows.h>

//线程接口
class ThreadBase
{
public:
    ThreadBase() {}
    virtual ~ThreadBase() {}
    virtual bool run() = 0;//线程函数
    virtual void OnShutdown() {}
    HANDLE THREAD_HANDLE;
};

#endif