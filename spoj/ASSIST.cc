#include <cstdio>
#include <cstring>
#include <cstdlib>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

const int MAXN=3005;
const int SIZE=34005;

int tree[SIZE*4];
int tmp[SIZE];
int ans[MAXN];
int N;

void build(int rt, int l, int r)
{
	tree[rt]=r-l+1;
	if (l==r) return;
	build(lson, l, mid);
	build(rson, mid+1, r);
}

void modify(int rt, int l, int r, int k)
{
	if (l==r)
	{
		tree[rt]=0;
		return;
	}
	if (k<=mid) modify(lson, l, mid, k);
	else modify(rson, mid+1, r, k);
	tree[rt]=tree[lson]+tree[rson];
}

int query(int rt, int l, int r, int k)
{
	if (l==r) return l;
	if (tree[lson]>=k) return query(lson, l, mid, k);
	else return query(rson, mid+1, r, k-tree[lson]);
}

void calc(int N, int M)
{
	build(1, 2, M);
	for (int i=1; i<=N; i++)
	{
		ans[i]=query(1, 2, M, 1);
		modify(1, 2, M, ans[i]);
		int cnt=0;
		for (int j=ans[i]; j<=tree[1]; j+=ans[i])
			tmp[cnt++]=query(1, 2, M, j);
		for (int j=0; j<cnt; j++)
			modify(1, 2, M, tmp[j]);
	}
}

int main()
{
	calc(3000, 34000);
	while (scanf("%d", &N)==1&&N)
	{
		printf("%d\n", ans[N]);
	}
	return 0;
}
