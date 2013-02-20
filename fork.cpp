#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	printf("Now only one process\n");
	printf("Calling fork...\n");

	pid = fork();

	if (!pid)
		printf("I am the child: %d\n", pid);
	else if (pid > 0)
		printf("I am the father: %d\n", pid);
	else
		printf("Fork failed!\n");

	return 0;
}
