#include <stdio.h>

typedef struct _T_LIST_NODE {
	int nType;
	_T_LIST_NODE *pT_Next;
} T_LIST_NODE;

T_LIST_NODE* ReverseList1(T_LIST_NODE* pHead)
{
	T_LIST_NODE* p1 = NULL;
	T_LIST_NODE* p2 = pHead;
	T_LIST_NODE *pTemp = NULL;
	while (p2) {
		pTemp = p2->pT_Next;
		p2->pT_Next = p1;
		p1 = p2;
		p2 = pTemp;
	}
	return p1;
}

T_LIST_NODE *ReverseList2(T_LIST_NODE *pHead) {
	T_LIST_NODE *pNewHead = pHead;
	if (pHead == NULL || pHead->pT_Next == NULL) return pHead;
	pNewHead = ReverseList2(pHead->pT_Next);
	pHead->pT_Next->pT_Next = pHead;
	pHead->pT_Next = NULL;
	return pNewHead;
}

int main(int argc, char* argv[]) {
	T_LIST_NODE *lst = new T_LIST_NODE[10];
	T_LIST_NODE *pTemp;
	lst->nType = 0;
	lst->pT_Next = NULL;
	for (int i = 1; i < 10; i++) {
		pTemp = new T_LIST_NODE;
		pTemp->nType = i;
		pTemp->pT_Next = lst;
		lst = pTemp;
	}

	pTemp = lst;
	while (pTemp) {
		printf ("%d ", pTemp->nType);
		pTemp = pTemp->pT_Next;
	}
	printf("\n");

	lst = ReverseList2(lst);
	pTemp = lst;
	while (pTemp) {
		printf("%d ", pTemp->nType);
		pTemp = pTemp->pT_Next;
	}
	printf("\n");

	return 0;
}

