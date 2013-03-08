#include <stdio.h>
#include <string.h>

void getFactorial(int param)
{
	if (param == 0 || param == 1)
	{
		printf("%d! = 1\n", param);
		return;
	}

	if (param < 0)
	{
		printf("invalid parameter!\n");
		return;
	}

	int j = 0;
	int len = 1;
	int temp = 0;
	int *a = new int[3 * param];
	memset(a, 0, 3 * param);

	a[1] = 1;

	for (int i = 2; i <= param; i++)
	{
		int carry = 0;

		for (int j = 1; j <= len; j++)
		{
			temp = a[j] * i + carry;
			a[j] = temp % 10;
			carry = temp / 10;

			if (j == len && carry != 0) len++;
		}
	}

	for (int i = len; i > 0; i--)
		printf("%d", a[i]);

	printf("\n");
}

int main(int argc, const char* argv[])
{
	getFactorial(100);

	return 0;
}
