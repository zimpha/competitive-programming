#include <cstring>
#include <vector>
#include <memory>
#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

using int64 = long long;

template <class T, class Compare = std::less<T>>
class SchieberVishkinRMQ {
public:
  SchieberVishkinRMQ() = default;

  void build(const std::vector<T> &a) {
    build(a.data(), a.size());
  }

  void build(const T *a, int n) {
    std::vector<int> left(n, -1), right(n, -1);
    std::vector<int> stk(n);
    // build Cartesian Tree
    for (int i = 0, top = 0; i < n; ++i) {
      int last = -1;
      while (top && compare(a[i], a[stk[top - 1]])) {
        last = stk[--top];
      }
      if (top) right[stk[top - 1]] = i;
      left[i] = last;
      stk[top++] = i;
    }

    // find preorder
    int root = stk[0];
    std::vector<int> parents(n, -1), order;
    indices.resize(n), inlabel.resize(n);
    for (int top = 1; top; ) {
      int u = stk[--top];
      order.push_back(u);
      indices[u] = inlabel[u] = order.size();
      if (left[u] != -1) {
        stk[top++] = left[u];
        parents[left[u]] = u;
      }
      if (right[u] != -1) {
        stk[top++] = right[u];
        parents[right[u]] = u;
      }
    }

    // calc helper structures for Schieber-Vishkin LCA
    ascendant.resize(n), head.resize(n);
    for (int i = n - 1; i > 0; --i) {
      int v = order[i], p = parents[v];
      if (lowbit(inlabel[p]) < lowbit(inlabel[v])) {
        inlabel[p] = inlabel[v];
      }
    }
    ascendant[root] = 0;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
    }
    head[0] = root;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      if (inlabel[v] != inlabel[p]) head[indices[v] - 1] = p;
      else head[indices[v] - 1] = head[indices[p] - 1];
    }
  }

  // return the index of the minimum value in [u, v] in O(1)
  int query(int u, int v) const {
    uint Iv = inlabel[v], Iu = inlabel[u];
    uint hIv = lowbit(Iv), hIu = lowbit(Iu);
    uint mask = highbit((Iv ^ Iu) | hIv | hIu);
    uint j = lowbit(ascendant[v] & ascendant[u] & ~mask);
    int x, y;
    if (j == hIv) x = v;
    else {
      mask = highbit(ascendant[v] & (j - 1));
      x = head[(indices[v] & ~mask | (mask + 1)) - 1];
    }
    if (j == hIu) y = u;
    else {
      mask = highbit(ascendant[u] & (j - 1));
      y = head[(indices[u] & ~mask | (mask + 1)) - 1];
    }
    return indices[x] < indices[y] ? x : y;
  }

private:
  using uint = unsigned int;
  static uint lowbit(uint x) {
    return x & (~x + 1); // x & (-x) or x & (x ^ (x - 1))
  }
  static uint highbit(uint v) {
    v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
		return v >> 1;
  }

  Compare compare;
  std::vector<uint> indices;
  std::vector<uint> inlabel;
  std::vector<uint> ascendant;
  std::vector<int> head;
};

// Two Efficient Algorithms for Linear Suffix Array Construction
#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;
  std::vector<int> lcp;
  SchieberVishkinRMQ<int> lcpRMQ;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const {
    return sa.size() - 1;
  }
  int computeLCP(int i, int j) const {
    if (i == j) return size() - i;
    int x = rank[i], y = rank[j];
    if (x > y) std::swap(x, y);
    return lcp[lcpRMQ.query(x + 1, y)];
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

const int N = 4e5 + 10;

int dsu[N], size[N], ret[N];
char s[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  int n, q;
  scanf("%d%d%s", &n, &q, s);
  SuffixArray sa;
  sa.build(s, n);
  for (; q--; ) {
    int m, mod;
    scanf("%d%d", &m, &mod);
    std::vector<std::pair<int, int>> qs(m);
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &qs[i].first, &qs[i].second);
      --qs[i].first;
      qs[i].second -= qs[i].first;
    }
    std::sort(qs.begin(), qs.end(), [&](const std::pair<int, int> &a, const std::pair<int, int> &b) {
      int lcp = sa.computeLCP(a.first, b.first);
      if (lcp >= a.second || lcp >= b.second) {
        return a.second < b.second;
      }
      return s[a.first + lcp] < s[b.first + lcp];
    });
    std::vector<std::pair<int, int>> prefix(m - 1);
    for (int i = 1; i < m; ++i) {
      int lcp = sa.computeLCP(qs[i - 1].first, qs[i].first);
      prefix[i - 1].first = std::min(lcp, std::min(qs[i - 1].second, qs[i].second));
      prefix[i - 1].second = i - 1;
    }
    std::sort(prefix.begin(), prefix.end());
    std::reverse(prefix.begin(), prefix.end());
    for (int i = 0; i < m; ++i) {
      dsu[i] = i;
      size[i] = 1;
      ret[i] = 2 % mod;
    }
    for (const auto &p: prefix) {
      int u = get(p.second);
      int v = get(p.second + 1);
      if (u == v) continue;
      int t_ret = 0;
      if (size[u] == 1 && p.first == qs[u].second) {
        t_ret = (1 + ret[v]) % mod;
      } else if (size[v] == 1 && p.first == qs[v].second) {
        t_ret = (1 + ret[u]) % mod;
      } else {
        t_ret = (int64)ret[u] * ret[v] % mod;
      }
      if (size[u] < size[v]) std::swap(u, v);
      size[u] += size[v];
      dsu[v] = u;
      ret[u] = t_ret;
    }
    printf("%d\n", ret[get(0)]);
  }
  return 0;
}
