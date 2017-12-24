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
	LL s1, s2, cover, add;
	bool flag;
};

node tree[MAXN*4];
int N, M;

inline void update(int rt)
{
	tree[rt].s1=tree[lson].s1+tree[rson].s1;
	tree[rt].s2=tree[lson].s2+tree[rson].s2;
}

void build(int rt, int l, int r)
{
	tree[rt].cover=tree[rt].add=0ll;
	tree[rt].flag=false;
	if (l==r)
	{
		LL x;
		scanf("%lld", &x);
		tree[rt].s1=x; tree[rt].s2=x*x;
		return;
	}
	build(lson, l, mid); build(rson, mid+1, r);
	update(rt);
}

inline void change0(int rt, int l, int r, LL x)
{
	tree[rt].flag=true; tree[rt].cover=x; tree[rt].add=0;
	tree[rt].s1=x*(r-l+1); tree[rt].s2=x*x*(r-l+1);
}

inline void change1(int rt, int l, int r, LL x)
{
	tree[rt].add+=x;
	tree[rt].s2+=2ll*x*tree[rt].s1+x*x*(r-l+1);
	tree[rt].s1+=x*(r-l+1);
}

inline void pushdown(int rt, int l, int r)
{
	if (tree[rt].flag)
	{
		change0(lson, l, mid, tree[rt].cover);
		change0(rson, mid+1, r, tree[rt].cover);
	}
	if (tree[rt].add)
	{
		change1(lson, l, mid, tree[rt].add);
		change1(rson, mid+1, r, tree[rt].add);
	}
	tree[rt].flag=false; tree[rt].cover=tree[rt].add=0;
}

void add(int rt, int l, int r, int ll, int rr, int x)
{
	if (ll<=l&&rr>=r)
	{
		change1(rt, l, r, (LL)x);
		return;
	}
	pushdown(rt, l, r);
	if (ll<=mid) add(lson, l, mid, ll, rr, x);
	if (rr>mid) add(rson, mid+1, r, ll, rr, x);
	update(rt);
}

void cover(int rt, int l, int r, int ll, int rr, int x)
{
	if (ll<=l&&rr>=r)
	{
		change0(rt, l, r, (LL)x);
		return;
	}
	pushdown(rt, l, r);
	if (ll<=mid) cover(lson, l, mid, ll, rr, x);
	if (rr>mid) cover(rson, mid+1, r, ll, rr, x);
	update(rt);
}

LL query(int rt, int l, int r, int ll, int rr)
{
	if (ll<=l&&rr>=r) return tree[rt].s2;
	pushdown(rt, l, r);
	LL ret=0;
	if (ll<=mid) ret+=query(lson, l, mid, ll, rr);
	if (rr>mid) ret+=query(rson, mid+1, r, ll, rr);
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int cas=1; cas<=T; cas++)
	{
		scanf("%d%d", &N, &M);
		build(1, 1, N);
		printf("Case %d:\n", cas);
		while (M--)
		{
			int opt, l, r;
			int x;
			scanf("%d%d%d", &opt, &l, &r);
			if (opt==0) 
			{
				scanf("%d", &x);
				cover(1, 1, N, l, r, x);
			}
			else if (opt==1)
			{
				scanf("%d", &x);
				add(1, 1, N, l, r, x);
			}
			else printf("%lld\n", query(1, 1, N, l, r));
		}
	}
	return 0;
}
