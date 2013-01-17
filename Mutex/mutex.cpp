#include "StdAfx.h"
#include "CMutex.h"

CCMutex::CCMutex()
{
#ifndef WIN32
 pthread_mutex_init(&mutex_, NULL);
#else
 InitializeCriticalSection(&criticalSection_);
#endif
}

CCMutex::~CCMutex()
{
#ifndef WIN32
 int ret = pthread_mutex_destroy(&mutex_);
#else
 DeleteCriticalSection(&criticalSection_);
#endif
}

void CCMutex::lock()
{
#ifndef WIN32
 int ret = pthread_mutex_lock(&mutex_);
#else
 EnterCriticalSection(&criticalSection_);
#endif
 return;
}

void CCMutex::unlock()
{
#ifndef WIN32
 int ret = pthread_mutex_unlock(&mutex_);
#else
 LeaveCriticalSection(&criticalSection_);
#endif
 return;
}