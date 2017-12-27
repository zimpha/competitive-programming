#include <cstdio>
#include <vector>

using int64 = long long;

namespace solve {
  const int N = 100000 + 10;
  std::vector<int> divs[N];
  std::vector<std::pair<int, int>> edges[N];
  int p[N], m;
  int64 f[N], mu[N];
  void init() {
    for (int i = 1; i < N; ++i) {
      for (int j = i; j < N; j += i) {
        divs[j].push_back(i);
      }
    }
    mu[1] = 1;
    m = 0;
    for (int i = 2; i < N; ++i) {
      if(!p[i]) p[m++] = i, mu[i] = -1;
      for (int j = 0; i * p[j] < N && j < m; ++j) {
        p[i * p[j]] = 1;
        if (i % p[j]) mu[i * p[j]] = -mu[i];
        else {
          mu[i * p[j]] = 0;
          break;
        }
      }
    }
  }
  void run(int n) {
    for (int i = 1; i <= n; ++i) {
      edges[i].clear();
      f[i] = n / i;
    }
    int64 ret = 0, A = 0, B = 0;
    for (int i = 1; i <= n; ++i) {
      ret += mu[i] * f[i] * f[i] * f[i];
    }
    std::vector<int> from, to, wei;
    m = 0;
    std::vector<int> deg(n + 1);
    for (int i = 1; i <= n; ++i) {
      if (!mu[i]) continue;
      for (int j = i; j <= n; j += i) {
        if (mu[j] && mu[j / i]) {
          for (auto &&k: divs[j / i]) {
            int x = i * k, y = j / k;
            if (x >= y) continue;
            deg[x]++;
            deg[y]++;
            B += (mu[x] * f[y] + mu[y] * f[x]) * f[j] * f[j];
            from.push_back(x);
            to.push_back(y);
            wei.push_back(f[j]);
            ++m;
          }
        }
      }
    }
    for (int i = 0; i < m; ++i) {
      int u = from[i], v = to[i], w = wei[i];
      if (deg[u] < deg[v]) edges[u].emplace_back(v, w);
      else edges[v].emplace_back(u, w);
    }
    std::vector<int> mark(n + 1, -1);
    for (int a = 1; a <= n; ++a) {
      for (auto &&e: edges[a]) mark[e.first] = e.second;
      for (auto &&e: edges[a]) {
        int b = e.first, w1 = e.second;
        for (auto &&ee: edges[b]) {
          int c = ee.first, w2 = ee.second;
          if (mark[c] != -1) {
            A += mu[a] * mu[b] * mu[c] * w1 * w2 * mark[c];
          }
        }
      }
      for (auto &&e: edges[a]) mark[e.first] = -1;
    }
    ret += A * 6 + B * 3;
    printf("%lld\n", ret);
  }
}

int main() {
  solve::init();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    solve::run(n);
  }
  return 0;
}
