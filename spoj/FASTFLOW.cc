#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN=5000+10;
const int MAXM=30000+10;
const LL inf=(1ll<<60ll);

struct node {
	int v, next;
	LL flow;
}edge[MAXM*2];

int head[MAXN], que[MAXN], level[MAXN];
int N, M, S, T;
int cnt;

void addedge(int u, int v, LL a, LL b) {
	edge[cnt].v=v; edge[cnt].flow=a; edge[cnt].next=head[u]; head[u]=cnt++;
	edge[cnt].v=u; edge[cnt].flow=b; edge[cnt].next=head[v]; head[v]=cnt++;
}

bool dinic_bfs() {
	for (int i=1; i<=N; i++) level[i]=-1;
	level[S]=0; que[0]=S;
	for (int h=0, t=1; h<t; h++) {
		int u=que[h], v;
		for (int now=head[u]; now!=-1; now=edge[now].next)
			if (level[v=edge[now].v]==-1&&edge[now].flow>0) {
				level[v]=level[u]+1;
				que[t++]=v;
			}
	}
	return (level[T]!=-1);
}

LL dinic_dfs(int u, LL low) {
	LL ret=0, tmp;
	if (u==T) return low;
	for (int v, now=head[u]; now!=-1&&ret<low; now=edge[now].next)
		if (level[v=edge[now].v]==level[u]+1&&edge[now].flow>0)
			if (tmp=dinic_dfs(v, min(low-ret, edge[now].flow))) {
				ret+=tmp; edge[now].flow-=tmp; edge[now^1].flow+=tmp;
			}
	if (!ret) level[u]=-1;
	return ret;
}

LL dinic() {
	LL maxflow=0, t;
	while (dinic_bfs()) {
		while (t=dinic_dfs(S, inf)) maxflow+=t;
	}
	return maxflow;
}

int main() {
	scanf("%d%d", &N, &M);
	S=1; T=N; cnt=0;
	for (int i=1; i<=N; i++) head[i]=-1;
	for (int a, b, c, i=0; i<M; i++) {
		scanf("%d%d%d", &a, &b, &c);
		addedge(a, b, c, c);
	}
	printf("%lld\n", dinic());
}
