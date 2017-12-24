#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

const int MAXN=50005;

struct node
{
	int lc, rc, mc, sum;
};

node tree[MAXN*4];
int N, M;

inline void update(int rt)
{
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
	tree[rt].mc=max(tree[lson].rc+tree[rson].lc, max(tree[lson].mc, tree[rson].mc));
	tree[rt].lc=max(tree[lson].lc, tree[lson].sum+tree[rson].lc);
	tree[rt].rc=max(tree[rson].rc, tree[rson].sum+tree[lson].rc);
}

void build(int rt, int l, int r)
{
	if (l==r)
	{
		int x;
		scanf("%d", &x);
		tree[rt].lc=tree[rt].rc=tree[rt].mc=tree[rt].sum=x;
		return;
	}
	build(lson, l, mid);
	build(rson, mid+1, r);
	update(rt);
}

node query(int rt, int l, int r, int ll, int rr)
{
	if (ll==l&&rr==r) return tree[rt];
	if (rr<=mid) return query(lson, l, mid, ll, rr);
	else if (ll>mid) return query(rson, mid+1, r, ll, rr);
	else
	{
		node left, right, ret;
		left=query(lson, l, mid, ll, mid);
		right=query(rson, mid+1, r, mid+1, rr);
		ret.sum=left.sum+right.sum;
		ret.lc=max(left.lc, left.sum+right.lc);
		ret.rc=max(right.rc, right.sum+left.rc);
		ret.mc=max(left.rc+right.lc, max(left.mc, right.mc));
		return ret;
	}
}

int main()
{
	scanf("%d", &N);
	build(1, 1, N);
	scanf("%d", &M);
	while (M--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(1, 1, N, l, r).mc);
	}
	return 0;
}
