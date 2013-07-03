#include <stdio.h>

int sign1(int x) {
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else return -1;
}

int sign2(int x) {
	int ox = abs(x) + 1;
	int r1 = (x + 1) / ox;
	int r2 = (x - 1) / ox;
	return r1 + r2;
}

int sign3(int x) {
	int k = x & 0x80000000;
	int j = k >> 30;
	return j + !!x;
}

int main(int argc, char* argv[]) {
	int a = 0;
	for (a = -5; a < 5; a++) {
		printf("%d\n", sign1(a));
	}
	return 0;
}
