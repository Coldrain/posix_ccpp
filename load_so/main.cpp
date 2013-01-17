#include "base.h"
#include <iostream>
#include <dlfcn>

int main()
{
	void *pLib = dlopen("libsubclass.so", RTLD_LAZY);
	if (!pLib)
	{
		std::cout << dlerror() << std::endl;
		return -1;
	}

	create_obj *crtObj = (create_obj*)dlsym(pLib, "create_obj");
	char *error_dlsys = dlerror();
	if (error_dlsys)
	{
		std::out << dlsym_error << std::endl;
		return -1;
	}

	destroy_obj *dstObj = (destroy_obj*)dlsym(pLib, "destroy_obj");
	error_dlsys = dlerror();
	if (error_dlsys)
	{
		std::cout << dlsym_error << std::endl;
		return -1;
	}

	CBase *p = crtObj();
	p->check();
	dstObj(p);

	dlclose(pLib);

	return 0;
}

