#include "MemPool.h"   
  
//�����ڴ�����ṹ.   
typedef struct tagMEMORY_BLOCK  MEMORY_BLOCK, *LPMEMORY_BLOCK;  
struct tagMEMORY_BLOCK  
{  
    DWORD                 dwIndex;  
    DWORD                 dwSize;  
    LPMEMORY_BLOCK        lpNext;  
    LPMEMORY_BLOCK        lpPrev;  
    LPBYTE                lpMemory;  
};  
  
//�ڴ�ر�ͷ�ṹ   
typedef struct tagHEADER  HEADER, *LPHEADER;  
struct tagHEADER  
{  
    LPMEMORY_BLOCK   lpHead;  
    HANDLE           hHeap;  
};  
  
//�ڴ�ض����캯��   
CMemPool::CMemPool()  
{  
    handle = NULL;  
}  
  
//�ڴ�ض�����������   
CMemPool::~CMemPool()  
{  
    Destroy();  
}  
  
//�ڴ�ض����ʼ�����״η���8KB�ڴ���Ϊ�ڴ��   
BOOL CMemPool::Initialize()  
{  
    if( NULL == handle )  
    {  
        HANDLE  procHeap = GetProcessHeap();  
  
        // �����ڴ�ص�ͷ�ڵ�.   
        handle = HeapAlloc(procHeap, 0, sizeof(HEADER));  
  
        if (handle)   
        {  
            LPHEADER header = (LPHEADER)handle;  
            // ����ͷ�ڵ�ɹ������ڳ�ʼ���ڴ��.   
            header->lpHead = NULL;  
            header->hHeap = procHeap;  
  
            //����ʵ�ʷ���8KB�ڴ浽�ڴ��.   
            BOOL  ableToAddMemory = AddMemory(0);  
  
            if (!ableToAddMemory)   
            {  
                //�����ڴ�ʧ�ܣ�ϵͳ��Դƿ����   
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
  
        //�������������ͷ��ڴ����.   
        blockToFree = poolHeader->lpHead;  
  
        while (blockToFree != NULL)  
        {  
            nextBlock = blockToFree->lpNext;  
            HeapFree(poolHeader->hHeap, 0, blockToFree);  
            blockToFree = nextBlock;  
        }  
  
        //�������ˣ��ڴ��ͷ���Ҳ��Ҫ�ͷ�.   
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
  
    // �ж��Ƿ���Ҫ������ڴ棬����ǣ������֮.   
    sizeNeeded = dwSize;  
  
    if (currentBlock->dwSize - currentBlock->dwIndex < sizeNeeded + dwAlignSize)  
    {  
        haveEnoughMemory = AddMemory(sizeNeeded + dwAlignSize);  
        currentBlock = poolHeader->lpHead;  
    }  
  
    // ���������㹻���ڴ棬��������   
    if (haveEnoughMemory)  
    {  
        if (dwAlignSize)  
        {  
            padLength = (DWORD)currentBlock + sizeof(MEMORY_BLOCK) + currentBlock->dwIndex;  
            currentBlock->dwIndex += (dwAlignSize - (padLength % dwAlignSize)) % dwAlignSize;  
        }  
          
        //����õ����ڴ��ַ����������   
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
  
    // ������Ҫ�����ڴ����С����������ͼ����֮.   
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
        // ʹ�ڴ���ͷ���洢һ��MEMORY_BLOCK�ṹ.   
        newBlock = (LPMEMORY_BLOCK)allocedMemory;  
        newBlock->dwSize = sizeNeeded - sizeof(MEMORY_BLOCK);  
        newBlock->lpMemory = allocedMemory + sizeof(MEMORY_BLOCK);  
        newBlock->dwIndex = 0;  
      
        // ���ڴ�����ӵ�list��.   
        if(poolHeader->lpHead)   
        {  
            poolHeader->lpHead->lpPrev = newBlock;  
        }  
        newBlock->lpNext = poolHeader->lpHead;  
        newBlock->lpPrev = NULL;  
        poolHeader->lpHead = newBlock;  
    }  
  
    // ���allocedMemory ���� NULL, ��������ǳɹ���.   
    return allocedMemory != NULL;  
}  