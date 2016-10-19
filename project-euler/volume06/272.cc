#include <bits/stdc++.h>

using LL = long long;

const int N = 7000000;

int p[N], m;

void sieve() {
  for (int i = 2; i< N; ++i) {
    if (!p[i]) p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      p[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

LL dfs(LL n, int d, LL now, int cnt) {
  if (d == m) {
    if (cnt == 0) return now;
    else return 0;
  }
  int p = ::p[d];
  LL upp = n / p;
  if (now > upp) {
    if (cnt == 0) return now;
    else return 0;
  }
  LL tmp = now;
  for (int i = 0; i < cnt; ++i) {
    if (tmp > upp) return 0;
    tmp *= p;
  }
  LL ret = dfs(n, d + 1, now, cnt);
  if (p % 3 == 1) {
    while (cnt && now <= upp) {
      now *= p;
      ret += dfs(n, d + 1, now, cnt - 1);
    }
  } else if (p % 3 == 2) {
    while (now <= upp) {
      now *= p;
      ret += dfs(n, d + 1, now, cnt);
    }
  } else if (now <= upp) {
    now *= p;
    ret += dfs(n, d + 1, now, cnt);
    while (cnt && now <= upp) {
      now *= p;
      ret += dfs(n, d + 1, now, cnt - 1);
    }
  }
  return ret;
}


LL run(LL n) {
  return dfs(n, 0, 1, 5);
}

int main() {
  sieve();
  std::cout << run(100000000000ll) << std::endl;
  return 0;
}
