#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

#define	MAXFD	64

void daemon_init(char *pname, int facility)
{
	int i = 0;
	pid_t pid;

	// kill parent process
	if (pid = fork())
		exit(0);

	// the first process
	setsid();

	signal(SIGHUP, SIG_IGN);
	// kill the first child process
	if (pid = fork())
		exit(0);

	// the second child process
	daemon_proc = 1;

	// setup work directory
	chdir("/");

	// clear file mask
	umask();

	// close all handles of files
	for (i = 0; i < MAXFD; i++)
		close(i);

	// open log
	openlog(pname, LOG_PID, facility);
}
