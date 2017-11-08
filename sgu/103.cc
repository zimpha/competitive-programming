#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 300 + 10;
const int inf = 1e9;

int dis[MAXN], vis[MAXN], G[MAXN][MAXN], pre[MAXN];
int period[MAXN][2], remain[MAXN], color[MAXN];

void gao(int n, int nowtime, int &nowcolor, int &nexttime) {
	if (nowtime < remain[n]) nexttime = remain[n], nowcolor = color[n];
	else {
		int tmp = (nowtime - remain[n]) % (period[n][0] + period[n][1]);
		nowtime = nowtime - tmp;
		if (color[n] == 1) {
			if (tmp < period[n][0]) nowcolor = 0, nexttime = nowtime + period[n][0];
			else nowcolor = 1, nexttime = nowtime + period[n][0] + period[n][1];
		}
		else {
			if (tmp < period[n][1]) nowcolor = 1, nexttime = nowtime + period[n][1];
			else nowcolor = 0, nexttime = nowtime + period[n][0] + period[n][1];
		}
	}
}

int calcTime(int a, int b, int nowtime, int f) {
	int ca, cb, ta, tb;
	gao(a, nowtime, ca, ta); gao(b, nowtime, cb, tb);
	if (ca == cb) return nowtime;
	if (ta == tb) {
		if (f == 0) return calcTime(a, b, ta, 1);
		else if (nowtime <= remain[a] || nowtime <= remain[b]) return calcTime(a, b, ta, 1);
		else return inf;
	}
	return min(ta, tb);
}

int main() {
	int src, tar; scanf("%d%d", &src, &tar);
	int N, M; scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++ i) {
		char st[10]; scanf("%s%d%d%d", st, remain + i, &period[i][0], &period[i][1]);
		color[i] = (st[0] != 'B');
		dis[i] = inf; vis[i] = false;
	}
	for (int i = 0; i < M; ++ i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		G[u][v] = G[v][u] = w;
	}
	dis[src] = 0; vis[src] = true; pre[src] = -1;
	queue<int> Q; Q.push(src); 
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); vis[u] = false;
		for (int v = 1; v <= N; ++ v) {
			if (!G[u][v]) continue;
			int cost = calcTime(u, v, dis[u], 0);
			if (cost >= inf) continue;
			if (cost + G[u][v] < dis[v]) {
				dis[v] = cost + G[u][v]; pre[v] = u;
				if (!vis[v]) Q.push(v), vis[v] = true;
			}
		}
	}
	if (dis[tar] == inf) puts("0");
	else {
		printf("%d\n", dis[tar]); N = 0;
		for (int u = tar; u != -1; u = pre[u]) dis[N ++] = u;
		for (int i = N - 1; i >= 0; -- i) {
			printf("%d%c", dis[i], " \n"[i == 0]);
		}
	}
	return 0;
}
