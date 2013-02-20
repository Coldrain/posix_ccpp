#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (access(argv[1], R_OK) == 0)
	{
		printf(__FILE__);
		printf("\t");
		printf(__func__);
		printf("\t");
		printf("%s\t", date());
		printf("It exists!\n");
	}

	return 0;
}
