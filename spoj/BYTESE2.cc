#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=205;

struct node
{
	int s, t;
};

node A[MAXN];
int N;

bool cmp(node a, node b)
{
	if (a.s==b.s) return (a.t>b.t);
	else return (a.s<b.s);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int l, r, i=1; i<=N; i++)
		{
			scanf("%d%d", &l, &r);
			A[2*i-1].s=l; A[2*i].s=r;
			A[2*i-1].t=1; A[2*i].t=-1;
		}
		N*=2;
		sort(A+1, A+1+N, cmp);
		int cnt=0, ret=0;
		for (int i=1; i<=N; i++)
		{
			cnt+=A[i].t;
			if (cnt>ret) ret=cnt;
		}
		printf("%d\n", ret);
	}
	return 0;
}
