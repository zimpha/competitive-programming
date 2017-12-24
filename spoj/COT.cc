#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 10;
const int SIZE = MAXN * 35;

vector<int> G[MAXN], C;
int ls[SIZE], rs[SIZE], root[SIZE], sum[SIZE];
int val[MAXN], dep[MAXN], father[MAXN][20];
int N, M, tot, sz;

void build(int &rt, int l, int r) {
    rt = sz ++; sum[rt] = 0;
    if (l + 1 == r) return;
    int mid = (l + r) >> 1;
    build(ls[rt], l, mid);
    build(rs[rt], mid, r);
}

void modify(int &rt, int last, int l, int r, int p) {
    rt = sz ++; sum[rt] = sum[last] + 1;
    ls[rt] = ls[last], rs[rt] = rs[last];
    if (l + 1 == r) return;
    int mid = (l + r) >> 1;
    if (p < mid) modify(ls[rt], ls[last], l, mid, p);
    else modify(rs[rt], rs[last], mid, r, p);
}

int query(int rt1, int rt2, int rt3, int rt4, int l, int r, int k) {
    if (l + 1 == r) return l;
    int mid = (l + r) >> 1;
    int cnt = sum[ls[rt1]] + sum[ls[rt2]] - sum[ls[rt3]] - sum[ls[rt4]];
    if (k <= cnt) return query(ls[rt1], ls[rt2], ls[rt3], ls[rt4], l, mid, k);
    else return query(rs[rt1], rs[rt2], rs[rt3], rs[rt4], mid, r, k - cnt);
}

void dfs(int u, int f) {
    dep[u] = dep[f] + 1; father[u][0] = f;
    modify(root[u], root[f], 0, tot, val[u]);
    for (int i = 0, v; i < (int)G[u].size(); ++ i) {
        if ((v = G[u][i]) == f) continue;
        dfs(v, u);
    }
}

namespace LCA {
void build() {
    for (int i = 1; (1 << i) <= N; ++ i) {
        for (int j = 1; j <= N; ++ j) {
            if (father[j][i - 1] == 0) continue;
            father[j][i] = father[father[j][i - 1]][i - 1];
        }
    }
}

int anc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int delta = dep[u] - dep[v];
    for (int i = 0; i <= 16; ++ i) {
        if (delta & (1 << i)) u = father[u][i];
    }
    for (int i = 16; i >= 0; -- i) {
        if (father[u][i] == father[v][i]) continue;
        u = father[u][i];
        v = father[v][i];
    }
    if (u != v) u = father[u][0];
    return u;
}
}

int main() {
    scanf("%d%d", &N, &M); C.clear();
    for (int i = 1; i <= N; ++ i) {
        scanf("%d", &val[i]);
        G[i].clear(); C.push_back(val[i]);
    }
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    for (int i = 1; i <= N; ++ i) {
        val[i] = lower_bound(C.begin(), C.end(), val[i]) - C.begin();
    }
    sz = 0; tot = C.size(); build(root[0], 0, tot);
    for (int i = 1; i < N; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, 0);
    LCA::build();
    int lastans = 0;
    while (M --) {
        int u, v, k; scanf("%d%d%d", &u, &v, &k);
        //u ^= lastans;
        int rt = LCA::anc(u, v);
        int rr = father[rt][0];
        lastans = C[query(root[u], root[v], root[rt], root[rr], 0, tot, k)];
        printf("%d\n", lastans);
        //if (M) puts("");
    }
    return 0;
}
