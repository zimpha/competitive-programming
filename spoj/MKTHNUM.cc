#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN=100005;
const int SIZE=20;

struct node
{
	int num[MAXN];
	int cnt[MAXN];
};

node tree[SIZE];
int tmp[MAXN];
int N, M;

void build(int dep, int l, int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	int il=l, ir=mid+1;
	int same=0;
	for (int i=mid; tmp[i]==tmp[mid]&&i>0; i--, same++);
	int cnt_left=0;
	for (int i=l; i<=r; i++)
	{
		if (tree[dep].num[i]<tmp[mid])
		{
			tree[dep+1].num[il++]=tree[dep].num[i];
			cnt_left++;
		}
		else if (tree[dep].num[i]==tmp[mid]&&same)
		{
			tree[dep+1].num[il++]=tree[dep].num[i];
			cnt_left++; same--;
		}
		else tree[dep+1].num[ir++]=tree[dep].num[i];
		tree[dep].cnt[i]=cnt_left;
	}
	build(dep+1, l, mid);
	build(dep+1, mid+1, r);
}

int query(int dep, int l, int r, int ll, int rr, int k)
{
	if (l==r) return tree[dep].num[l];
	int mid=(l+r)>>1;
	int left, cnt_left;
	int newl, newr;
	if (ll==l) left=0;
	else left=tree[dep].cnt[ll-1];
	cnt_left=tree[dep].cnt[rr]-left;
	if (cnt_left>=k)
	{
		newl=l+left;
		newr=newl+cnt_left-1;
		return query(dep+1, l, mid, newl, newr, k);
	}
	else
	{
		newl=mid+1+(ll-l-left);
		newr=newl+(rr-ll+1-cnt_left)-1;
		return query(dep+1, mid+1, r, newl, newr, k-cnt_left);
	}
}

int main()
{
	while (scanf("%d%d", &N, &M)==2)
	{
		memset(tree, 0, sizeof(tree));
		for (int i=1; i<=N; i++)
		{
			scanf("%d", &tmp[i]);
			tree[0].num[i]=tmp[i];
		}
		sort(tmp+1, tmp+N+1);
		build(0, 1, N);
		while (M--)
		{
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", query(0, 1, N, l, r, k));
		}
	}
	return 0;
}
