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
	int sum[3], tag;
};

node tree[MAXN*4];
int N, M;

void build(int rt, int l, int r)
{
	tree[rt].sum[0]=r-l+1;
	tree[rt].sum[1]=tree[rt].sum[2]=tree[rt].tag=0;
	if (l==r) return;
	build(lson, l, mid);
	build(rson, mid+1, r);
}

inline void change(int sum[3], int d)
{
	int tmp[3];
	for (int i=0; i<3; i++)
		tmp[(i+d)%3]=sum[i];
	for (int i=0; i<3; i++)
		sum[i]=tmp[i];
}

inline void update(int rt)
{
	for (int i=0; i<3; i++)
		tree[rt].sum[i]=tree[lson].sum[i]+tree[rson].sum[i];
}

inline void pushdown(int rt)
{
	tree[lson].tag+=tree[rt].tag;
	tree[rson].tag+=tree[rt].tag;
	change(tree[lson].sum, tree[rt].tag);
	change(tree[rson].sum, tree[rt].tag);
	tree[rt].tag=0;
}

void modify(int rt, int l, int r, int ll, int rr)
{
	if (ll<=l&&rr>=r)
	{
		tree[rt].tag=(tree[rt].tag+1)%3;
		change(tree[rt].sum, 1);
		return;
	}
	if (tree[rt].tag) pushdown(rt);
	if (ll<=mid) modify(lson, l, mid, ll, rr);
	if (rr>mid) modify(rson, mid+1, r, ll, rr);
	update(rt);
}

int query(int rt, int l, int r, int k)
{
	if (k<=0) return 0;
	if (k>=r) return tree[rt].sum[0];
	if (tree[rt].tag) pushdown(rt);
	int ret=query(lson, l, mid, k);
	if (k>mid) ret+=query(rson, mid+1, r, k);
	return ret;
}

int main()
{
	scanf("%d%d", &N, &M);
	build(1, 1, N);
	while (M--)
	{
		int opt, A, B;
		scanf("%d%d%d", &opt, &A, &B);
		A++; B++;
		if (opt==0) modify(1, 1, N, A, B);
		else
		{
			int s1=query(1, 1, N, A-1);
			int s2=query(1, 1, N, B);
			printf("%d\n", s2-s1);
		}
	}
}
