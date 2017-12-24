#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN=100005;

int H[MAXN], A[MAXN], B[MAXN];
int N;

LL calc()
{
	A[1]=0;
	for (int i=2; i<=N; i++)
	{
		int j=i-1;
		for ( ; H[j]>=H[i]; j=A[j]);
		A[i]=j;
	}
	B[N]=N+1;
	for (int i=N-1; i>0; i--)
	{
		int j=i+1;
		for ( ; H[j]>=H[i]; j=B[j]);
		B[i]=j;
	}
	LL ret=0;
	for (int i=1; i<=N; i++)
		ret=max(ret, (LL)H[i]*(B[i]-A[i]-1));
	return ret;
}

int main()
{
	while (scanf("%d", &N)==1&&N)
	{
		memset(H, -1, sizeof(H));
		for (int i=1; i<=N; i++)
			scanf("%d", &H[i]);
		LL ans=calc();
		printf("%lld\n", ans);
	}
	return 0;
}
