#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define FIFO_FILE "./fifo"
#define BUFFER_SIZE PIPE_BUF

int main(void) {
	char buff[BUFFER_SIZE] = {0};

	if (access(FIFO_FILE, F_OK) == -1)
	{
		if ((mkfifo(FIFO_FILE, 0666) < 0) && (errno != EEXIST))
		{
			printf("Filo file create error!\n");
		}
	}

	pid_t newfork = fork();
	if (newfork < 0)
	{
		printf("Fork error!\n");
		exit(1);
	}
	else if (newfork == 0)
	{
		int fd1 = open(FIFO_FILE, O_RDONLY);
		int reader;
		if (fd1 < 0)
		{
			printf("child process fd error!\n");
			exit(1);
		}

		while (1)
		{
			reader = read(fd1, buff, BUFFER_SIZE);
			if (buff[0] == 'q' && buff[1] == '\0')
			{
				printf("Get EXIT message and quit!\n");
				close(fd1);
				exit(0);
			}
			if (reader > 0)
			{
				printf("Read from FIFO:%s\n", buff);
			}
		}
	}
	else
	{
		int fd2 = open(FIFO_FILE, O_WRONLY);
		int writer;
		if (fd2 < 0)
		{
			printf("Father process fd error!\n");
			exit(1);
		}

		while (1)
		{
			if (buff[0] == 'q' && buff[1] == '\0')
			{
				close(fd2);
				exit(0);
			}

			scanf("%s", buff);
			writer = write(fd2, buff, BUFFER_SIZE);
		}
	}
}
