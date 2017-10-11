#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>

using int64 = long long;
using uint64 = unsigned long long;
using int128 = __int128;

int128 isqrt(int128 n) {
  int128 x = int128(sqrt(n));
  while (true) {
    int128 y = (x + n / x) >> 1;
    if (y >= x) break;
    x = y;
  }
  while (x * x <= n) ++x;
  while (x * x > n) --x;
  return x;
}

int128 icbrt(int128 n) {
  int128 x = int128(pow(n, 1.0 / 3));
  while (true) {
    int128 y = (2 * x + n / (x * x)) / 3;
    if (y >= x) break;
    x = y;
  }
  while (x * x * x <= n) ++x;
  while (x * x * x > n) --x;
  return x;
}

const int N = 2e6;

int mu[N], p[N], m;

void sieve(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!p[i]) p[m++] = i, mu[i] = -1;
    for (int j = 0, u = n / i, v; j < m && p[j] <= u; ++j) {
      p[v = p[j] * i] = 1;
      if (i % p[j]) mu[v] = mu[i] * -1;
      else {mu[v] = 0; break;}
    }
  }
}

void print(int128 n) {
  const uint64 base = 10000000000000000000llu;
  if (n <= base) printf("%llu\n", (uint64)n);
  else printf("%llu%018llu\n", uint64(n / base), uint64(n % base));
}

std::pair<int128, int128> squarefree(int128 n, int128 sub) {
  int128 cnt = 0, sum = -sub;
  int sq = sqrt(n);
  for (int i = 1; i <= sq; ++i) {
    int128 v = n / i / i, u = (int128)i * i;
    cnt += v * mu[i];
    v = v * (v + 1) / 2;
    sum += v * v * mu[i] * u * u * u;
  }
  return {cnt, sum};
}

int main() {
  int128 n = 0;
  std::string s;
  std::cin >> s;
  for (auto &&c: s) n = n * 10 + c - '0';
  int cn = std::min<int>(icbrt(n), 1000000);
  sieve(cn);
  int128 cnt = 0, sum = 0;
  int128 s_cnt = 0, s_sum = 0;
  for (int i = 1; i <= cn; ++i) {
    if (!mu[i]) continue;
    int128 cb = (int128)i * i * i;
    int128 tn = n / cb;
    int128 sq = isqrt(tn);
    cnt += sq;
    sum += cb * sq * (sq + 1) * (sq * 2 + 1) / 6;
    s_cnt += 1;
    s_sum += cb;
  }
  int u = isqrt(n / cn / cn / cn);
  for (int i = 1; i <= u; ++i) {
    int ub = icbrt(n / i / i);
    if (ub <= cn) continue;
    auto res = squarefree(ub, s_sum);
    cnt += res.first - s_cnt;
    sum += res.second * i * i;
  }
  print(cnt);
  print(sum);
  return 0;
}
