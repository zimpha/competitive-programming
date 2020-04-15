#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

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

using int64 = long long;
const int N = 200000 + 10;
const int mod = 1e9 + 7;

std::vector<std::pair<int, int>> ends[N];
std::vector<std::pair<int, int>> runs[N];
int64 dp[N], t_dp[2][N * 20];
char s[N];
int n, m;

void compute_runs() {
  SuffixArray s1, s2;
  s1.build(s, n);
  std::reverse(s, s + n);
  s2.build(s, n);
  for (int i = 0; i <= n; ++i) ends[i].clear();
  for (int i = 0; i <= n; ++i) runs[i].clear();
  for (int per = 1; per <= n / 2; ++per) {
    for (int pos = per; pos + per <= n; pos += per) {
      int prefix = s1.computeLCP(pos - 1, pos + per - 1);
      int suffix = s2.computeLCP(n - pos, n - pos - per);
      if (prefix + suffix > per) {
        runs[pos - suffix].emplace_back(pos + per + prefix - 2, per);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::sort(runs[i].begin(), runs[i].end());
    for (size_t j = 0; j < runs[i].size(); ++j) {
      if (j == 0 || runs[i][j].first != runs[i][j - 1].first) {
        int p = runs[i][j].second, r = runs[i][j].first;
        for (int x = i + p * 2 - 1; x <= r; ++x) {
          ends[x + 1].emplace_back(p, m + (x - i + 1) % p);
        }
        m += std::min(p, r - i - p * 2 + 2);
      }
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    n = strlen(s), m = 0;
    compute_runs();
    for (int i = 0; i <= m; ++i) {
      t_dp[0][i] = t_dp[1][i] = 0;
    }
    dp[0] = 1;
    int64 sum_0 = 1, sum_1 = 0;
    for (int i = 1; i <= n; ++i) {
      dp[i] = (sum_0 * i - sum_1 + mod) % mod;
      for (auto &e: ends[i]) {
        int p = e.first, x = e.second;
        t_dp[0][x] = (t_dp[0][x] + dp[i - p * 2]) % mod;
        t_dp[1][x] = (t_dp[1][x] + dp[i - p * 2] * (i - p * 2)) % mod;
        dp[i] = (dp[i] - (t_dp[0][x] * i - t_dp[1][x]) + p * t_dp[0][x]) % mod;
      }
      dp[i] %= mod; dp[i] += mod; dp[i] %= mod;
      sum_0 = (sum_0 + dp[i]) % mod;
      sum_1 = (sum_1 + dp[i] * i) % mod;
    }
    printf("%lld\n", dp[n]);
  }
  return 0;
}
