#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

const int N = 1e5 + 10;
const int mod = 998244353;

using int64 = long long;

std::vector<int> edges[N];
std::map<std::vector<int>, int> group;

std::vector<int> ways;
bool visited[N];
int nodes[N], idx[N];
int col[N];
int n, m;

void find_cc(int u) {
  idx[u] = m;
  nodes[m++] = u;
  visited[u] = 1;
  for (auto &v: edges[u]) {
    if (!visited[v]) find_cc(v);
  }
}

void dfs(int d, int c) {
  if (d == m) {
    ways[c - 1]++;
    return;
  }
  int mask = 0;
  for (auto &v: edges[nodes[d]]) if (idx[v] < d) {
    mask |= 1 << col[v];
  }
  for (int i = 1; i <= c + 1; ++i) if (~mask >> i & 1) {
    col[nodes[d]] = i;
    dfs(d + 1, std::max(c, i));
  }
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, u, v; i < m; ++i) {
    scanf("%d%d", &u, &v);
    edges[u - 1].push_back(v - 1);
    edges[v - 1].push_back(u - 1);
  }
  for (int i = 0; i < n; ++i) if (!visited[i]) {
    m = 0;
    find_cc(i);
    ways.assign(m, 0);
    dfs(0, 0);
    group[ways]++;
  }
  for (int i = 1; i <= n; ++i) {
    std::vector<int64> ways(7);
    ways[1] = i;
    for (int j = 2; j <= 6; ++j) {
      ways[j] = ways[j - 1] * (i - j + 1) % mod;
    }
    int64 ret = 1;
    for (auto &e: group) {
      int64 sum = 0;
      for (size_t k = 0; k < e.first.size(); ++k) {
        sum += ways[k + 1] * e.first[k] % mod;
      }
      ret = ret * pow_mod(sum % mod, e.second) % mod;
    }
    printf("%lld", ret);
    if (i == n) puts("");
    else putchar(' ');
  }
  return 0;
}
