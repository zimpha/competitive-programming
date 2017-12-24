#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=100005;
const int SIZE=505;
const int P=500;

struct node
{
	int l, r, size;
};

node blk[SIZE];
int pos[MAXN];
int A[MAXN], B[MAXN];
int N, M, Q;

int main()
{
	scanf("%d%d", &N, &Q); M=0;
	for (int i=0; i<N; i++)
	{
		scanf("%d", &A[i]); pos[i]=i/P;
		if (i%P==0)
		{
			blk[M].l=i; blk[M].r=min(i+P, N);
			blk[M].size=blk[M].r-blk[M].l;
			M++;
		}
	}
	memcpy(B, A, sizeof(A));
	for (int i=0; i<M; i++) sort(B+blk[i].l, B+blk[i].r);
	while (Q--)
	{
		char st[10];
		int l, r, x;
		int pl, pr;
		scanf("%s", st);
		if (st[0]=='M')
		{
			scanf("%d%d", &l, &x); l--;
			pl=pos[l]; A[l]=x;
			memcpy(B+blk[pl].l, A+blk[pl].l, sizeof(int)*blk[pl].size);
			sort(B+blk[pl].l, B+blk[pl].r);
		}
		else if (st[0]=='C')
		{
			scanf("%d%d%d", &l, &r, &x); l--; r--;
			pl=pos[l]; pr=pos[r];
			int ret=0;
			if (pl==pr)
			{
				for (int i=l; i<=r; i++) ret+=(A[i]<=x);
			}
			else
			{
				for (int i=l; i<blk[pl].r; i++) ret+=(A[i]<=x);
				for (int i=blk[pr].l; i<=r; i++) ret+=(A[i]<=x);
				for (int i=pl+1; i<pr; i++)
				{
					int k=upper_bound(B+blk[i].l, B+blk[i].r, x)-(B+blk[i].l);
					ret+=k;
				}
			}
			printf("%d\n", ret);
		}
	}
	return 0;
}
