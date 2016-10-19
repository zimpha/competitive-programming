#include <bits/stdc++.h>

using LL = long long;

const int N = 100000000;

int e[N + 1], p[N + 1], d[N + 1], m;

void sieve() {
  d[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (e[i] == 0) p[m++] = i, e[i] = 1, d[i] = 2;
    for (int j = 0; j < m && p[j] * i <= N; ++j) {
      if (i % p[j] == 0) {
        d[i * p[j]] = d[i] / (e[i] + 1) * (e[i] + 2);
        e[i * p[j]] = e[i] + 1;
      } else {
        d[i * p[j]] = d[i] * 2;
        e[i * p[j]] = 1;
      }
    }
  }
}

LL run(int n, int m) {
  int h = 0, t = -1, *q = p;
  for (int i = 1; i < m; ++i) {
    while (h <= t && d[i] >= d[q[t]]) --t;
    q[++t] = i;
  }
  LL ret = 0;
  for (int i = m; i <= n; ++i) {
    while (h <= t && d[i] >= d[q[t]]) --t;
    q[++t] = i;
    ret += d[q[h]];
    while (h <= t && q[h] <= i - m + 1) ++h;
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(1000, 10) << std::endl;
  std::cout << run(100000000, 100000) << std::endl;
  return 0;
}
