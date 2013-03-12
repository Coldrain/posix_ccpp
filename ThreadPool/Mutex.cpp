#include "stdafx.h"
#include "Mutex.h"
 
Mutex::Mutex() 
{
    //创建临界区对象
    InitializeCriticalSection(&cs);
}
Mutex::~Mutex()
{
    //删除临界区对象
    DeleteCriticalSection(&cs);
}