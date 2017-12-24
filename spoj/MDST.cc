#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN=1000+10;
const int MAXM=100000+10;
const int inf=1e9;

struct node {
	int u, v;
	int next;
}E[MAXM], edge[MAXM];
bool vis[MAXN];
int map[MAXN][MAXN], dis[MAXN][MAXN];
int head[MAXN], rk[MAXN][MAXN];
int que[MAXN];
int n, m, cnt, cur;

inline void addedge(int u, int v) {
	E[cnt].v=v; E[cnt].next=head[u]; head[u]=cnt++;
}

void bfs(int s, int *dis) {
	//while (!q.empty()) q.pop();
	fill(vis, vis+n+1, false);
	fill(dis, dis+n+1, inf);
	que[0]=s; vis[s]=true; dis[s]=0;
	for (int h=0, t=1; h<t; h++) {
		int u=que[h], v;
		for (int now=head[u]; now!=-1; now=E[now].next) 
			if (!vis[v=E[now].v]) {
				vis[v]=true; dis[v]=dis[u]+1;
				que[t++]=v;
			}
	}
	/*q.push(s); vis[s]=true; dis[s]=0;
	while (!q.empty()) {
		int v, u=q.front(); q.pop();
		for (int now=head[u]; now!=-1; now=E[now].next) 
			if (!vis[v=E[now].v]) {
				vis[v]=true; dis[v]=dis[u]+1;
				q.push(v);
			}
	}*/
}


bool cmp(int a, int b) {
	return dis[cur][a]<dis[cur][b];
}

void find_center() {
	for (int i=1; i<=n; i++) bfs(i, dis[i]);
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) rk[i][j]=j;
		cur=i; sort(rk[i]+1, rk[i]+n+1, cmp);
	}
	int ret=inf;
	for (int i=0; i<m; i++) {
		int u=edge[i].u, v=edge[i].v;
		if (map[u][v]==-1) continue;
		ret=min(ret, dis[u][rk[u][n]]<<1);
		ret=min(ret, dis[v][rk[v][n]]<<1);
		for (int j=n-1, t=n; j>=1; j--) 
			if (dis[v][rk[u][j]]>dis[v][rk[u][t]]) {
				int tmp=dis[u][rk[u][j]]+dis[v][rk[u][t]]+map[u][v];
				if (tmp<ret) ret=tmp;;
				t=j;
			}
	}
	printf("%d\n", (ret==inf)?0:ret);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		m=cnt=0; fill(head, head+n+1, -1);
		memset(map, -1, sizeof(map));
		for (int k, u, i=0; i<n; i++) {
			scanf("%d%d", &u, &k);
			for (int v, j=0; j<k; j++) {
				scanf("%d", &v);
				addedge(u, v); addedge(v, u);
				map[u][v]=map[v][u]=1;
				edge[m].u=u; edge[m++].v=v;
			}
		}
		find_center();
	}
	return 0;
}
