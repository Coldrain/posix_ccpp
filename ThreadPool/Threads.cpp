#include "stdafx.h"
#include "CThreads.h"

CThread::CThread() : ThreadBase()
{    
    //���Ի��̵߳�״̬Ϊ�Ⱥ�
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