#include <stdio.h>

char toLower(char c) {
	return c | 0x20;
}

char toUpper(char c) {
	return c & ~0x20;
}

int main(int argc, char* argv[]) {
	unsigned int a = 0;
	for (a = 'A'; a <= 'z'; a++) printf("%c ", toLower(a));
	printf("\n");
	for (a = 'A'; a <= 'z'; a++) printf("%c ", toUpper(a));
	printf("\n");
	return 0;
}
