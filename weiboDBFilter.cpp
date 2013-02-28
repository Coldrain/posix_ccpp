#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define FAILED		-1
#define	SUCCEED		0

map<string, string> container;

int intlen(long n)
{
	int i = 1;
	while (n /= 10) i++;
	return i;
}

bool allNum(const char *src, int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
		if (src[i] < '0' || src[i] > '9')
			break;

	return i == len;
}

int loadFile(char *filePath)
{
	FILE *fp;
	char buf[20] = {0}, tmp[20] = {0}, vle[20] = {0};
	int len = 0, index = 0;

	fp = fopen (filePath, "r");
	if (!fp)
	{
		cout << "fopen filePath failed" << endl;
		return FAILED;
	}
	else
	{
		cout << "fopen filePath succeed" << endl;
	}

	while (fgets(buf, sizeof(buf), fp))
	{
		if (buf[0] == '\n') continue;

		len = strlen(buf);
		if (buf[len - 1] == '\n') buf[len - 1] = '\0';
		sscanf(buf, "%s%s", tmp, vle);

		index++;
		for (int i = 0; i < intlen(index); i++) cout << '\b';
		cout << index;

		if (strcmp(&tmp[len - 7], "@qq.com"))
			container[tmp] = vle;
	}

	cout << endl;
	fclose(fp);
	return SUCCEED;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "example: a.out 6" << endl;
		return FAILED;
	}

	char path[20] = {0};
	strcpy(path, "new");
//	strcpy(path, "weibo.dbh");
	if (loadFile(path) == FAILED)
	{
		cout << "loadFile failed" << endl;
		return FAILED;
	}

	map<string, string>::iterator iter;
	for (iter = container.begin(); iter != container.end(); iter ++)
	{
		if (iter->first.length() == atoi(argv[1]) + 7)
			if (iter->first.substr(iter->first.length() - 7) == "@qq.com")
				if (allNum(iter->first.c_str(), iter->first.length() - 7))
					cout << iter->first << "\t\t" << iter->second << endl;
	}

	return 0;
}
