#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int status = 0;
	char line[128] = {0};
	int seconds = 0;
	pid_t pid = 0;
	char message[64] = {0};

	while (1)
	{
		printf("Alarm > ");

		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(0);

		if (strlen(line) <= 1)
			continue;

		if (sscanf(line, "%d %64[^\n]", &seconds, message) < 2)
		{
			fprintf(stderr, "Bad Command\n");
			return 0;
		}

		pid = fork();
		if (pid == (pid_t)-1)
			printf("Fork\n");
		if (pid == (pid_t)0)
		{
			sleep (seconds);
			printf("(%d) %s\n", seconds, message);
			exit(0);
		}
		else
		{
			do {
				pid = waitpid ((pid_t)-1, NULL, WNOHANG);
				if (pid == (pid_t)-1)
					printf ("Wait for child\n");
			} while (pid != (pid_t)0);
		}
	}

	return 0;
}
