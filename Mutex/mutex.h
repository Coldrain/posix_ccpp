#pragma once

#ifndef WIN32
#include <pthread.h>
#else
#include <Windows.h>
#endif

class LockableObject
{
public:
 LockableObject(){}
 ~LockableObject(){}

 virtual void lock() = 0;
 virtual void unlock() = 0;
};

class CCMutex: public LockableObject
{
public:
 CCMutex();
 ~CCMutex();

 void lock();
 void unlock();

private:

#ifndef WIN32
 pthread_mutex_t  mutex_;
#else
 CRITICAL_SECTION  criticalSection_;
#endif
};

class MyGuard
{
public:
 MyGuard(LockableObject *pLockableObject)
 {
 pLockableObject_ = pLockableObject;
 pLockableObject_->lock();
 }

 ~MyGuard()
 {
 pLockableObject_->unlock();
 }

private:
 LockableObject * pLockableObject_;
};