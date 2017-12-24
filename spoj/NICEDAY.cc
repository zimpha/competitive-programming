#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

const int MAXN=100005;

struct node
{
	int a, b, c;

	friend bool operator < (node a, node b)
	{
		if (a.a!=b.a) return (a.a<b.a);
		if (a.b!=b.b) return (a.b<b.b);
		return (a.c<b.c);
	}
};

node C[MAXN];
int tree[MAXN*4];
int N;

void build(int rt, int l, int r)
{
	tree[rt]=N+1;
	if (l==r) return;
	build(lson, l, mid); build(rson, mid+1, r);
}

int modify(int rt, int l, int r, int k, int x)
{
	if (l==r) return tree[rt]=x;
	if (k<=mid) modify(lson, l, mid, k, x);
	else modify(rson, mid+1, r, k, x);
	return tree[rt]=min(tree[lson], tree[rson]);
}

int query(int rt, int l, int r, int k)
{
	if (k>=r) return tree[rt];
	int ret=query(lson, l, mid, k);
	if (k>mid) ret=min(ret, query(rson, mid+1, r, k));
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &N);
		for (int i=1; i<=N; i++)
			scanf("%d%d%d", &C[i].a, &C[i].b, &C[i].c);
		sort(C+1, C+N+1);
		build(1, 1, N);
		int ret=0;
		for (int i=1; i<=N; i++)
		{
			int tmp=query(1, 1, N, C[i].b);
			if (tmp>C[i].c) ret++;
			modify(1, 1, N, C[i].b, C[i].c);
		}
		printf("%d\n", ret);
	}
	return 0;
}
