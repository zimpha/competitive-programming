#include <bits/stdc++.h>

using LL = long long;

__int128 bfs(int n) {
  std::vector<int> f(n, -1), pre(n, -1);
  std::queue<int> queue;
  for (int d = 1; d <= 2; ++d) {
    if (f[d % n] == -1) {
      f[d % n] = 0;
      queue.push(d % n);
    }
  }
  for (; !queue.empty(); queue.pop()) {
    int u = queue.front();
    for (int d = 0; d <= 2; ++d) {
      int v = (u * 10 + d) % n;
      if (f[v] == -1) {
        f[v] = f[u] + 1;
        pre[v] = u << 2 | d;
        queue.push(v);
      }
    }
  }
  __int128 res = 0, pw = 1, u;
  for (u = 0; pre[u] != -1;) {
    int d = pre[u] & 3;
    u = pre[u] >> 2;
    res += pw * d;
    pw *= 10;
  }
  if (u == 0) u = n;
  res += pw * u;
  return res;
}

LL run(int n) {
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    ret += LL(bfs(i) / i);
  }
  return ret;
}

int main() {
  assert(run(100) == 11363107);
  std::cout << run(10000) << std::endl;
}
