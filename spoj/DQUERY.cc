#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=30005;
const int MAXM=200005;

struct node
{
	int l, r, id;
};

map<int, int> mp;
node query[MAXM];
int A[MAXM], C[MAXN];
int next[MAXN];
int N, M;

bool cmp(node a, node b)
{
	return (a.l<b.l);
}

void add(int k, int d)
{
	for ( ; k<=N; k+=(k&-k))
		C[k]+=d;
}

int getsum(int k)
{
	int ret=0;
	for ( ; k>0; k-=(k&-k))
		ret+=C[k];
	return ret;
}

int main()
{
	scanf("%d", &N);
	memset(C, 0, sizeof(C));
	memset(next, 0, sizeof(next));
	mp.clear();
	for (int x, i=1; i<=N; i++)
	{
		scanf("%d", &x);
		map<int, int>::iterator it=mp.find(x);
		if (it==mp.end()) add(i, 1);
		else next[it->second]=i;
		mp[x]=i;
	}
	scanf("%d", &M);
	for (int i=0; i<M; i++)
	{
		scanf("%d%d", &query[i].l, &query[i].r);
		query[i].id=i;
	}
	sort(query, query+M, cmp);
	for (int i=1, j=0; i<=N; i++)
	{
		for ( ; j<M&&query[j].l==i; j++)
			A[query[j].id]=getsum(query[j].r)-getsum(i-1);
		add(i, -1);
		if (next[i]) add(next[i], 1);
	}
	for (int i=0; i<M; i++)
		printf("%d\n", A[i]);
	return 0;
}
