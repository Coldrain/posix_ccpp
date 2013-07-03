#include <iostream>
#include <stack>

using namespace std;
void sysConv(int num, int base, stack<char>& result) {
    while (num) {
	int nTemp = num % base;
	if (nTemp < 10) result.push(nTemp + '0');
	else result.push(nTemp - 10 + 'A');
	num /= base;
    }
}

int main(int argc, char* argv[])
{
    int a, b;
    cin >> a >> b;
    stack<char> result;

    sysConv(a, b, result);

    while (!result.empty()) {
	cout << result.top();
	result.pop();
    }
    cout << endl;
    return 0;
}

