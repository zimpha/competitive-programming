#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

// Two Efficient Algorithms for Linear Suffix Array Construction
#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;
  std::vector<int> lcp;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const {
    return sa.size() - 1;
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

template <class T>
void SuffixArray::computeLCPArray(const T *s) {
  const int n = size() + 1;
  lcp.resize(n);
  for (int i = 0, h = lcp[0] = 0; i < n; ++i) {
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

namespace segment_tree {
struct Node {
  int l, r;
  int lm, rm, delta;
} pool[N * 40];
int size = 0;

int new_node() {
  pool[size].l = pool[size].r = -1;
  pool[size].lm = pool[size].rm = -1;
  pool[size].delta = -1;
  return size++;
}

int update(int o) {
  int l = pool[o].l, r = pool[o].r;
  if (l == -1 && r == -1) return o;
  if (l != -1) {
    pool[o].lm = pool[l].lm;
    pool[o].rm = pool[l].rm;
    pool[o].delta = pool[l].delta;
  }
  if (r != -1) {
    pool[o].rm = pool[r].rm;
    if (pool[o].lm == -1) pool[o].lm = pool[r].lm;
    pool[o].delta = std::max(pool[o].delta, pool[r].delta);
  }
  if (l != -1 && r != -1) {
    pool[o].delta = std::max(pool[r].lm - pool[l].rm, pool[o].delta);
  }
  return o;
}

int insert(int l, int r, int x) {
  if (x >= r) return -1;
  int o = new_node();
  if (l + 1 == r) {
    pool[o].lm = pool[o].rm = x;
    pool[o].delta = 0;
    return o;
  }
  int m = (l + r) >> 1;
  if (x < m) pool[o].l = insert(l, m, x);
  else pool[o].r = insert(m, r, x);
  return update(o);
}

int merge(int x, int y) {
  if (x == -1 || y == -1) return x == -1 ? y : x;
  int o = new_node();
  pool[o].l = merge(pool[x].l, pool[y].l);
  pool[o].r = merge(pool[x].r, pool[y].r);
  return update(o);
}

}

struct Interval {
  int dsu;
  int root;
  int height;
};


char s[N];
Interval iv[N];
int prefix[N], suffix[N], n;
std::vector<int> event[N];
SuffixArray sa;
int mx[N << 2];

void build(int o, int l, int r) {
  if (l + 1 == r) {
    mx[o] = prefix[l];
    return;
  }
  int m = (l + r) >> 1;
  if (l < m) build(o << 1, l, m);
  if (r > m) build(o << 1 | 1, m, r);
  mx[o] = std::max(mx[o << 1], mx[o << 1 | 1]);
}

int search(int o, int l, int r, int L, int R, int p) {
  if (mx[o] < p) return -1;
  if (l + 1 == r) return l;
  int m = (l + r) >> 1, ret = -1;
  if (L < m) ret = search(o << 1, l, m, L, R, p);
  if (ret != -1) return ret;
  if (R > m) ret = search(o << 1 | 1, m, r, L, R, p);
  return ret;
}

int dsu(int x) {
  if (iv[x].dsu != x) iv[x].dsu = dsu(iv[x].dsu);
  return iv[x].dsu;
}

void kmp(char *s, int n, int* fail) {
  memset(fail, -1, sizeof(int) * n);
  for (int i = 1, j = -1; i < n; ++i) {
    while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = (s[j + 1] == s[i]) ? ++j : j;
  }
  for (int i = 0; i < n; ++i) ++fail[i];
}

std::vector<std::pair<int, int>> query[N];
// suffix[p] [l, r]
void solve(int p, int l, const Interval& iv) {
  int r = iv.height;
  if (l > r) return;
  auto &node = segment_tree::pool[iv.root];
  l = std::max(l, node.delta);
  l = std::max(l, node.lm);
  l = std::max(l, n - node.rm - suffix[node.rm]);
  if (l > r) return;
  l += node.lm - 1;
  r += node.lm - 1;
  query[node.lm].emplace_back(l, r);
}

int main() {
  scanf("%s", s);
  n = strlen(s);
  sa.build(s, n);
  kmp(s, n, prefix);
  std::reverse(s, s + n);
  kmp(s, n, suffix);
  std::reverse(s, s + n);
  std::reverse(suffix, suffix + n);
  for (int i = 1; i <= n; ++i) {
    event[sa.lcp[i]].push_back(sa.sa[i]);
  }
  for (int i = 0; i <= n; ++i) {
    iv[i].root = segment_tree::insert(0, n, i);
    iv[i].dsu = i;
    iv[i].height = n - i;
  }
  for (int i = n - 1; i >= 0; --i) {
    const auto &ev = event[i];
    for (auto &x: ev) {
      int u = dsu(x);
      int v = dsu(sa.sa[sa.rank[x] - 1]);
      assert(u != v);
      iv[u].dsu = v;
      solve(v, i + 1, iv[v]);
      solve(u, i + 1, iv[u]);
      iv[v].root = segment_tree::merge(iv[v].root, iv[u].root);
      iv[v].height = i;
    }
  }
  build(1, 0, n);
  for (int i = 0; i <= n; ++i) event[i].clear();
  int64 ret = 0;
  int best = n, start = 0;
  for (int i = 0; i < n; ++i) {
    suffix[i] = 0;
    for (auto &e: query[i]) {
      if (e.first) event[e.first - 1].push_back(-i - 1);
      event[e.second].push_back(i + 1);
      int p = search(1, 0, n, e.first, e.second + 1, i);
      if (p != -1 && (p - i + 1 < best || (p - i + 1 == best && sa.rank[i] < sa.rank[start]))) {
        start = i;
        best = p - i + 1;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int x = prefix[i]; x >= 0; x -= ~x & x + 1) suffix[x] += 1;
    for (auto &p: event[i]) {
      int s = p > 0 ? 1 : -1;
      p = p * s;
      for (int x = p - 1; x <= n; x += ~x & x + 1) ret += suffix[x] * s;
    }
  }
  printf("%lld\n", ret);
  for (int i = 0; i < best; ++i) putchar(s[start + i]);
  puts("");
  return 0;
}
