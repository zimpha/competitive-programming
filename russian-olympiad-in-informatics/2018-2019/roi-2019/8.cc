#include <cstdio>
#include <random>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <cassert>
#include <functional>
#include <algorithm>
#include <iostream>

using int64 = long long;
using pii = std::pair<int, int>;

namespace run {
struct TreeNode;
}

const int M = 2e6, N = 2e5 + 10;

template <class T, class Compare = std::less<T> >
class BitDirectRMQ {
public:
  static constexpr int block_size = 32;

  void build(const std::vector<T> &a) {
    build(a.data(), a.size());
  }

  void build(const T *a, int n) {
    blocks = (n + block_size - 1) / block_size;
    buildSparseTable(a, n);
    buildInnerBlocks(a, n);
  }

  int query(const T *a, int l, int r) const { // [l, r]
    int x = l / block_size, y = r / block_size;
    if (x == y) return query_lookup(l, r);
    int ret = l;
    if (x + 1 <= y - 1) ret = query_st(a, x + 1, y - 1);
    ret = leftMinIndex(a, query_lookup(l, x * block_size + block_size - 1), ret);
    ret = leftMinIndex(a, ret, query_lookup(y * block_size, r));
    return ret;
  }

  int query_st(const T *a, int x, int y) const {
    int z = log[y - x + 1];
    return leftMinIndex(a, table[x + z * blocks], table[y - (1 << z) + 1 + z * blocks]);
  }
  int query_lookup(int x, int y) const {
    return x + __builtin_ctz(lookup[y] >> (x % block_size));
  }

private:
  int minIndex(const T *a, int x, int y) const {
    return compare(a[x], a[y]) || (a[x] == a[y] && x < y) ? x : y;
  }

  int leftMinIndex(const T *a, int x, int y) const {
    return compare(a[y], a[x]) ? y : x;
  }

  void buildSparseTable(const T *a, int n) {
    int height = 0;
    while ((1 << height) < blocks) ++height;
    table.resize(blocks * (height + 1));
    log.assign(blocks + 1, -1);
    for (int i = 1; i <= blocks; ++i) {
      log[i] = log[i >> 1] + 1;
    }
    int *u = table.data();
    for (int i = 0, idx = 0; i < n; i += block_size, ++idx) {
      u[idx] = i;
      for (int j = i + 1; j < n && j < i + block_size; ++j) {
        u[idx] = leftMinIndex(a, u[idx], j);
      }
    }
    for (int t = 1; t * 2 < blocks; t *= 2) {
      memcpy(u + blocks, u, sizeof(int) * blocks);
      u += blocks;
      for (int i = 0; i < blocks - t; ++i) {
        u[i] = leftMinIndex(a, u[i], u[i + t]);
      }
    }
  }

  void buildInnerBlocks(const T *a, int n) {
    lookup.assign(n, 0);
    std::vector<int> stack(block_size);
    for (int i = 0; i < blocks; ++i) {
      int l = i * block_size;
      int r = std::min(n, l + block_size);
      uint32_t state = 0;
      for (int j = l, top = 0; j < r; ++j) {
        while (top && compare(a[j], a[stack[top - 1]])) {
          state ^= uint32_t(1) << (stack[top - 1] - l);
          --top;
        }
        stack[top++] = j;
        state ^= uint32_t(1) << (j - l);
        lookup[j] = state;
      }
    }
  }

  std::vector<uint32_t> lookup;
  std::vector<int> log;
  std::vector<int> table;
  int blocks;
  Compare compare;
};

#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;
  std::vector<int> lcp;
  BitDirectRMQ<int> lcpRMQ;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const {
    return sa.size() - 1;
  }
  int computeLCP(int i, int j) const {
    if (i == j) return size() - i;
    int x = rank[i], y = rank[j];
    if (x > y) std::swap(x, y);
    return lcp[lcpRMQ.query(lcp.data(), x + 1, y)];
  }

private:
  using SLTypes = std::vector<bool>;
  int *buffer, *freq, *cur;
  int len;

  void buildRankTable();
  void buildLCPArrayRMQ();
  template <class T> void computeLCPArray(const T *s);
  template <class T> void countFrequency(const T *s, int n, int m);
  template <class T> void induce(const T *s, int *sa, int m, const SLTypes &t);
  template <class T> void sa_is(const T *s, int *sa, int n, int m);
};

template <class T>
void SuffixArray::build(const T *s, int n) {
  this->len = n;
  int m = *std::max_element(s, s + n) + 1;
  build(s, n, m);
  buildRankTable();
  computeLCPArray(s);
  buildLCPArrayRMQ();
}

template <class T>
void SuffixArray::build(const T *s, int n, int m) {
  sa.resize(n + 1);
  if (n == 0) sa[0] = 0;
  else {
    // memory usage: sa + buffer + types
    // = 4 * (n + max(m * 2, n)) + 2 * n / 8 + O(1) bytes
    std::vector<int> buffer((std::max(m, (n + 1) / 2) + 1) * 2);
    this->buffer = &buffer[0];
    sa_is<T>(s, &sa[0], n + 1, m);
  }
}

void SuffixArray::buildRankTable() {
  int n = size() + 1;
  rank.resize(n);
  for (int i = 0; i < n; ++i) rank[sa[i]] = i;
}

void SuffixArray::buildLCPArrayRMQ() {
  lcpRMQ.build(&lcp[0], size() + 1);
}

template <class T>
void SuffixArray::computeLCPArray(const T *s) {
  const int n = size() + 1;
  lcp.resize(n);
  for (int i = 0, h = lcp[0] = 0; i < n; ++i) if (rank[i]) {
    int j = sa[rank[i] - 1];
    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
    if (lcp[rank[i]] = h) --h;
  }
}

template <class T>
void SuffixArray::countFrequency(const T *s, int n, int m) {
  memset(freq, 0, sizeof(int) * m);
  for (int i = 0; i < n; ++i) ++freq[(int)s[i]];
  for (int i = 1; i < m; ++i) freq[i] += freq[i - 1];
  memcpy(cur, freq, sizeof(int) * m);
}

template <class T>
void SuffixArray::induce(const T *s, int *sa, int m, const SLTypes &t) {
  const int n = t.size();
  memcpy(cur + 1, freq, sizeof(int) * (m - 1));
  for (int i = 0; i < n; ++i) {
    int p = sa[i] - 1;
    if (p >= 0 && t[p]) pushL(p);
  }
  memcpy(cur, freq, sizeof(int) * m);
  for (int i = n - 1; i > 0; --i) {
    int p = sa[i] - 1;
    if (p >= 0 && !t[p]) pushS(p);
  }
}

template <class T>
void SuffixArray::sa_is(const T *s, int *sa, int n, int m) {
  SLTypes t(n); memset(sa, 0, sizeof(int) * n);
  for (int i = n - 2; ~i; --i) {
    t[i] = (s[i] == s[i + 1]) ? t[i + 1] : s[i] > s[i + 1];
  }
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = 1; i < n; ++i) if (t[i - 1] > t[i]) pushS(i);
  induce(s, sa, m, t);
  int n1 = 0, order = 0;
  for (int i = 0, p; i < n; ++i) {
    if ((p = sa[i]) && t[p - 1] > t[p]) sa[n1++] = p;
  }
  int *s1 = sa + n1;
  memset(s1, -1, sizeof(int) * (n - n1));
  s1[(sa[0] - 1) / 2] = order++;
  for (int i = 1; i < n1; ++i) {
    bool diff = true;
    for (int x = sa[i - 1], y = sa[i]; ; ++x, ++y) {
      if (s[x] != s[y] || t[x] != t[y]) break;
      else if (t[x] > t[x + 1] && t[y] > t[y + 1]) {
        diff = (s[x + 1] != s[y + 1]); break;
      }
    }
    s1[(sa[i] - 1) / 2] = (order += diff) - 1;
  }
  for (int i = 0, x = 0; i < n - n1; ++i) {
    if (~s1[i]) s1[x++] = s1[i];
  }
  if (order != n1) {
    sa_is<int>(s1, sa, n1, order);
    for (int i = 0; i < n1; ++i) s1[sa[i]] = i;
  }
  for (int i = 1, j = 0; i < n; ++i) {
    if (t[i - 1] > t[i]) sa[s1[j++]] = -i;
  }
  memset(s1, 0, sizeof(int) * (n - n1));
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = n1 - 1; ~i; --i) pushS(-sa[i]);
  induce(s, sa, m, t);
}

// 2-3-tree
namespace ttt {
struct Node {
  Node* ch[3];
  int64 len;
  int tree_node_idx;
  int cnt;
  char c;
} pool[M], *ptr;

void init() { ptr = pool; }

Node* new_node(char c) {
  assert(ptr < pool + M);
  ptr->tree_node_idx = -1;
  ptr->cnt = 0;
  ptr->c = c;
  ptr->len = 1;
  return ptr++;
}

Node* new_node(const std::vector<Node*> nodes) {
  assert(ptr < pool + M);
  ptr->tree_node_idx = -1;
  ptr->cnt = nodes.size();
  ptr->c = 0;
  ptr->len = 0;
  for (int i = 0; i < ptr->cnt; ++i) {
    ptr->ch[i] = nodes[i];
    ptr->len += nodes[i]->len;
  }
  return ptr++;
}

int64 size(Node* o) { return o ? o->len : 0; }

void split(Node* o, int64 l, int64 r, std::vector<Node*>& nodes) { // [l, r]
  if (l <= 0 && r >= o->len) {
    nodes.push_back(o);
    return;
  }
  if (r <= 0) return;
  if (l >= o->len) return;
  for (int i = 0; i < o->cnt; ++i) {
    split(o->ch[i], l, r, nodes);
    l -= o->ch[i]->len;
    r -= o->ch[i]->len;
  }
}

Node* merge(Node* x, Node* y) {
  if (!x || !y) return x ? x : y;
  return new_node({x, y});
}

Node* merge(std::vector<Node*> &nodes) {
  if (nodes.empty()) return NULL;
  while (nodes.size() > 1) {
    auto nr = nodes.back(); nodes.pop_back();
    auto nl = nodes.back(); nodes.pop_back();
    assert(nr);
    assert(nl);
    if (nodes.size() >= 1) {
      auto na = nodes.back(); nodes.pop_back();
      assert(na);
      nodes.push_back(new_node({na, nl, nr}));
    } else {
      nodes.push_back(merge(nl, nr));
    }
  }
  assert(nodes[0]);
  return nodes[0];
}

Node* split(Node* o, int64 l, int64 r) {
  std::vector<Node*> nodes;
  split(o, l, r, nodes);
  return merge(nodes);
}

std::string get_str(Node* o) {
  if (o->c) return std::string(1, o->c);
  std::string ret = "";
  for (int i = 0; i < o->cnt; ++i) {
    ret += get_str(o->ch[i]);
  }
  return ret;
}
}

char s[N], t[N];

struct str_t {
  SuffixArray sa;
  std::vector<int> fail, link, diff;
  std::vector<std::vector<int>> tree;
  std::vector<int> st, ed;
  std::string s;
  int n, size;
  void build(int n, char *s) {
    this->n = n;
    this->s = std::string(s, s + n + 1);
    fail.resize(n); link.resize(n); diff.resize(n);
    fail[0] = link[0] = -1; diff[0] = 1;
    for (int i = 1, j = -1; i < n; ++i) {
      while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
      fail[i] = s[j + 1] == s[i] ? ++j : j;
      diff[i] = i - fail[i];
      if (fail[i] == -1 || diff[i] != diff[fail[i]]) link[i] = fail[i];
      else link[i] = link[fail[i]];
    }
    tree.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      tree[fail[i] + 1].push_back(i + 1);
    }
    sa.build(s, n);
    st.resize(n + 1);
    ed.resize(n + 1);
    size = 0;
    dfs(0);
  }

  void dfs(int u) {
    st[u] = size++;
    for (auto &v: tree[u]) dfs(v);
    ed[u] = size++;
  }

  int query(int x, int l) {
    for (; x != -1; x = link[x]) if (l >= link[x] + 1) {
      int k = (l - link[x] - 1) / diff[x];
      return std::min(x, link[x] + k * diff[x]) + 1;
    }
    return 0;
  }

  pii max_prefix(int full_len, const pii& pre, const pii& suf) {
    int pre_len = pre.second;
    int suf_len = suf.second;
    if (pre_len != full_len) return pre;
    int lcp = -1;

    auto less = [&](int x) {
      int lcp_pre = sa.computeLCP(sa.sa[x], pre.first);
      lcp = lcp_pre = std::min(lcp_pre, pre_len);
      if (lcp_pre < pre_len) return s[sa.sa[x] + lcp_pre] < s[pre.first + lcp_pre];
      int lcp_suf = sa.computeLCP(sa.sa[x] + lcp_pre, suf.first);
      lcp_suf = std::min(lcp_suf, suf_len);
      lcp += lcp_suf;
      if (lcp_suf == suf_len) return false;
      return s[sa.sa[x] + lcp] < s[suf.first + lcp_suf];
    };

    int left = 0, right = n;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (less(mid)) left = mid;
      else right = mid - 1;
    }
    int best = -1, start = -1;
    for (int i = std::max(0, left - 1); i <= n && i <= left + 1; ++i) {
      less(i);
      if (best == -1 || best < lcp) {
        best = lcp;
        start = sa.sa[i];
      }
    }
    return {start, best};
  }
};

int occ[26];

namespace run {
  struct TreeNode {
    pii pre, suf;
    int64 cnt;
    bool solved;
    TreeNode *l, *r;
  } pool[M], *ptr;

  std::vector<std::pair<int, TreeNode*>> query[N];

  TreeNode* new_node() {
    ptr->l = ptr->r = NULL;
    ptr->cnt = ptr->solved = 0;
    return ptr++;
  }

  TreeNode* build_tree(ttt::Node* o, str_t& s, str_t& rs) {
    auto merge = [&](TreeNode *l, TreeNode* r, int64 l_len, int64 r_len) {
      auto p = new_node();
      p->l = l, p->r = r;
      p->pre = s.max_prefix(l_len, l->pre, r->pre);
      p->suf = rs.max_prefix(r_len, r->suf, l->suf);
      if (l && r && r->pre.second && l->suf.second && s.n != 1) {
        int suf = rs.query(s.n - r->pre.first - 1, r->pre.second);
        int pre = s.query(s.n - l->suf.first - 1, l->suf.second);
        if (pre && suf) {
          query[suf].emplace_back(pre, p);
        }
      }
      return p;
    };

    if (o->tree_node_idx != -1) return pool + o->tree_node_idx;
    TreeNode* p;
    if (o->cnt == 0) {
      p = new_node();
      if (occ[o->c - 'a'] != -1) {
        if (s.n == 1) p->cnt = 1;
        p->pre = {occ[o->c - 'a'], 1};
        p->suf = {s.n - occ[o->c - 'a'] - 1, 1};
      } else {
        p->pre = p->suf = {s.n, 0};
      }
    } else {
      std::vector<TreeNode*> nodes;
      std::vector<int64> lens;
      for (int i = 0; i < o->cnt; ++i) {
        nodes.push_back(build_tree(o->ch[i], s, rs));
        lens.push_back(o->ch[i]->len);
      }
      if (nodes.size() == 2) {
        p = merge(nodes[0], nodes[1], lens[0], lens[1]);
      } else {
        auto q = merge(nodes[0], nodes[1], lens[0], lens[1]);
        p = merge(q, nodes[2], lens[0] + lens[1], lens[2]);
      }
    }
    o->tree_node_idx = p - pool;
    return p;
  }

  int64 solve(TreeNode* o) {
    if (!o) return 0;
    if (o->solved) return o->cnt;
    o->solved = 1;
    o->cnt += solve(o->l) + solve(o->r);
    return o->cnt;
  }

  int64 run(ttt::Node* o, str_t& s, str_t& rs) {
    ptr = pool;
    auto root = build_tree(o, s, rs);
    int n = s.n;
    std::vector<int> bit(s.size, 0);

    auto add = [&](int x, int v) {
      for (; x < s.size; x += ~x & x + 1) bit[x] += v;
    };

    auto get = [&](int x, int r = 0) {
      for (; x >= 0; x -= ~x & x + 1) r += bit[x];
      return r;
    };

    std::function<void(int)> dfs = [&](int x) {
      if (x != 0 && x != n) {
        add(s.st[n - x], +1); add(s.ed[n - x], -1);
      }
      for (auto &e: query[x]) {
        e.second->cnt = get(s.st[e.first]);
      }
      for (auto &y: rs.tree[x]) dfs(y);
      if (x != 0 && x != n) {
        add(s.st[n - x], -1); add(s.ed[n - x], +1);
      }
    };

    dfs(0);

    return solve(root);
  }
}

int main() {
  int n, m;
  scanf("%d%d%s", &n, &m, s);
  memset(occ, -1, sizeof(occ));
  for (int i = 0; i < n; ++i) {
    occ[s[i] - 'a'] = i;
  }
  ttt::init();
  ttt::Node *root = NULL;
  std::vector<ttt::Node*> letters(26);
  for (int i = 0; i < 26; ++i) {
    letters[i] = ttt::new_node('a' + i);
  }
  for (int i = 0; i < m; ++i) {
    int type;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%s", t);
      int len = strlen(t);
      std::vector<ttt::Node*> nodes(len);
      for (int j = 0; j < len; ++j) {
        nodes[j] = letters[t[j] - 'a'];
      }
      while (nodes.size() != 1) {
        int nn = 0;
        for (size_t i = 0; i < nodes.size(); i += 2) {
          if (i + 1 == nodes.size()) nodes[nn++] = nodes[i];
          else nodes[nn++] = ttt::new_node({nodes[i], nodes[i + 1]});
        }
        nodes.erase(nodes.begin() + nn, nodes.end());
      }
      root = ttt::merge(root, nodes[0]);
    } else {
      int64 p, l;
      scanf("%lld%lld", &p, &l);
      auto x = ttt::split(root, p - 1, std::min(p - 1 + l, ttt::size(root)));
      int64 k = l / x->len;
      int64 r = l % x->len;
      auto y = ttt::split(x, 0, r);
      std::vector<ttt::Node*> nodes;
      for (; k; k >>= 1) {
        if (k & 1) nodes.push_back(x);
        x = ttt::new_node({x, x});
      }
      root = ttt::merge(root, ttt::merge(ttt::merge(nodes), y));
    }
  }
  str_t str, rev_str;
  str.build(n, s);
  std::reverse(s, s + n);
  rev_str.build(n, s);
  printf("%lld\n", run::run(root, str, rev_str));
  return 0;
}
