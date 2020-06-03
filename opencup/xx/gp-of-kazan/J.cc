#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;
const int64 inf = 1ll << 60;

std::vector<std::pair<int, int>> edges[N];

void max(std::vector<int64> &x, const std::vector<int64>& y) {
  while (x.size() < y.size()) x.push_back(-inf);
  for (size_t i = 0; i < y.size(); ++i) {
    x[i] = std::max(x[i], y[i]);
  }
}

std::vector<int64> sum(const std::vector<int64> &x, const std::vector<int64> &y) {
  std::vector<int64> delta;
  delta.reserve(x.size() + y.size());
  size_t i = 1, j = 1;
  while (i < x.size() && j < y.size()) {
    if (x[i] - x[i - 1] > y[j] - y[j - 1]) delta.push_back(x[i] - x[i - 1]), ++i;
    else delta.push_back(y[j] - y[j - 1]), ++j;
  }
  while (i < x.size()) delta.push_back(x[i] - x[i - 1]), ++i;
  while (j < y.size()) delta.push_back(y[j] - y[j - 1]), ++j;
  std::vector<int64> z;
  z.reserve(x.size() + y.size());
  z.push_back(x[0] + y[0]);
  for (auto &d: delta) z.push_back(z.back() + d);
  return z;
}

struct Value {
  std::vector<int64> inc, exc;
  int64 w;
};

std::vector<int64> T[N << 2][2][2], S[N << 2][2];
int64 upw[N << 2];
std::vector<Value> hld[N];
int size[N];

void solve_heavy(const std::vector<Value> &val, int o, int l, int r) {
  for (int x = 0; x < 2; ++x) for (int y = 0; y < 2; ++y) {
    T[o][x][y].clear();
  }
  if (l + 1 == r) {
    T[o][0][0] = val[l].exc;
    T[o][0][1] = val[l].exc;
    T[o][1][0] = val[l].exc;
    T[o][1][1] = val[l].inc;
    upw[o] = val[l].w;
    return;
  }
  int m = (l + r) >> 1;
  solve_heavy(val, o << 1, l, m);
  solve_heavy(val, o << 1 | 1, m, r);
  for (int x = 0; x < 2; ++x) for (int y = 0; y < 2; ++y) {
    max(T[o][x][y], sum(T[o << 1][x][1], T[o << 1 | 1][1][y]));
    int xx = (m - l > 1) ? x : 1;
    int yy = (r - m > 1) ? y : 1;
    auto buf = sum(T[o << 1][xx][0], T[o << 1 | 1][0][yy]);
    for (auto &e: buf) e += upw[o << 1];
    buf.insert(buf.begin(), 0);
    max(T[o][xx][yy], buf);
  }
  upw[o] = upw[o << 1 | 1];
}

void solve_light(const std::vector<Value> &val, int o, int l, int r) {
  S[o][0].clear(); S[o][1].clear();
  if (l + 1 == r) {
    S[o][0] = val[l].exc;
    S[o][1] = val[l].inc;
    return;
  }
  int m = (l + r) >> 1;
  solve_light(val, o << 1, l, m);
  solve_light(val, o << 1 | 1, m, r);
  for (int x = 0; x < 2; ++x) for (int y = 0; y < 2; ++y) {
    if (x == 1 && y == 1) continue;
    max(S[o][x + y], sum(S[o << 1][x], S[o << 1 | 1][y]));
  }
}

void solve_heavy(const std::vector<Value> &val, std::vector<int64> &inc, std::vector<int64> &exc) {
  solve_heavy(val, 1, 0, val.size());
  exc = T[1][0][0]; max(exc, T[1][1][0]);
  inc = T[1][0][1]; max(inc, T[1][1][1]);
  return;
}

void solve_light(const std::vector<Value> &val, std::vector<int64> &inc, std::vector<int64>& exc) {
  solve_light(val, 1, 0, val.size());
  exc = S[1][0]; inc = S[1][1];
  return;
}

void dfs(int u, int p = -1) {
  size[u] = 1;
  int heavy = -1, up_w = -1;
  for (auto &e: edges[u]) {
    int v = e.first;
    if (v == p) continue;
    dfs(v, u);
    size[u] += size[v];
    if (heavy == -1 || size[v] > size[heavy]) {
      heavy = v, up_w = e.second;
    }
  }
  std::vector<Value> light;
  for (auto &e: edges[u]) {
    int v = e.first;
    if (v == heavy || v == p) continue;
    std::vector<int64> inc, exc;
    solve_heavy(hld[v], inc, exc);
    auto t_inc = exc;
    for (auto &x: t_inc) x += e.second;
    t_inc.insert(t_inc.begin(), 0);
    max(inc, exc);
    exc = inc;
    max(inc, t_inc);
    light.push_back({inc, exc, 0});
  }
  std::vector<int64> inc, exc;
  if (light.empty()) {
    inc = exc = {0};
  } else {
    solve_light(light, inc, exc);
  }
  if (heavy != -1) {
    hld[u].swap(hld[heavy]);
    hld[u].back().w = up_w;
  }
  hld[u].push_back({inc, exc, -inf});
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }

  dfs(0);

  std::vector<int64> inc, exc;
  solve_heavy(hld[0], inc, exc);
  std::vector<int64> ret;
  max(ret, inc); max(ret, exc);
  for (int i = 1; i <= n - 1; ++i) {
    if (i > 1) putchar(' ');
    if (i < (int)ret.size()) printf("%lld", ret[i]);
    else putchar('?');
  }
  puts("");
  return 0;
}
