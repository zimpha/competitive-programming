#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10, BLK = 333;
vector<int> G[MAXN];
map<int, int> mp;
int father[MAXN][17], dfn[MAXN], pt[MAXN];
int col[MAXN], dep[MAXN], N, Q, sz;
int st[MAXN], ed[MAXN], tid;

namespace SegTree {
}

namespace LCA {
    static const int POW = 16;
    void build() {
        for (int i = 1; (1 << i) <= N; ++ i) {
            for (int j = 1; j <= N; ++ j) {
                if (father[j][i - 1] == 0) continue;
                father[j][i] = father[father[j][i - 1]][i - 1];
            }
        }
    }
    int up(int u, int d) {
        for (int i = 0; d; ++ i, d >>= 1) {
            if (d & 1) u = father[u][i];
        }
        return u;
    }
    int ask(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = up(u, dep[u] - dep[v]);
        for (int i = POW; i >= 0; -- i) {
            if (father[u][i] == father[v][i]) continue;
            u = father[u][i]; v = father[v][i];
        }
        if (u != v) u = father[u][0];
        return u;
    }
}

struct Query {
    int l, r, i;
    Query() {}
    Query(int l, int r, int i) : l(l), r(r), i(i) {}
    const bool operator <(const Query &rhs) const {
        int bl1 = l / BLK, bl2 = rhs.l / BLK;
        if (bl1 == bl2) return r < rhs.r;
        else return bl1 < bl2;
    }
} q[MAXN];

bool isAnc(int u, int v) {
    return st[u] <= st[v] && ed[u] >= ed[v];
}

namespace COT2 {
    int ans[MAXN], cnt[MAXN], sz;
    bool vis[MAXN];
    int x, y, z;

    bool onWay(int v, int x, int y, int z) {
        return (isAnc(z, v) && (isAnc(v, x) || isAnc(v, y)));
    }

    inline void add(int x) {
        if ((++ cnt[x]) == 1) ++ sz;
    }

    inline void del(int x) {
        if ((-- cnt[x]) == 0) -- sz;
    }

    void gao(int v) {
        if (onWay(v, x, y, z)) {
            if (!vis[v]) {
                vis[v] = true; add(col[v]);
            }
        }
        else if (vis[v]) {
            vis[v] = false; del(col[v]);
        }
    }

    void go(int v, int to) {
        int z = LCA::ask(v, to);
        while (v != z) {
            gao(v);
            v = father[v][0];
        }
        gao(z); v = to;
        while (v != z) {
            gao(v);
            v = father[v][0];
        }
    }
    void solve() {
        int v1 = 1, v2 = 1;
        x = y = z = 1; sz = 0;
        gao(v1);
        for (int i = 0; i < Q; ++ i) {
            x = q[i].l, y = q[i].r, z = LCA::ask(x, y);
            go(v1, q[i].l); v1 = q[i].l;
            go(v2, q[i].r); v2 = q[i].r;
            ans[q[i].i] = sz;
        }
    }
}

void dfs(int u, int p) {
    dfn[u] = sz; pt[sz ++] = u;
    st[u] = ++ tid;
    father[u][0] = p; dep[u] = dep[p] + 1;
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        int v = G[u][i]; if (v == p) continue;
        dfs(v, u);
    }
    ed[u] = ++ tid;
}

int main() {
    scanf("%d%d", &N, &Q); mp.clear();
    for (int i = 1, cc = 0; i <= N; ++ i) {
        int x; scanf("%d", &x); 
        if (!mp.count(x)) mp[x] = cc ++;
        col[i] = mp[x];
    }
    for (int i = 1; i < N; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y); G[y].push_back(x);
    }
    tid = sz = 0; dfs(1, 0); LCA::build();
    for (int i = 0; i < Q; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        u = dfn[u]; v = dfn[v];
        if (u > v) swap(u, v);
        q[i] = Query(u, v, i);
    }
    sort(q, q + Q);
    for (int i = 0; i < Q; ++ i) {
        q[i].l = pt[q[i].l];
        q[i].r = pt[q[i].r];
    }
    COT2::solve();
    for (int i = 0; i < Q; ++ i) {
        printf("%d\n", COT2::ans[i]);
    }
    return 0;
}
