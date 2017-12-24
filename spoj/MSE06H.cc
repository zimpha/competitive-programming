#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int MAXN=1005;
const int MAXK=1000005;

struct node
{
	int l, r;
};

node seg[MAXK];
int C[MAXN];
int N, M, K;

bool cmp(node a, node b)
{
	if (a.l==b.l) return (a.r<b.r);
	else return (a.l<b.l);
}

void add(int k, int d)
{
	for ( ; k>0; k-=(k&-k))
		C[k]+=d;
}

int getsum(int k)
{
	int ret=0;
	for ( ; k<=M; k+=(k&-k))
		ret+=C[k];
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int cas=1; cas<=T; cas++)
	{
		scanf("%d%d%d", &N, &M, &K);
		for (int i=1; i<=K; i++)
			scanf("%d%d", &seg[i].l, &seg[i].r);
		std::sort(seg+1, seg+1+K, cmp);
		memset(C, 0, sizeof(C));
		long long ret=0;
		for (int i=1; i<=K; i++)
		{
			int tmp=getsum(seg[i].r+1);
			ret+=(long long)tmp;
			add(seg[i].r, 1);
		}
		printf("Test case %d: %lld\n", cas, ret);
	}
	return 0;
}

