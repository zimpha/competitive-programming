#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

const int MAXN=30005;

struct node
{
	int min, sum;
};

node tree[MAXN*4];
int N, M;

inline void update(int rt)
{
	tree[rt].sum=tree[lson].sum+tree[rson].sum;
	tree[rt].min=min(tree[lson].min, tree[lson].sum+tree[rson].min);
}

void build(int rt, int l, int r)
{
	if (l==r)
	{
		char ch=getchar();
		if (ch=='(') tree[rt].sum=tree[rt].min=1;
		else tree[rt].sum=tree[rt].min=-1;
		return;
	}
	build(lson, l, mid);
	build(rson, mid+1, r);
	update(rt);
}

void modify(int rt, int l, int r, int k)
{
	if (l==r)
	{
		tree[rt].sum=-tree[rt].sum;
		tree[rt].min=-tree[rt].min;
		return;
	}
	if (k<=mid) modify(lson, l, mid, k);
	else modify(rson, mid+1, r, k);
	update(rt);
}

int main()
{
	int cas=0;
	while (scanf("%d\n", &N)==1)
	{
		build(1, 1, N);
		printf("Test %d:\n", ++cas);
		scanf("%d", &M);
		while (M--)
		{
			int x;
			scanf("%d", &x);
			if (x==0)
			{
				if (tree[1].sum==0&&tree[1].min>=0) puts("YES");
				else puts("NO");
			}
			else modify(1, 1, N, x);
		}
	}
	return 0;
}
