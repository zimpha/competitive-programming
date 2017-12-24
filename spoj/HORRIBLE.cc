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
	LL sum, tag;
};

node tree[MAXN*4];
int N, M;

inline void pushdown(int rt, int l, int r)
{
	tree[lson].tag+=tree[rt].tag;
	tree[rson].tag+=tree[rt].tag;
	tree[lson].sum+=tree[rt].tag*(mid-l+1);
	tree[rson].sum+=tree[rt].tag*(r-mid);
	tree[rt].tag=0;
}

void modify(int rt, int l, int r, int ll, int rr, int v)
{
	if (ll<=l&&rr>=r)
	{
		tree[rt].tag+=(LL)v;
		tree[rt].sum+=(LL)v*(r-l+1);
		return;
	}
	if (tree[rt].tag) pushdown(rt, l, r);
	if (ll<=mid) modify(lson, l, mid, ll, rr, v);
	if (rr>mid) modify(rson, mid+1, r, ll, rr, v);
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
}

LL query(int rt, int l, int r, int k)
{
	if (k==0) return 0;
	if (k>=r) return tree[rt].sum;
	if (tree[rt].tag) pushdown(rt, l, r);
	LL ret=query(lson, l, mid, k);
	if (k>mid) ret+=query(rson, mid+1, r, k);
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		memset(tree, 0, sizeof(tree));
		while (M--)
		{
			int opt, l, r, v;
			scanf("%d%d%d", &opt, &l, &r);
			if (opt==0)
			{
				scanf("%d", &v);
				modify(1, 1, N, l, r, v);
			}
			else printf("%lld\n", query(1, 1, N, r)-query(1, 1, N, l-1));
		}
	}
	return 0;
}
