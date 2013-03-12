#include <TCHAR.H>   
#include "MemPool.h"   
  
int main()  
{  
    CMemPool mp;  
    assert( mp.Initialize() );  
  
    for(int i = 0; i<100; i++)  
    {  
        TCHAR* psz = mp.GetStringBuffer(8192);  
        _stprintf_s(psz, 8192, TEXT("now i=%d/n"), i);  
        _tprintf(psz);  
    }  
  
    mp.Destroy();  
    return getchar();  
}  