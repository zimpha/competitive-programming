#include <bits/stdc++.h>

using LL = long long;

const int N = 100000000;

int p[N], m;
bool mark[N];

void sieve() {
  memset(mark, 1, sizeof(mark));
  mark[0] = mark[1] = m = 0;
  for (int i = 2; i < N; ++i) {
    if (mark[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mark[i * p[j]] = 0;
      if (i % p[j] == 0) break;
    }
  }
}

void process() {
  typedef std::pair<int, int> pii;
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> Q;
  Q.push({2, 2});
  for (int i = 0; i < N; ++i) if (mark[i]) p[i] = 1e9;
  p[2] = 2;
  for (; !Q.empty();) {
    int u = Q.top().second, pw = 1;
    int w = Q.top().first;
    Q.pop();
    if (w > p[u]) continue;
    while (pw < u) {
      for (int d = 0; d < 10; ++d) {
        int v = u / pw / 10 * (pw * 10) + d * pw + u % pw;
        if (v < N && mark[v]) {
          int cost = std::max(v, p[u]);
          if (cost < p[v]) {
            p[v] = cost;
            Q.push({cost, v});
          }
        }
      }
      pw *= 10;
    }
    for (int d = 1; d < 10; ++d) {
      int v = d * pw + u;
      if (v < N && mark[v]) {
        int cost = std::max(v, p[u]);
        if (cost < p[v]) {
          p[v] = cost;
          Q.push({cost, v});
        }
      }
    }
  }
}

LL run(int n) {
  LL ret = 0;
  for (int i = 2; i <= n; ++i) {
    if (mark[i] && p[i] > i) ret += i;
  }
  return ret;
}

int main() {
  sieve();
  process();
  std::cout << run(1000) << std::endl;
  std::cout << run(10000) << std::endl;
  std::cout << run(10000000) << std::endl;
  return 0;
}
