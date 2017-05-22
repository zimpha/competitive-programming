#include <bits/stdc++.h>

const int N = 1000000;

int p[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (p[i]) continue;
    p[m++] = i;
    for (int j = i; j < N; j += i) p[j] = 1;
  }
}

long mul_mod(long a, long n, long m) {
  long r = 0;
  for (; n; n >>= 1) {
    if (n & 1) r = (r + a) % m;
    a = (a + a) % m;
  }
  return r;
}

void run(long n) {
  long last = 1;
  long double lg = 0;
  for (int i = 0; i < m && p[i] <= n; ++i) {
    long cnt = 0;
    for (long j = p[i]; j <= n; j *= p[i]) cnt += n / j;
    lg += log10(cnt * 2 + 1);
    last = mul_mod(last, cnt * 2 + 1, 20000000000ll);
  }
  last = (last - 1) / 2 + 1;
  lg -= log10(2);
  long rest = floor(lg) - 20 + 1;
  printf("%.0f[%ld]%010ld\n", floor(pow(10, lg - floor(lg) + 9)), rest, last);
}

int main() {
  sieve();
  run(100);
  run(1000000);
  return 0;
}
