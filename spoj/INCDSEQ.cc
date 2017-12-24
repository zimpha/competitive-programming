#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXK=55;
const int MAXN=10005;
const int MOD=5000000;

bool vis[MAXN];
int S[MAXN], A[MAXN];
int C[MAXK][MAXN];
int N, K, M;

int get_id(int l, int r, int x)
{
	while (l<=r)
	{
		int m=(l+r)>>1;
		if (A[m]==x) return m;
		if (A[m]<x) l=m+1;
		else r=m-1;
	}
	return -1;
}

inline int lowbit(int k)
{
	return k&-k;
}

void add(int C[], int k0, int d)
{
	for (int k=k0; k<=M; k+=lowbit(k))
		C[k]=(C[k]+d)%MOD;
}

int getsum(int C[], int k0)
{
	int ret=0;
	for (int k=k0; k>0; k-=lowbit(k))
		ret=(ret+C[k])%MOD;
	return ret;
}

int main()
{
	scanf("%d%d", &N, &K);
	for (int i=1; i<=N; i++)
		scanf("%d", &S[i]);
	memcpy(A, S, sizeof(S));
	sort(A+1, A+1+N);
	M=1;
	for (int i=2; i<=N; i++)
		if (A[i]!=A[i-1]) A[++M]=A[i];
	memset(C, 0, sizeof(C));
	memset(vis, 0, sizeof(vis));
	for (int i=1; i<=N; i++)
	{
		int x=get_id(1, M, S[i]);
		for (int j=K; j>1; j--)
			add(C[j], x, getsum(C[j-1], x-1)-getsum(C[j], x)+getsum(C[j], x-1));
			if (!vis[x])
			{
				add(C[1], x, 1);
				vis[x]=true;
			}
	}
	printf("%d\n", getsum(C[K], M)%MOD);
	return 0;
}
