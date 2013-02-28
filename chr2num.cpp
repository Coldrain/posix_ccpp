#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int chr2num(char src)
{
	return src - 0x30;
}

int main()
{
	printf("%d\n", chr2num('9'));
}
