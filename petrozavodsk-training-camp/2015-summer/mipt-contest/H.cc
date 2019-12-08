#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10, inf = 1e9;

struct SuffixTree {
  struct node {
    // Following suffix link will lead to the vertex corresponding to the same substring, but without first character.
    node *go[26], *link, *fa;
    int cnt, st, len;
    node() {}
    void clr() {
      st = cnt = 0;
      len = inf;
      link = fa = NULL;
      memset(go, 0, sizeof(go));
    }
  } pool[N * 2], *rt, *ptr;
  int s[N], n;

  struct position {
    node *u; // active node
    int cur; // the position in the string
    int pos; // number of chars needed to insert current suffix
    int rem; // number suffixes not finished yet
    position() {}
    void go(int o) {u = u->go[o]; pos -= u->len; cur += u->len; }
    bool can(int o) {return u->go[o] && pos >= u->go[o]->len;}
  } last;

  node *new_node(node* fa, int st, int len) {
    ptr->clr();
    ptr->fa = fa;
    ptr->st = st;
    ptr->len = len;
    if (fa) fa->cnt++;
    return ptr++;
  }
  void init() {
    n = 0, ptr = pool;
    last.u = rt = new_node(NULL, 0, inf);
    last.cur = last.pos = last.rem = 0;
  }
  void walk() {
    while (last.can(s[last.cur])) {
      last.go(s[last.cur]);
    }
  }
  void follow_link() {
    if (last.u == rt) { if (last.pos) --last.pos, ++last.cur; }
    else last.u = last.u->link ? last.u->link : rt;
    --last.rem;
  }
  void add(int c) {
    s[n++] = c; ++last.rem;
    for (node* p = rt; last.rem; ) {
      if (!last.pos) last.cur = n - 1;
      walk();
      int o = s[last.cur];
      node* &v = last.u->go[o];
      int t = s[v == NULL ? 0 : v->st + last.pos];
      if (v == NULL) {
        v = new_node(last.u, n - 1, inf);
        p->link = last.u;
        p = rt;
      } else if (t == c) {
        p->link = last.u;
        ++last.pos;
        return;
      } else {// split edge
        node *u = new_node(last.u, v->st, last.pos);
        last.u->cnt--;
        u->go[c] = new_node(u, n - 1, inf);
        u->go[t] = v; ++u->cnt;
        v->fa = u;
        v->st += last.pos;
        v->len -= last.pos;
        p->link = v = u;
        p = u;
      }
      follow_link();
    }
  }
  void build(std::vector<std::vector<int>> &q) {
    for (node *p = pool; p < ptr; ++p) {
      int len = std::min(p->len, n - p->st);
      if (p != rt) {
        q[len + p->st - 1].push_back(p->st);
      }
    }
  }
} suffix_tree;

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
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    suffix_tree.init();
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
      suffix_tree.add(s[i] - 'a');
    }
    std::vector<std::vector<int>> ql(n);
    suffix_tree.build(ql);
    SAM::build(n, s);
    fen::init(n);
    ST::init(SAM::dfn);
    std::vector<SAM::Node*> go(n + 1);
    auto p = SAM::rt;
    int64 ret = 0;
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
        ret += fen::get(e, i);
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}
