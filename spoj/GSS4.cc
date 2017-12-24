#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

typedef long long LL;

const int MAXN=100005;

struct node
{
	LL sum, max;
};

node tree[MAXN*4];
int N, M;

void build(int rt, int l, int r)
{
	if (l==r)
	{
		LL x;
		scanf("%lld", &x);
		tree[rt].sum=tree[rt].max=x;
		return;
	}
	build(lson, l, mid);
	build(rson, mid+1, r);
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
	tree[rt].max=max(tree[lson].max, tree[rson].max);
}

void modify(int rt, int l, int r, int ll, int rr)
{
	if (tree[rt].max<=1) return;
	if (l==r)
	{
		tree[rt].sum=tree[rt].max=(LL)sqrt(tree[rt].max);
		return;
	}
	if (ll<=mid) modify(lson, l, mid, ll, rr);
	if (rr>mid) modify(rson, mid+1, r, ll, rr);
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
	tree[rt].max=max(tree[lson].max, tree[rson].max);
}

LL query(int rt, int l, int r, int k)
{
	if (k<=0) return 0ll;
	if (k>=r) return tree[rt].sum;
	LL ret=query(lson, l, mid, k);
	if (k>mid) ret+=query(rson, mid+1, r, k);
	return ret;
}

int main()
{
	int cas=0;
	while (scanf("%d", &N)==1)
	{
		build(1, 1, N);
		scanf("%d", &M);
		printf("Case #%d:\n", ++cas);
		while (M--)
		{
			int opt, x, y;
			scanf("%d%d%d", &opt, &x, &y);
			if (x>y) swap(x, y);
			if (opt==0) modify(1, 1, N, x, y);
			else
			{
				LL s1=query(1, 1, N, x-1);
				LL s2=query(1, 1, N, y);
				printf("%lld\n", s2-s1);
			}
		}
		puts("");
	}
	return 0;
}

