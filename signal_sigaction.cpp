#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void my_func(int sig_no)
{
	if (sig_no == SIGINT)
	{
		printf("I get SIGINT\n");
	}
	else if (sig_no == SIGQUIT)
	{
		printf("I get SIGQUIT\n");
	}
}

int main()
{
	printf("waiting for signal...\n");

	signal(SIGINT, my_func);

	signal(SIGQUIT, my_func);

	pause();

	exit(0);
}

