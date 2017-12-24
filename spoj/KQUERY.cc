#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int MAXQ=200005;
const int MAXN=30005;

struct node1
{
	int l, r, k;
	int id;
};

struct node2
{
	int x, id;
};

node1 query[MAXQ];
node2 A[MAXN];
int ans[MAXQ];
int C[MAXN];
int N, Q;

bool cmp1(node1 a, node1 b)
{
	return (a.k>b.k);
}

bool cmp2(node2 a, node2 b)
{
	return (a.x>b.x);
}

void add(int idx)
{
	for (int i=idx; i<=N; i+=(i&-i))
		C[i]++;
}

int getsum(int idx)
{
	int ret=0;
	for (int i=idx; i>0; i-=(i&-i))
		ret+=C[i];
	return ret;
}

int main()
{
	//cin >> N;
	scanf("%d", &N);
	for (int i=0; i<N; i++) {
		//cin >> A[i].x;
		scanf("%d", &A[i].x);
		A[i].id=i+1;
	}
	//cin >> Q;
	scanf("%d", &Q);
	for (int i=0; i<Q; i++) {
		//cin >> query[i].l >> query[i].r >> query[i].k;
		scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
		query[i].id=i;
	}
	sort(query, query+Q, cmp1);
	sort(A, A+N, cmp2);
	memset(C, 0, sizeof(C));
	for (int j=0, i=0; i<Q; i++) {
		while (j<N&&A[j].x>query[i].k) {
			add(A[j].id);
			j++;
		}
		ans[query[i].id]=getsum(query[i].r)-getsum(query[i].l-1);
	}
	for (int i=0; i<Q; i++) {
		//cout << ans[i] << endl;
		printf("%d\n", ans[i]);
	}
	return 0;
}
