#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN=30005;

map<string, int> mp;
int C[MAXN], A[MAXN];
int N;

void add(int k)
{
	for ( ; k>0; k-=(k&-k))
		C[k]++;
}

int getsum(int k)
{
	int ret=0;
	for ( ; k<=N; k+=(k&-k))
		ret+=C[k];
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		char str[30];
		mp.clear();
		scanf("%d", &N);
		for (int i=1; i<=N; i++)
		{
			scanf("%s", str);
			mp[str]=i;
		}
		for (int i=1; i<=N; i++)
		{
			scanf("%s", str);
			A[i]=mp[str];
		}
		memset(C, 0, sizeof(C));
		int ret=0;
		for (int i=1; i<=N; i++)
		{
			ret+=getsum(A[i]+1);
			add(A[i]);
		}
		printf("%d\n", ret);
	}
	return 0;
}
