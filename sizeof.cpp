#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("sizeof: short\t\t%d\n", sizeof(short));
	printf("sizeof: int\t\t%d\n", sizeof(int));
	printf("sizeof: long\t\t%d\n", sizeof(long int));
	printf("sizeof: unsigned long\t%d\n", sizeof(unsigned long));
	printf("sizeof: long long\t%d\n", sizeof(long long));

	return 0;
}
