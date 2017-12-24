#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

char buf;
inline int xint() { while (buf = getchar(), buf < '0' || buf > '9'); int x = buf - '0'; for (; buf = getchar(), buf >= '0' && buf <= '9'; x = x * 10 + buf - '0'); return x; }

const int MAXN = 100000 + 10;

namespace SegTree {
    const int SIZE = MAXN << 6;
    int ls[SIZE], rs[SIZE], cnt[SIZE], sz = 1;
    void init() {
        sz = 1; ls[0] = rs[0] = cnt[0] = 0;
    }
    void update(int &now, int pre, int l, int r, int x) {
        now = sz ++; cnt[now] = cnt[pre] + 1;
        ls[now] = ls[pre], rs[now] = rs[pre];
        if (l + 1 == r) return;
        int mid = (l + r) >> 1;
        if (x < mid) update(ls[now], ls[pre], l, mid, x);
        else update(rs[now], rs[pre], mid, r, x);
    }
    int query(int now, int pre, int l, int r, int k) {
        if (l + 1 == r) return l;
        int left = cnt[ls[now]] - cnt[ls[pre]], mid = (l + r) >> 1;
        if (k <= left) return query(ls[now], ls[pre], l, mid, k);
        else return query(rs[now], rs[pre], mid, r, k - left);
    }
}

struct Edge {
    int v, nxt;
    Edge() {}
    Edge(int a, int b) : v(a), nxt(b) {}
} E[MAXN << 1];

int val[MAXN], C[MAXN], idx[MAXN], root[MAXN];
int st[MAXN], ed[MAXN], G[MAXN], nodes[MAXN];
int N, M, sz;

void dfs(int u, int f) {
    st[u] = sz; nodes[sz ++] = u;
    for (int now = G[u]; ~now; now = E[now].nxt) {
        int v = E[now].v; if (v == f) continue;
        dfs(v, u);
    }
    ed[u] = sz;
}

int main() {
    N = xint(); sz = 0;
    for (int i = 1; i <= N; ++ i) {
        C[i - 1] = val[i] = xint();
        G[i] = -1;
    }
    sort(C, C + N);
    for (int i = 1; i <= N; ++ i) {
        val[i] = lower_bound(C, C + N, val[i]) - C;
        idx[val[i]] = i;
    }
    for (int i = 1; i < N; ++ i) {
        int u = xint(), v = xint(); //scanf("%d%d", &u, &v);
        E[sz] = Edge(v, G[u]); G[u] = sz ++;
        E[sz] = Edge(u, G[v]); G[v] = sz ++;
    }
    sz = 0; dfs(1, 0);
    SegTree::init(); root[0] = 0;
    for (int i = 0; i < N; ++ i) SegTree::update(root[i + 1], root[i], 0, N, val[nodes[i]]);
    M = xint();
    while (M --) {
        int x = xint(), k = xint();
        printf("%d\n", idx[SegTree::query(root[ed[x]], root[st[x]], 0, N, k)]);
    }
    return 0;
}

