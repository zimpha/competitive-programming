#include <cstdio>
#include <cstring>
#include <cstdlib>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

const int MAXN=100005;

struct node
{
	int sum, tag;
};

node tree[MAXN*4];
int N, M;

void build(int rt, int l, int r)
{
	tree[rt].sum=tree[rt].tag=0;
	if (l==r) return;
	build(lson, l, mid);
	build(rson, mid+1, r);
}

inline void pushdown(int rt, int l, int r)
{
	tree[lson].tag^=1;
	tree[rson].tag^=1;
	tree[lson].sum=mid-l+1-tree[lson].sum;
	tree[rson].sum=r-mid-tree[rson].sum;
	tree[rt].tag=0;
}

void modify(int rt, int l, int r, int ll, int rr)
{
	if (ll<=l&&rr>=r)
	{
		tree[rt].tag^=1;
		tree[rt].sum=r-l+1-tree[rt].sum;
		return;
	}
	if (tree[rt].tag) pushdown(rt, l, r);
	if (ll<=mid) modify(lson, l, mid, ll, rr);
	if (rr>mid) modify(rson, mid+1, r, ll, rr);
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
}

int query(int rt, int l, int r, int ll, int rr)
{
	if (ll<=l&&rr>=r) return tree[rt].sum;
	if (tree[rt].tag) pushdown(rt, l, r);
	int ret=0;
	if (ll<=mid) ret+=query(lson, l, mid, ll, rr);
	if (rr>mid) ret+=query(rson, mid+1, r, ll, rr);
	return ret;
}

int main()
{
	while (scanf("%d%d", &N, &M)==2)
	{
		build(1, 1, N);
		while (M--)
		{
			int opt, l, r;
			scanf("%d%d%d", &opt, &l, &r);
			if (opt==0) modify(1, 1, N, l, r);
			else printf("%d\n", query(1, 1, N, l, r));
		}
	}
	return 0;
}
