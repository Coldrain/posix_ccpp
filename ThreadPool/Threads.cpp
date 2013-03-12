#include "stdafx.h"
#include "CThreads.h"

CThread::CThread() : ThreadBase()
{    
    //初试化线程的状态为等候
    ThreadState = THREADSTATE_AWAITING;
    start_time  = 0;
}

CThread::~CThread()
{
    
}

bool CThread::run()
{
    return false;
}

void CThread::OnShutdown()
{
    SetThreadState(THREADSTATE_TERMINATE);
}