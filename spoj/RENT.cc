#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

const int MAXN=20005;

struct ORDER
{
	int l, r, p;
};

ORDER order[MAXN];
int tree[MAXN*4];
int C[MAXN];
int N, cnt;

bool cmp(ORDER a, ORDER b)
{
	return (a.r<b.r);
}

int get_id(int l, int r, int x)
{
	while (l<=r)
	{
		int m=(l+r)>>1;
		if (C[m]==x) return m;
		if (C[m]<x) l=m+1;
		else r=m-1;
	}
	return -1;
}

void build(int rt, int l, int r)
{
	tree[rt]=0;
	if (l==r) return;
	build(lson, l, mid);
	build(rson, mid+1, r);
}

void modify(int rt, int l, int r, int k, int val)
{
	if (l==r)
	{
		if (tree[rt]<val) tree[rt]=val;
		return;
	}
	if (k<=mid) modify(lson, l, mid, k, val);
	else modify(rson, mid+1, r, k, val);
	tree[rt]=max(tree[lson], tree[rson]);
}

int query(int rt, int l, int r, int ll, int rr)
{
	if (ll>rr) return 0;
	if (ll<=l&&rr>=r) return tree[rt];
	int ret=0;
	if (ll<=mid) ret=max(ret, query(lson, l, mid, ll, rr));
	if (rr>mid) ret=max(ret, query(rson, mid+1, r, ll, rr));
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int i=1; i<=N; i++)
		{
			scanf("%d%d%d", &order[i].l, &order[i].r, &order[i].p);
			order[i].r+=order[i].l-1;
			C[2*i-1]=order[i].l; C[2*i]=order[i].r;
		}
		sort(C+1, C+1+2*N);
		sort(order+1, order+1+N, cmp);
		cnt=1;
		for (int i=2; i<=2*N; i++)
			if (C[i]!=C[i-1]) C[++cnt]=C[i];
		build(1, 1, cnt);
		for (int i=1; i<=N; i++)
		{
			int l=get_id(1, cnt, order[i].l);
			int r=get_id(1, cnt, order[i].r);
			int tmp=query(1, 1, cnt, 1, l-1)+order[i].p;
			modify(1, 1, cnt, r, tmp);
		}
		printf("%d\n", tree[1]);
	}
	return 0;
}
