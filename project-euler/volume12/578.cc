#include <bits/stdc++.h>

const int N = 30000;

int p[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!p[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      p[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

void dfs1(int d, int a, long now, long upp);
void dfs2(int d, int a, long now, long upp);
long ret;

void dfs1(int d, int a, long now, long upp) {
  if (d >= m) return;
  long tmp = 1;
  for (int i = 0; i <= a; ++i) {
    if (tmp > upp / p[d]) tmp = upp / p[d];
    tmp *= p[d];
  }
  if (now > 1 && tmp > upp / now) return;
  ret += now > 1;
  if (ret % 100000 == 0) std::cout << ret << std::endl;
  //std::cout << ret << ' ' << now << ' ' << p[d] << std::endl;
  for (int i = d; i < m; ++i) {
    if (now <= upp / p[i]) dfs2(i, a, now, upp);
    else break;
  }
}

void dfs2(int d, int a, long now, long upp) {
  now *= p[d];
  for (int i = 1; i <= a; ++i) {
    dfs1(d + 1, i, now, upp);
    if (now > upp / p[d]) break;
    now *= p[d];
  }
}

long run(long n) {
  ret = 0;
  dfs1(0, 100, 1, n);
  return ret;
}

int main() {
  sieve();
  //std::cout << run(100) << std::endl;
  //std::cout << run(1000000) << std::endl;
  std::cout << run(10000000000000ll) << std::endl;
  return 0;
}
