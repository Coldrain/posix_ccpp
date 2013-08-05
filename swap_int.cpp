#include <stdio.h>

int main(int argc, char* argv[]) {
	int nA = 101;
	int nB = 102;

	printf("ORIGINAL DATA: %d - %d\n", nA, nB);

	nA = nA ^ nB;
	nB = nA ^ nB;
	nA = nA ^ nB;

	printf("RESULT DATA: %d - %d\n", nA, nB);

	return 0;
}
