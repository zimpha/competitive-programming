#include <bits/stdc++.h>

const int N = 200, M = 62;

long g[N][10];
long sg[N], fac[N];

long ds(long n) {
  long r = 0;
  for (; n; n /= 10) r += n % 10;
  return r;
}

bool less(long a[10], long b[10]) {
  long sa = 0, sb = 0;
  for (int i = 1; i < 10; ++i) sa += a[i], sb += b[i];
  if (sa != sb) return sa < sb;
  for (int i = 1; i < 10; ++i) {
    if (a[i] > b[i]) return true;
    if (a[i] < b[i]) return false;
  }
  return false;
}

void prepare() {
  fac[0] = 1;
  for (int i = 1; i < 10; ++i) fac[i] = fac[i - 1] * i;
  for (int i = 0; i < N; ++i) g[i][0] = -1;
  for (int fn = 1; fn < 10000000; ++fn) {
    long cnt[10], s = ds(fn);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 9, n = fn; i >= 1; --i) {
      cnt[i] = n / fac[i];
      n %= fac[i];
    }
    if (g[s][0] == -1 || less(cnt, g[s])) {
      for (int i = 0; i < 10; ++i) g[s][i] = cnt[i];
    }
  }
  for (int i = 1; i <= M; ++i) {
    sg[i] = 0;
    for (int j = 1; j < 10; ++j) sg[i] += g[i][j] * j;
  }
}

long calc(int n) {
  long x = n % 9, l = n / 9;
  for (int i = 0; i < l; ++i) x = x * 10 + 9;
  long cnt[10];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 9; i > 0; --i) {
    cnt[i] = x / fac[i];
    x %= fac[i];
  }
  long ret = 0;
  for (int i = 1; i < 10; ++i) ret += i * cnt[i];
  return sg[n] = ret;
}

long run(int n) {
  long ret = 0;
  for (int i = 1; i <= n && i <= M; ++i) ret += sg[i];
  for (int i = M + 1; i <= n; ++i) ret += calc(i);
  return ret;
}

int main() {
  prepare();
  std::cout << run(20) << std::endl;
  std::cout << run(150) << std::endl;
  return 0;
}

