#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200000 + 10, inf = 2e9;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int a, int b) : v(a), w(b) {}
};

vector<Edge> G[MAXN];
int vis[MAXN], size[MAXN], dep[MAXN], hate[MAXN];
int N, K, M, root, mins, ret, total;

void getRoot(int u, int f) {
    size[u] = 1; int mx = 0;
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        int v = G[u][i].v; if (v == f || vis[v]) continue;
        getRoot(v, u); 
        size[u] += size[v]; mx = max(mx, size[v]);
    }
    mx = max(mx, total - size[u]);
    if (mx < mins) mins = mx, root = u;
}

void getDepth(int u, int f) {
    dep[u] = 0; size[u] = 1;
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        int v = G[u][i].v; if (v == f || vis[v]) continue;
        getDepth(v, u);
        dep[u] = max(dep[u], dep[v]); size[u] += size[v];
    }
    dep[u] += hate[u];
}

bool cmp(int a, int b) {
    return dep[G[root][a].v] < dep[G[root][b].v];
}

int F[MAXN], P[MAXN];

void dfs(int u, int f, int d, int s) {
    P[d] = max(P[d], s);
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        int v = G[u][i].v, w = G[u][i].w; if (v == f || vis[v]) continue;
        dfs(v, u, d + hate[v], s + w);
    }
}

int A[MAXN], cnt;

void work(int u) {
    mins = inf; total = size[u];
    getRoot(u, -1); 
    u = root; vis[u] = true;
    getDepth(u, -1);
    cnt = 0;
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        if (!vis[G[u][i].v]) A[cnt ++] = i;
    }
    if (cnt == 0) return;
    sort(A, A + cnt, cmp);
    for (int i = 0; i <= dep[G[root][A[cnt - 1]].v]; ++ i) F[i] = -inf;
    for (int i = 0, pre = 0; i < cnt; ++ i) {
        int v = G[u][A[i]].v, w = G[u][A[i]].w;
        for (int j = 0; j <= dep[v]; ++ j) P[j] = -inf;
        dfs(v, u, hate[v], w);
        for (int j = 0; j <= dep[v] && j <= K - hate[u]; ++ j) {
            int tmp = min(K - hate[u] - j, pre);
            if (F[tmp] != -inf && P[j] != -inf) ret = max(ret, F[tmp] + P[j]);
        }
        for (int j = 0; j <= dep[v]; ++ j) {
            F[j] = max(F[j], P[j]);
            if (j) F[j] = max(F[j], F[j - 1]);
            if (j + hate[u] <= K) ret = max(ret, P[j]);
        }
        pre = dep[v];
    }
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        if (!vis[G[u][i].v]) work(G[u][i].v);
    }
}

int main() {
    srand(time(NULL));
    scanf("%d%d%d", &N, &K, &M);
    for (int i = 0; i < M; ++ i) {
        int x; scanf("%d", &x);
        hate[x - 1] = 1;
    }
    for (int i = 1; i < N; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w); -- u, -- v;
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
    for (int i = 0; i < N; ++ i) vis[i] = false;
    ret = 0; root = rand() % N; size[root] = N;
    work(root);
    printf("%d\n", ret);
    return 0;
}
