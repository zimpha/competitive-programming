#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
int main()
{
	int n, m, a;
	scanf("%d%d%d", &n, &m, &a);
	n=(n%a)?(n/a+1):(n/a);
	m=(m%a)?(m/a+1):(m/a);
	cout << (long long)n*m << endl;
}
