#ifndef __THREADSTARTER_H__
#define __THREADSTARTER_H__

#include <windows.h>

//�߳̽ӿ�
class ThreadBase
{
public:
    ThreadBase() {}
    virtual ~ThreadBase() {}
    virtual bool run() = 0;//�̺߳���
    virtual void OnShutdown() {}
    HANDLE THREAD_HANDLE;
};

#endif