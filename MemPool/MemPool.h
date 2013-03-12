/*
//树型内存块分配结构.   
typedef struct tagMEMORY_BLOCK  MEMORY_BLOCK, *LPMEMORY_BLOCK;  
struct tagMEMORY_BLOCK  
{  
    DWORD                 dwIndex;  
    DWORD                 dwSize;  
    LPMEMORY_BLOCK        lpNext;  
    LPMEMORY_BLOCK        lpPrev;  
    LPBYTE                lpMemory;  
};  
  
//内存池标头结构   
typedef struct tagHEADER  HEADER, *LPHEADER;  
struct tagHEADER  
{  
    LPMEMORY_BLOCK   lpHead;  
    HANDLE           hHeap;  
};  
*/

#ifndef MEMPOOL_H   
#define MEMPOOL_H   
  
#define STRICT   
#define LEAN_AND_MEAN   
  
#include <windows.h>   
#include <assert.h>   
#include <stdio.h>   
#include <mbstring.h>   
  
//默认内存分配页大小设为8KB   
#define     MEMPOOL_BLOCK_SIZE      8192   
  
class CMemPool  
{  
public:  
  
    CMemPool();  
    ~CMemPool();  
  
    BOOL   Initialize();  
    VOID   Destroy();  
  
    LPVOID GetAlignedMemory(DWORD dwSize, DWORD dwAlignSize);  
    LPSTR  GetDuplicateStringA(LPCSTR szSrc);  
    LPWSTR GetDuplicateStringW(LPCWSTR szSrc);  
  
    inline LPVOID GetMemory(DWORD dwSize)   
    {  
        return GetAlignedMemory(dwSize, 0);  
    }  
  
    inline TCHAR* GetStringBuffer(DWORD dwLen)  
    {  
        return (TCHAR*)GetAlignedMemory(dwLen * sizeof(TCHAR), 0);  
    }  
  
    inline LPSTR GetStringBufferA(DWORD dwLen)   
    {  
        return (LPSTR)GetAlignedMemory(dwLen * sizeof(CHAR), sizeof(CHAR));  
    }  
  
    inline LPWSTR GetStringBufferW(DWORD dwLen)   
    {  
        return (LPWSTR)GetAlignedMemory(dwLen * sizeof(WCHAR), sizeof(WCHAR));  
    }  
  
    inline DWORD* GetDwordBuffer()  
    {  
        return (DWORD*)GetAlignedMemory(sizeof(DWORD), 0);  
    }  
  
private:  
    BOOL   AddMemory(DWORD dwSize);  
    LPVOID handle;  
};  
  
#endif //MEMPOOL_H  