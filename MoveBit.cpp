#include <stdio.h>
#include <string.h>

#define MOVE_LEFT(x, s, n)  ((x) << (n)) | ((x) >> ((s) - (n)))
#define MOVE_RIGHT(x, s, n) ((x) >> (n)) | ((x) << ((s) - (n)))

int main()
{
	unsigned int a = 0;
	scanf("%x", &a);
	printf("%08x\n", a);

	printf("move left: %08x\n", MOVE_LEFT(a, 8 * sizeof(int), 4));
	printf("move right: %08x\n", MOVE_RIGHT(a, 8 * sizeof(int), 4));

	return 0;
}
