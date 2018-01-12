#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = unsigned long long;
using pii = std::pair<int64, int64>;

const int N = 2.16e7, M = 1e4, S = 316228;

std::vector<pii> sqf[S];
int64 sf[S], sg[S], nn, m;
int omega[S], mu[N], sigma[N], e[N];
int ps[M];

void prepare(int n) {
  mu[1] = sigma[1] = 1;
  for (int i = 2, m = 0; i <= n; ++i) {
    if (!sigma[i]) {
      sigma[i] = e[i] = 2;
      mu[i] = -1;
      if (i <= n / i) ps[m++] = i;
    }
    for (int j = 0, u = n / i; j < m && ps[j] <= u; ++j) {
      int p = ps[j], v = p * i;
      if (i % p == 0) {
        mu[v] = 0;
        e[v] = e[i] + 1;
        sigma[v] = sigma[i] / e[i] * e[v];
      } else {
        e[v] = 2;
        mu[v] = -mu[i];
        sigma[v] = sigma[i] * 2;
      }
    }
  }
  std::vector<int64> p2(20, 1), p3(20, 1);
  for (int i = 1; i < 20; ++i) {
    p2[i] = p2[i - 1] * 2;
    p3[i] = p3[i - 1] * 3;
  }
  for (int i = 1; i < S; ++i) if (sigma[i] == 2) {
    for (int j = i; j < S; j += i) omega[j]++;
  }
  for (int i = 1; i < S; ++i) if (mu[i]) {
    for (int j = i; j < S; j += i) if (mu[j]) {
      int e3 = omega[j / i], e2 = omega[j] - e3;
      sqf[i].emplace_back(j, p2[e2] * p3[e3]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    e[i] = e[i - 1] + sigma[i] * mu[i] * mu[i];
    sigma[i] += sigma[i - 1];
  }
}

int64 sum_sigma(int64 n) {
  int64 v = sqrt(n), ret = 0;
  for (int i = 1; i <= v; ++i) ret += n / i;
  ret = ret * 2 - (int64)v * v;
  return ret;
}

int64 sum_sigma_mu(int64 n) {
  int64 ret = 0, ud = cbrt(n);
  for (int64 d = 1; d <= ud; ++d) if (mu[d]) {
    const auto &s = sqf[d];
    int64 nd = n / d, v = sqrt(nd), sum = 0;
    size_t ui = std::upper_bound(s.begin(), s.end(), pii(v + 1, 0)) - s.begin();
    for (size_t i = 0; i < ui; ++i) {
      int64 a = s[i].first, b = s[i].second;
      int64 u = nd / (a * a);
      sum += mu[a] * b * (u <= m ? sigma[u] : sg[nn / u]);
    }
    ret += mu[d] * sum;
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  std::vector<int64> tests(T);
  for (int i = 0; i < T; ++i) {
    scanf("%lld", &tests[i]);
  }
  m = *std::max_element(tests.begin(), tests.end());
  m = cbrt(m);
  m = m * m;
  m = std::max<int64>(m, 10000);
  prepare(m);
  for (auto &&n: tests) {
    nn = n;
    int sq = sqrt(n);
    for (int i = 1; i <= sq; ++i) if (n / i > m) {
      sg[i] = sum_sigma(n / i);
    }
    for (int i = 1; i <= sq; ++i) if (n / i > m) {
      sf[i] = sum_sigma_mu(n / i);
    }
    int64 last_f = 0, ret = 0;
    for (int64 i = 1, j; i <= n; i = j + 1) {
      j = n / (n / i);
      int64 v = n / i;
      int64 now_f = j <= m ? e[j] : sf[n / j];
      ret += (now_f - last_f) * (v <= m ? sigma[v] : sg[n / v]);
      last_f = now_f;
    }
    printf("%llu\n", ret);
  }
  return 0;
}
