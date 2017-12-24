#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

const int MAXN=200005;
const int inf=100000000;

long long ret;
int A[MAXN], B[MAXN];
int N;

void MergeSort(int l, int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	MergeSort(l, mid); MergeSort(mid+1, r);
	for (int i=l; i<=mid; i++) B[i]=A[i];
	for (int i=mid+1; i<=r; i++) B[i+1]=A[i];
	B[mid+1]=B[r+2]=inf;
	int i=l, j=mid+2;
	for (int k=l; k<=r; k++)
	{
		if (B[i]<=B[j]) A[k]=B[i++];
		else A[k]=B[j++], ret+=(long long)mid-i+1;
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int i=1; i<=N; i++)
			scanf("%d", &A[i]);
		ret=0;
		MergeSort(1, N);
		printf("%lld\n", ret);
	}
	return 0;
}

