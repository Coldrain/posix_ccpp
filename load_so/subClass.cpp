#include <stdio.h>
#include "subClass.h"

void CSubClass::check()
{
	printf ("load ok\n");
}
/*
extern "C"
{
	CBase* create_obj()
	{
		return new CSubClass;
	}

	void destroy_obj(CBase* pBase)
	{
		delete pBase;
	}
}
*/