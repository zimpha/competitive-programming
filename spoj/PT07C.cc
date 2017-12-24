#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN=200+10;
const int inf=1e9;

double dis[MAXN];
queue<int> q;
int map[MAXN][MAXN], d[MAXN][MAXN], rk[MAXN][MAXN];
int pre[MAXN], vis[MAXN];
int n, m, s1, s2;
int cur;

void floyd() {
	for (int k=0; k<n; k++) 
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
}

bool cmp(const int &a, const int &b) {
	return d[cur][a]<d[cur][b];
}

void find_center() {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) rk[i][j]=j;
		cur=i; sort(rk[i], rk[i]+n, cmp);
	}
	int ret=inf; s1=s2=-1;
	for (int u=0; u<n; u++) {
		if (d[u][rk[u][n-1]]*2<ret) {
			ret=d[u][rk[u][n-1]]*2;
			s1=s2=u; dis[s1]=0;
		}
		for (int v=0; v<n; v++) 
			if (map[u][v]!=-1) {
				for (int k=n-1, i=n-2; i>=0; i--)
					if (d[v][rk[u][i]]>d[v][rk[u][k]]) {
						int tmp=d[u][rk[u][i]]+d[v][rk[u][k]]+map[u][v];
						if (tmp<ret) {
							ret=tmp; s1=u; s2=v;
							dis[s1]=(double)tmp/2-d[u][rk[u][i]];
							dis[s2]=(double)map[u][v]-dis[s1];
						}
						k=i;
					}
			}
	}
	printf("%d\n", ret);
}

void spfa() {
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	for (int i=0; i<n; i++) if (i!=s1&&i!=s2) dis[i]=inf;
	while (!q.empty()) q.pop();
	q.push(s1); vis[s1]=true;
	if (s1!=s2) {
		q.push(s2); vis[s2]=true; pre[s2]=s1;
	}
	while (!q.empty()) {
		int u=q.front(); q.pop(); vis[u]=false;
		for (int v=0; v<n; v++) 
			if (map[u][v]!=-1&&dis[v]>dis[u]+map[u][v]) {
				dis[v]=dis[u]+map[u][v]; pre[v]=u;
				if (!vis[v]) {
					vis[v]=true;
					q.push(v);
				}				
			}
	}
}

void solve() {
	floyd();
	find_center();
	spfa();
	for (int i=0; i<n; i++)
		if (pre[i]!=-1) {
			if (i<pre[i]) printf("%d %d\n", i+1, pre[i]+1);
			else printf("%d %d\n", pre[i]+1, i+1);
		}
}

void init() {
	for (int i=0; i<n; i++) {
		d[i][i]=0;
		for (int j=i+1; j<n; j++) d[i][j]=d[j][i]=inf;
	}
	memset(map, -1, sizeof(map));
}

int main() {
	scanf("%d%d", &n, &m);
	init();
	for (int u, v, w, i=0; i<m; i++) {
		scanf("%d%d%d", &u, &v, &w); u--; v--;
		if (u==v) continue;
		if (w<d[u][v]) {
			d[u][v]=d[v][u]=w;
			map[u][v]=map[v][u]=w;
		}
	}
	solve();
	return 0;
}
