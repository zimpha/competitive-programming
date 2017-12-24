#include <cstdio>
#include <cstring>
#include <cstdlib>

#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

const int MAXN=20005;

int tree[MAXN*4];
int ans[MAXN];
int N;

void build(int rt, int l, int r)
{
	tree[rt]=r-l+1;
	if (l==r) return;
	build(lson, l, mid); build(rson, mid+1, r);
}

int query(int rt, int l, int r, int k)
{
	tree[rt]--;
	if (l==r) return l;
	if (tree[lson]>=k) return query(lson, l, mid, k);
	else return query(rson, mid+1, r, k-tree[lson]);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		build(1, 1, N);
		for (int i=1, next=2; i<=N; i++)
		{
			int pos=query(1, 1, N, next);
			if (N!=i) next=(next+i+1)%(N-i);
			else next=1;
			if (next==0) next=N-i;
			ans[pos]=i;
		}
		for (int i=1; i<=N; i++)
			printf("%d%c", ans[i], (i==N)?'\n':' ');
	}
	return 0;
}
