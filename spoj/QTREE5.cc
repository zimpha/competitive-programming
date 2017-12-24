#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10, inf = 1e9;

struct Edge {
    int v, nxt;
    Edge() {}
    Edge(int a, int b) :
        v(a), nxt(b) {}
} E[MAXN << 1];

struct SegTree {
    vector<int> u; int n;
    void init(int _n) {
        this->n = _n; u.assign(n << 2, 0);
    }
    void ins(int p, int v) {
        int rt = 1, l = 0, r = n;
        for (u[rt] += v; l + 1 != r; ) {
            int mid = (l + r) >> 1;
            if (p < mid) rt <<= 1, r = mid;
            else rt = rt << 1 | 1, l = mid;
            u[rt] += v;
        }
    }
    int get() {
        int rt = 1, l = 0, r = n;
        if (u[rt] == 0) return -1;
        for (; l + 1 != r; ) {
            int mid = (l + r) >> 1;
            if (u[rt << 1]) rt <<= 1, r = mid;
            else rt = rt << 1 | 1, l = mid;
        }
        return l;
    }
} ST[MAXN << 5];

struct Entry {
    int anc, dis;
    SegTree *pt;
    Entry() {}
    Entry(int a, int b, SegTree *c) :
        anc(a), dis(b), pt(c) {}
};

vector<Entry> entry[MAXN];
int G[MAXN], vis[MAXN], col[MAXN];
int sz, n, q;

namespace TreeSplit {
    int size[MAXN], dep[MAXN], tot, rt, ms;
    SegTree *pt;
    void getCenter(int u, int f = -1) {
        int mx = 0; size[u] = 1;
        for (int it = G[u]; ~it; it = E[it].nxt) {
            int v = E[it].v; if (vis[v] || v == f) continue;
            getCenter(v, u); size[u] += size[v];
            mx = max(mx, size[v]);
        }
        mx = max(mx, tot - size[u]);
        if (mx < ms) ms = mx, rt = u;
    }
    void getDepth(int u, int f = -1) {
        size[u] = 1; dep[u] = 0;
        for (int it = G[u]; ~it; it = E[it].nxt) {
            int v = E[it].v; if (v == f || vis[v]) continue;
            getDepth(v, u); size[u] += size[v];
            dep[u] = max(dep[u], dep[v] + 1);
        }
    }
    void dfs(int u, int d, int f = -1) {
        pt->ins(d, col[u]);
        entry[u].push_back(Entry(rt, d, pt));
        for (int it = G[u]; ~it; it = E[it].nxt) {
            int v = E[it].v; if (v == f || vis[v]) continue;
            dfs(v, d + 1, u);
        }
    }
    void work(int u, int _n = n) {
        tot = _n; ms = inf;
        getCenter(u); u = rt; vis[u] = true;
        getDepth(u);
        pt = &ST[sz ++];
        pt->init(dep[u] + 1);
        dfs(u, 0);
        for (int it = G[u]; ~it; it = E[it].nxt) {
            int v = E[it].v; if (vis[v]) continue;
            work(v, size[v]);
        }
    }
}

int main() {
    scanf("%d", &n); sz = 0;
    for (int i = 1; i <= n; ++ i) G[i] = -1;
    for (int i = 1; i < n; ++ i) {
        int a, b; scanf("%d%d", &a, &b);
        E[sz] = Edge(b, G[a]); G[a] = sz ++;
        E[sz] = Edge(a, G[b]); G[b] = sz ++;
    }
    sz = 0;
    TreeSplit::work(1);
    scanf("%d", &q);
    while (q --) {
        int t, u; scanf("%d%d", &t, &u);
        if (t == 0) {
            int now = col[u] ^ 1;
            for (int i = 0; i < (int)entry[u].size(); ++ i) {
                Entry &nc = entry[u][i];
                nc.pt->ins(nc.dis, now - col[u]);
            }
            col[u] ^= 1;
        }
        else {
            int ret = -1;
            for (int i = 0; i < (int)entry[u].size(); ++ i) {
                Entry &nc = entry[u][i];
                int tmp = nc.pt->get(); 
                if (tmp != -1) {
                    if (ret == -1) ret = tmp + nc.dis;
                    else ret = min(ret, tmp + nc.dis);
                }
            }
            printf("%d\n", ret);
        }
    }
    return 0;
}
