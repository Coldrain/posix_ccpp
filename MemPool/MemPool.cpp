#include "MemPool.h"   
  
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
  
//内存池对象构造函数   
CMemPool::CMemPool()  
{  
    handle = NULL;  
}  
  
//内存池对象析构函数   
CMemPool::~CMemPool()  
{  
    Destroy();  
}  
  
//内存池对象初始化，首次分配8KB内存作为内存池   
BOOL CMemPool::Initialize()  
{  
    if( NULL == handle )  
    {  
        HANDLE  procHeap = GetProcessHeap();  
  
        // 分配内存池的头节点.   
        handle = HeapAlloc(procHeap, 0, sizeof(HEADER));  
  
        if (handle)   
        {  
            LPHEADER header = (LPHEADER)handle;  
            // 分配头节点成功，现在初始化内存池.   
            header->lpHead = NULL;  
            header->hHeap = procHeap;  
  
            //初次实际分配8KB内存到内存池.   
            BOOL  ableToAddMemory = AddMemory(0);  
  
            if (!ableToAddMemory)   
            {  
                //分配内存失败，系统资源瓶颈！   
                HeapFree(header->hHeap, 0, handle);  
                handle = NULL;  
            }  
        }  
    }  
    return (handle != NULL);  
}  
  
VOID CMemPool::Destroy()  
{  
    if(handle != NULL)  
    {  
        LPMEMORY_BLOCK  nextBlock;  
        LPMEMORY_BLOCK  blockToFree;   
        LPHEADER        poolHeader = (LPHEADER)handle;  
  
        //遍历链表，进行释放内存操作.   
        blockToFree = poolHeader->lpHead;  
  
        while (blockToFree != NULL)  
        {  
            nextBlock = blockToFree->lpNext;  
            HeapFree(poolHeader->hHeap, 0, blockToFree);  
            blockToFree = nextBlock;  
        }  
  
        //别忘记了，内存池头结点也需要释放.   
        HeapFree(poolHeader->hHeap, 0, handle);  
        handle = NULL;  
    }  
}  
  
LPVOID CMemPool::GetAlignedMemory(DWORD dwSize, DWORD dwAlignSize)  
{  
    assert(handle != NULL);  
  
    BOOL            haveEnoughMemory = TRUE;  
    LPVOID          lpMemory         = NULL;  
    LPHEADER        poolHeader       = (LPHEADER)handle;  
    LPMEMORY_BLOCK  currentBlock;  
    DWORD           sizeNeeded;  
    DWORD           padLength;  
  
    currentBlock = poolHeader->lpHead;  
  
    // 判断是否需要更多的内存，如果是，则分配之.   
    sizeNeeded = dwSize;  
  
    if (currentBlock->dwSize - currentBlock->dwIndex < sizeNeeded + dwAlignSize)  
    {  
        haveEnoughMemory = AddMemory(sizeNeeded + dwAlignSize);  
        currentBlock = poolHeader->lpHead;  
    }  
  
    // 现在有了足够的内存，返回它！   
    if (haveEnoughMemory)  
    {  
        if (dwAlignSize)  
        {  
            padLength = (DWORD)currentBlock + sizeof(MEMORY_BLOCK) + currentBlock->dwIndex;  
            currentBlock->dwIndex += (dwAlignSize - (padLength % dwAlignSize)) % dwAlignSize;  
        }  
          
        //这里得到了内存地址，返回它！   
        lpMemory = (LPVOID)&(currentBlock->lpMemory[currentBlock->dwIndex]);  
  
        currentBlock->dwIndex += sizeNeeded;  
    }  
  
    return lpMemory;  
}  
  
LPSTR CMemPool::GetDuplicateStringA(LPCSTR szSrc)  
{  
    assert(szSrc);  
  
    DWORD dwBytes = (_mbslen((const unsigned char*)szSrc) + 1) * sizeof(CHAR);  
    LPSTR pString = (LPSTR)GetAlignedMemory(dwBytes, sizeof(CHAR));  
  
    if (pString)   
    {  
        _mbscpy_s((unsigned char*)pString, dwBytes, (const unsigned char*)szSrc);  
    }  
    return pString;  
}  
  
LPWSTR CMemPool::GetDuplicateStringW(LPCWSTR szSrc)  
{  
    assert(szSrc);  
  
    DWORD dwBytes = (wcslen(szSrc) + 1) * sizeof(WCHAR);  
    LPWSTR pString = (LPWSTR)GetAlignedMemory(dwBytes, sizeof(WCHAR));  
  
    if (pString)   
    {  
        wcscpy_s(pString, dwBytes, szSrc);  
    }  
    return pString;  
}  
  
BOOL CMemPool::AddMemory(DWORD dwSize)  
{  
    LPBYTE           allocedMemory;  
    LPMEMORY_BLOCK   newBlock;  
    LPHEADER         poolHeader = (LPHEADER)handle;  
    DWORD            sizeNeeded;  
  
    assert(poolHeader != NULL);  
  
    // 计算需要分配内存的最小数量，并试图分配之.   
    if (dwSize + sizeof(MEMORY_BLOCK) > MEMPOOL_BLOCK_SIZE)   
    {  
        sizeNeeded = dwSize + sizeof(MEMORY_BLOCK);  
    }  
    else   
    {  
        sizeNeeded = MEMPOOL_BLOCK_SIZE;  
    }  
  
    allocedMemory = (LPBYTE)HeapAlloc(poolHeader->hHeap, 0, sizeNeeded);  
  
    if (allocedMemory)   
    {  
        // 使内存块的头部存储一个MEMORY_BLOCK结构.   
        newBlock = (LPMEMORY_BLOCK)allocedMemory;  
        newBlock->dwSize = sizeNeeded - sizeof(MEMORY_BLOCK);  
        newBlock->lpMemory = allocedMemory + sizeof(MEMORY_BLOCK);  
        newBlock->dwIndex = 0;  
      
        // 把内存块链接到list中.   
        if(poolHeader->lpHead)   
        {  
            poolHeader->lpHead->lpPrev = newBlock;  
        }  
        newBlock->lpNext = poolHeader->lpHead;  
        newBlock->lpPrev = NULL;  
        poolHeader->lpHead = newBlock;  
    }  
  
    // 如果allocedMemory 不是 NULL, 则表明我们成功了.   
    return allocedMemory != NULL;  
}  