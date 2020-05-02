#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;

std::vector<int> edges[N];
int weight[N];

namespace SAM {
  struct Node {
    Node *go[26], *fa;
    int val;
    bool visited;
    Node(): fa(0), val(0) {
      memset(go, 0, sizeof(go));
      visited = 0;
    }
    void clear() {
      memset(go, 0, sizeof(go));
      fa = 0;
      val = 0;
      visited = 0;
    }
  } pool[N], *rt, *last;

  Node *sz = pool;
  int dfn;

  void init() {
    if (sz != pool) {
      for (Node *p = pool; p < sz; ++ p) p->clear();
    }
    sz = pool;
    last = rt = sz++;
    dfn = 0;
  }

  int node2idx(Node* u) { return u - pool; }
  Node* idx2node(int u) { return pool + u; }

  void add(int c) {
    Node *p = last, *np = sz ++;
    last = np; np->val = p->val + 1;
    for (; p && !p->go[c]; p = p->fa) p->go[c] = np;
    if (p) {
      Node *q = p->go[c];
      if (p->val + 1 == q->val) np->fa = q;
      else {
        Node *nq = sz ++; *nq = *q;
        nq->val = p->val + 1;
        q->fa = nq; np->fa = nq;
        for (; p && p->go[c] == q; p = p->fa) p->go[c] = nq;
      }
    }
    else np->fa = rt;
  }
  void build(int n, char *s) {
    init();
    for (int i = 0; i < n; ++i) {
      add(s[i] - 'a');
    }
  }
}

using int64 = long long;
int size[N], top[N], dfn[N], fa[N], sz;

void dfs_size(int u) {
  size[u] = 1;
  for (auto &v: edges[u]) {
    fa[v] = u;
    dfs_size(v);
    size[u] += size[v];
  }
}

void dfs_top(int u, int p) {
  dfn[u] = sz++; top[u] = p;
  int ws = -1;
  for (auto &v: edges[u]) {
    if (ws == -1 || size[ws] < size[v]) ws = v;
  }
  if (ws != -1) dfs_top(ws, p);
  for (auto &v: edges[u]) if (v != ws) {
    dfs_top(v, v);
  }
}

namespace seg {
  struct Node {
    int64 sum, s1, s2;
    int add;
    void apply(int64 v) {
      s2 += (2 * s1 + sum * v) * v;
      s1 += sum * v;
      add += v;
    }
  } T[N << 2];
  void build(int o, int l, int r) {
    if (l + 1 == r) {
      T[o].sum = weight[l];
      return;
    }
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m, r);
    T[o].sum = T[o << 1].sum + T[o << 1 | 1].sum;
  }
  void push(int o) {
    if (T[o].add) {
      T[o << 1].apply(T[o].add);
      T[o << 1 | 1].apply(T[o].add);
      T[o].add = 0;
    }
  }
  void add(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
      T[o].apply(1);
      return;
    }
    push(o);
    int m = (l + r) >> 1;
    if (L < m) add(o << 1, l, m, L, R);
    if (R > m) add(o << 1 | 1, m, r, L, R);
    T[o].s1 = T[o << 1].s1 + T[o << 1 | 1].s1;
    T[o].s2 = T[o << 1].s2 + T[o << 1 | 1].s2;
  }
}

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  SAM::build(n, s);
  for (SAM::Node* x = SAM::pool; x < SAM::sz; ++x) {
    if (x->fa) edges[SAM::node2idx(x->fa)].push_back(SAM::node2idx(x));
  }
  dfs_size(0);
  dfs_top(0, 0);
  for (SAM::Node* x = SAM::pool; x < SAM::sz; ++x) if (x->fa) {
    weight[dfn[SAM::node2idx(x)]] = x->val - x->fa->val;
  }
  seg::build(1, 0, sz);
  auto p = SAM::rt;
  for (int i = 0; i < n; ++i) {
    p = p->go[s[i] - 'a'];
    int x = SAM::node2idx(p);
    while (x) {
      seg::add(1, 0, sz, dfn[top[x]], dfn[x] + 1);
      x = fa[top[x]];
    }
    printf("%lld\n", seg::T[1].s2);
  }
  return 0;
}
