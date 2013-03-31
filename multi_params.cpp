#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void write_log(char* arg, ...)
{
	va_list va;
	char buf[1024] = {0};

	va_start (va, arg);
	(void) vsprintf(buf, arg, va);
	va_end(va);

	printf("%s-%s", "my_log_prehead", buf);
}

void read_num(int num, ...)
{
	va_list va;

	va_start(va, num);

	while (num--)
	{
		printf("%d\t", va_arg(va, int));
	}

	va_end(va);
}

int main()
{
	write_log("%d\t%s\n", 10, "hello world!");
	read_num(4, 2, 3, 4, 5);

	return 0;
}

