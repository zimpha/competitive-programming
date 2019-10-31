#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5e5 + 10;

struct Tree {
  std::vector<int> edges[N];
  std::vector<std::pair<int, int>> query[N];
  std::vector<std::pair<int, int>> ask[N];
  int fail[N];
  int st[N], ed[N], size;
  void init(int n) {
    for (int i = 0; i <= n + 1; ++i) {
      edges[i].clear();
      query[i].clear();
      ask[i].clear();
    }
    size = 0;
  }
} prefix, suffix;

struct Bit {
  int64 sum[N];
  int cnt[N];
  int n;

  void init(int n) {
    this->n = n;
    for (int i = 0; i <= n; ++i) {
      sum[i] = cnt[i] = 0;
    }
  }
  void add(int x, int v) {
    for (; x >= 0; x -= ~x & x + 1) {
      sum[x] += v;
      cnt[x] += 1;
    }
  }
  void del(int x, int v) {
    for (; x >= 0; x -= ~x & x + 1) {
      sum[x] -= v;
      cnt[x] -= 1;
    }
  }
  int64 get_sum(int x, int64 r = 0) {
    for (; x <= n; x += ~x & x + 1) r += sum[x];
    return r;
  }
  int get_cnt(int x, int r = 0) {
    for (; x <= n; x += ~x & x + 1) r += cnt[x];
    return r;
  }
} bit;

char s[N];
int64 ret[N];
int stack[N];
int n, m, top;

void prepare_prefix(int u) {
  stack[top++] = u;
  for (auto &e: prefix.query[u]) {
    int r = n - e.first + 1;
    int bound = std::min(u - r, (u + r) / 2 - r);
    int p = 0, q = top - 1;
    while (p < q) {
      int m = (p + q + 1) >> 1;
      if (stack[m] <= bound) p = m;
      else q = m - 1;
    }
    if (p) prefix.ask[stack[p]].push_back(e);
    /*printf("bound=%d; u=%d r=%d in %d\n", bound, u, r, stack[p]);
    printf("stack: ");
    for (int i = 0; i < top; ++i) printf("%d ", stack[i]);
    puts("");*/
  }
  prefix.st[u] = prefix.size++;
  for (auto &v: prefix.edges[u]) {
    prepare_prefix(v);
  }
  prefix.ed[u] = prefix.size;
  --top;
}

void prepare_suffix(int u) {
  stack[top++] = u;
  suffix.st[u] = suffix.size++;
  for (auto &e: suffix.query[u]) {
    int l = e.first;
    int bound = std::max(u + l, n + l + 1 - (l + n - u + 1) / 2);
    int p = 0, q = top - 1;
    while (p < q) {
      int m = (p + q + 1) >> 1;
      if (stack[m] >= bound) p = m;
      else q = m - 1;
    }
    if (p) suffix.ask[stack[p]].push_back(e);
  }
  for (auto &v: suffix.edges[u]) {
    prepare_suffix(v);
  }
  suffix.ed[u] = suffix.size;
  --top;
}

void solve_prefix(int u) {
  if (u && u != n) bit.add(suffix.st[u + 1], u);
  for (auto &e: prefix.ask[u]) {
    int l = suffix.st[e.first];
    int r = suffix.ed[e.first];
    auto sum = bit.get_sum(l) - bit.get_sum(r);
    auto cnt = bit.get_cnt(l) - bit.get_cnt(r);
    ret[e.second] += sum + (int64)cnt * (n - e.first + 1);
  }
  for (auto &v: prefix.edges[u]) {
    solve_prefix(v);
  }
  if (u && u != n) bit.del(suffix.st[u + 1], u);
}

void solve_suffix(int u) {
  if (u && u != n + 1) bit.add(prefix.st[u - 1], n - u + 1);
  for (auto &e: suffix.ask[u]) {
    int l = prefix.st[e.first];
    int r = prefix.ed[e.first];
    auto sum = bit.get_sum(l) - bit.get_sum(r);
    auto cnt = bit.get_cnt(l) - bit.get_cnt(r);
    ret[e.second] += sum + (int64)cnt * e.first;
  }
  for (auto &v: suffix.edges[u]) {
    solve_suffix(v);
  }
  if (u && u != n + 1) bit.del(prefix.st[u - 1], n - u + 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%s", &n, &m, s + 1);
    prefix.init(n); suffix.init(n);
    prefix.fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i) {
      while (j >= 1 && s[j + 1] != s[i]) j = prefix.fail[j];
      prefix.fail[i] = (s[j + 1] == s[i] ? ++j : j);
    }
    suffix.fail[n] = n + 1;
    for (int i = n - 1, j = n + 1; i >= 1; --i) {
      while (j <= n && s[j - 1] != s[i]) j = suffix.fail[j];
      suffix.fail[i] = (s[j - 1] == s[i] ? --j : j);
    }

    for (int i = 1; i <= n; ++i) {
      prefix.edges[prefix.fail[i]].push_back(i);
      suffix.edges[suffix.fail[i]].push_back(i);
    }

    std::vector<int> border;
    for (int i = n; i > 0; i = prefix.fail[i]) {
      border.push_back(i);
    }
    border.push_back(0);
    std::reverse(border.begin(), border.end());
    std::vector<int64> sum(border.size());
    for (size_t i = 1; i < border.size(); ++i) {
      sum[i] = sum[i - 1] + border[i];
    }
    for (int i = 0; i < m; ++i) {
      int l, r;
      scanf("%d%d", &l, &r);
      if (l == 1 && r == n) ret[i] = 0;
      else if (l - 1 >= n - r) { // left part
        prefix.query[l - 1].emplace_back(r + 1, i);
      } else { // right part
        suffix.query[r + 1].emplace_back(l - 1, i);
      }
      int len = std::min(l - 1, n - r);
      int p = std::upper_bound(border.begin(), border.end(), len) - border.begin() - 1;
      ret[i] = sum[p];
    }

    top = 0;
    assert(prefix.size == 0);
    prepare_prefix(0);
    top = 0;
    assert(suffix.size == 0);
    prepare_suffix(n + 1);

    top = 0;
    bit.init(n);
    solve_prefix(0);
    top = 0;
    bit.init(n);
    solve_suffix(n + 1);

    for (int i = 0; i < m; ++i) {
      printf("%lld\n", ret[i]);
    }
  }
  return 0;
}
