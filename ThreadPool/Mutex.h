#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <windows.h>

//多个线程操作相同的数据时，一般是需要按顺序访问的，否则会引导数据错乱
//为解决这个问题，就需要引入互斥变量，让每个线程都按顺序地访问变量。
class Mutex
{
public:
    Mutex();
    ~Mutex();

    __forceinline void Acquire()
    {
        EnterCriticalSection(&cs);
    }

    __forceinline void Release()
    {
        LeaveCriticalSection(&cs);
    }
    /*
    例如：
    线程操作函数。
    int AddCount(void)
    {
        EnterCriticalSection(&cs);
        int nRet = m_nCount++;
        LeaveCriticalSection(&cs);
        return nRet;
    }
    在函数AddCount里调用EnterCriticalSection和LeaveCriticalSection来互斥访问变量m_nCount。
    通过上面这种方法，就可以实现多线程按顺序地访问相同的变量
    */
    __forceinline bool AttemptAcquire()
    {
        //一个线程也可以调用TryEnterCriticalSection函数来请求某个临界区的所有权,此时即
        //使请求失败也不会被阻塞
        return 0;//(TryEnterCriticalSection(&cs) == TRUE ? true : false);
    }

protected:
    CRITICAL_SECTION cs;//临界区是一种防止多个线程同时执行一个特定代码节的机制

};

#endif