#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <windows.h>

//����̲߳�����ͬ������ʱ��һ������Ҫ��˳����ʵģ�������������ݴ���
//Ϊ���������⣬����Ҫ���뻥���������ÿ���̶߳���˳��ط��ʱ�����
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
    ���磺
    �̲߳���������
    int AddCount(void)
    {
        EnterCriticalSection(&cs);
        int nRet = m_nCount++;
        LeaveCriticalSection(&cs);
        return nRet;
    }
    �ں���AddCount�����EnterCriticalSection��LeaveCriticalSection��������ʱ���m_nCount��
    ͨ���������ַ������Ϳ���ʵ�ֶ��̰߳�˳��ط�����ͬ�ı���
    */
    __forceinline bool AttemptAcquire()
    {
        //һ���߳�Ҳ���Ե���TryEnterCriticalSection����������ĳ���ٽ���������Ȩ,��ʱ��
        //ʹ����ʧ��Ҳ���ᱻ����
        return 0;//(TryEnterCriticalSection(&cs) == TRUE ? true : false);
    }

protected:
    CRITICAL_SECTION cs;//�ٽ�����һ�ַ�ֹ����߳�ͬʱִ��һ���ض�����ڵĻ���

};

#endif