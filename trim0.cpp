#include <stdio.h>
#include <string.h>

char *trim0(char *src)
{
	int index = 0, i = 0;

	for (i = 0; i < strlen(src); i++)
	{
		if (src[i] != '0') break;
		else index++;
	}

	return &src[index];
}

int main()
{
	char szSrc[140] = {0};
	strcpy(szSrc, "000000202140000");

	printf("result: %s\n", trim0(szSrc));

	return 0;
}

