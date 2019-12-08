#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10;

namespace SAM {
  struct Node {
    Node *go[26], *fa;
    std::vector<Node*> children;
    int val, st, ed;
    bool visited;
    Node(): fa(0), val(0) {
      memset(go, 0, sizeof(go));
      children.clear();
      visited = 0;
    }
    void clear() {
      memset(go, 0, sizeof(go));
      children.clear();
      fa = 0;
      val = 0;
      visited = 0;
    }
  } pool[N << 1], *rt, *last;

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
  void dfs(Node* o) {
    o->st = dfn++;
    for (auto &p: o->children) dfs(p);
    o->ed = dfn;
  }
  void build(int n, char *s) {
    init();
    for (int i = 0; i < n; ++i) {
      add(s[i] - 'a');
    }
    for (Node* p = pool; p < sz; ++p) {
      if (p->fa) p->fa->children.push_back(p);
    }
    dfs(rt);
  }
}

namespace ST {
  int mx[N * 4], n;
  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n * 2; ++i) {
      mx[i] = 0;
    }
  }
  void add(int x, int v) {
    for (mx[x += n] = v; x > 1; x >>= 1) {
      mx[x >> 1] = std::max(mx[x], mx[x ^ 1]);
    }
  }
  int query(int l, int r) { // [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = std::max(res, mx[l++]);
      if (r & 1) res = std::max(res, mx[--r]);
    }
    return res;
  }
}

using int64 = long long;

namespace fen {
  int64 a[N], b[N];
  int n;
  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n; ++i) {
      a[i] = b[i] = 0;
    }
  }
  void add(int x, int v) { // [0, x] +v
    int64 va = (int64)x * v, vb = -v;
    for (; x <= n; x += ~x & x + 1) {
      a[x] += va; b[x] += vb;
    }
  }
  void add(int l, int r, int v) { //[l, r)
    add(r, v);
    add(l, -v);
  }
  int64 get(int x) {
    int64 ra = 0, rb = 0, r = x;
    for (; x >= 0; x -= ~x & x + 1) {
      ra += a[x]; rb += b[x];
    }
    return ra + rb * r;
  }
  int64 get(int l, int r) { // [l, r)
    return get(r) - get(l);
  }
}

char s[N];

int main() {
  int n, m;
  scanf("%d%d%s", &n, &m, s);
  std::vector<std::vector<std::pair<int, int>>> ql(n);
  std::vector<int64> ret(m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    ql[y].emplace_back(x, i);
  }
  SAM::build(n, s);
  fen::init(n);
  ST::init(SAM::dfn);
  std::vector<SAM::Node*> go(n + 1);
  auto p = SAM::rt;
  for (int i = 1; i <= n; ++i) {
    p = p->go[s[i - 1] - 'a'];
    fen::add(i - p->val, i, 1);
    auto u = p;
    while (u != SAM::rt && !u->visited) {
      u->visited = 1;
      u = u->fa;
    }
    while (u != SAM::rt) {
      int col = ST::query(u->st, u->ed);
      fen::add(col - u->val, col - go[col]->val, -1);
      std::swap(go[col], u);
    }
    ST::add(p->st, i);
    go[i] = SAM::rt;
    for (auto e: ql[i - 1]) {
      ret[e.second] = fen::get(e.first, i);
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}
