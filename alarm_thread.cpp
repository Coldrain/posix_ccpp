#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

typedef struct alart_tag
{
	int seconds;
	char message[64];
} alarm_t;

void *alarm_thread(void *arg)
{
	alarm_t *alarm = (alarm_t *)arg;
	int status = 0;

	status = pthread_detach(pthread_self());
	if (status != 0)
	{
		printf ("Detach thread failed\n");
	}

	sleep(alarm->seconds);

	printf("(%d) %s\n", alarm->seconds, alarm->message);

	free(alarm);

	return NULL;
}

int main(int argc, char *argv[])
{
	int status = 0;
	char line[128] = {0};
	alarm_t *alarm = new alarm_t;
	pthread_t thread;

	while (1)
	{
		printf ("Alarm > ");
		if (fgets(line, sizeof(line), stdin) == NULL)
			return 0;

		if (strlen(line) <= 1)
			continue;

		if (sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message) < 2)
		{
			fprintf(stderr, "Bad command\n");
			delete alarm;
			return 0;
		}

		status = pthread_create(&thread, NULL, alarm_thread, alarm);
		if (status != 0)
			printf("Create alarm thread failed\n");
	}

	return 0;
}

