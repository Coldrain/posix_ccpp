#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	fprintf(stderr, "ERROR: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);

	return 0;
}

