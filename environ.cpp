/*
 * 如何通过environ指针访问环境变量
 */

#include <stdio.h>

extern char **environ;

int main()
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env++);
	}

	return 0;
}
