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
  struct Node {
    int64 s_idx, s_cnt;
    int64 s1, s2;
    int add;
    void apply(int v) {
      s1 += s_cnt * v;
      s2 += s_idx * v;
      add += v;
    }
  } T[N << 2];
  void build(int o, int l, int r) {
    if (l + 1 == r) {
      T[o].s_idx = r;
      T[o].s_cnt = 1;
      return;
    }
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m, r);
    T[o].s_idx = T[o << 1].s_idx + T[o << 1 | 1].s_idx;
    T[o].s_cnt = T[o << 1].s_cnt + T[o << 1 | 1].s_cnt;
  }
  void push(int o) {
    if (T[o].add) {
      T[o << 1].apply(T[o].add);
      T[o << 1 | 1].apply(T[o].add);
      T[o].add = 0;
    }
  }
  void add(int o, int l, int r, int L, int R, int v) {
    if (L <= l && R >= r) {
      T[o].apply(v);
      return;
    }
    push(o);
    int m = (l + r) >> 1;
    if (L < m) add(o << 1, l, m, L, R, v);
    if (R > m) add(o << 1 | 1, m, r, L, R, v);
    T[o].s1 = T[o << 1].s1 + T[o << 1 | 1].s1;
    T[o].s2 = T[o << 1].s2 + T[o << 1 | 1].s2;
  }
  int64 get_s1(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) return T[o].s1;
    push(o);
    int64 ret = 0;
    int m = (l + r) >> 1;
    if (L < m) ret += get_s1(o << 1, l, m, L, R);
    if (R > m) ret += get_s1(o << 1 | 1, m, r, L, R);
    return ret;
  }
  int64 get_s2(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) return T[o].s2;
    push(o);
    int64 ret = 0;
    int m = (l + r) >> 1;
    if (L < m) ret += get_s2(o << 1, l, m, L, R);
    if (R > m) ret += get_s2(o << 1 | 1, m, r, L, R);
    return ret;
  }
}

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  SAM::build(n, s);
  fen::build(1, 0, n);
  ST::init(SAM::dfn);
  std::vector<SAM::Node*> go(n + 1);
  auto p = SAM::rt;
  unsigned long long ret = 0, total = 0;
  for (int i = 1; i <= n; ++i) {
    p = p->go[s[i - 1] - 'a'];
    int l = i - p->val;
    fen::add(1, 0, n, i - p->val, i, 1);
    auto u = p;
    while (u != SAM::rt && !u->visited) {
      u->visited = 1;
      u = u->fa;
    }
    int r = i - u->val - 1;
    total += r - l + 1;
    while (u != SAM::rt) {
      int col = ST::query(u->st, u->ed);
      fen::add(1, 0, n, col - u->val, col - go[col]->val, -1);
      std::swap(go[col], u);
    }
    ST::add(p->st, i);
    go[i] = SAM::rt;
    assert(l == 0);
    int64 s2 = fen::get_s2(1, 0, n, l, r + 1);
    int64 s1 = r + 1 < i ? fen::get_s1(1, 0, n, r + 1, i) : 0;
    ret += s2 + (r - l + 1) * s1;
  }
  auto x = total, y = total - 1;
  if (x % 2 == 0) x /= 2;
  else y /= 2;
  printf("%llu\n", x * y - ret + total);
  return 0;
}
