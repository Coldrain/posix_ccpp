#include "stdafx.h"
#include "Mutex.h"
 
Mutex::Mutex() 
{
    //�����ٽ�������
    InitializeCriticalSection(&cs);
}
Mutex::~Mutex()
{
    //ɾ���ٽ�������
    DeleteCriticalSection(&cs);
}