#include <cassert>
#include <cmath>
#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>

using uint64 = unsigned long long;
using uint32 = unsigned int;

constexpr uint32 S = 1e6 + 10;
constexpr uint32 N = 1.6e7;
constexpr uint32 M = 1e4;

uint64 sqf[S], tau[S];
int mu[N], sigma[N], e[N];
uint32 ps[M];

void prepare(uint32 n) {
  mu[1] = sigma[1] = 1;
  for (uint32 i = 2, m = 0; i <= n; ++i) {
    if (!sigma[i]) {
      sigma[i] = e[i] = 2;
      mu[i] = -1;
      if ((uint64)i * i <= n) ps[m++] = i;
    }
    for (uint32 j = 0, u = n / i; j < m && ps[j] <= u; ++j) {
      int p = ps[j], v = p * i;
      if (i % p == 0) {
        mu[v] = 0;
        e[v] = e[i] + 1;
        sigma[v] = sigma[i] / e[i] * e[v];
        break;
      } else {
        e[v] = 2;
        mu[v] = -mu[i];
        sigma[v] = sigma[i] * 2;
      }
    }
  }
  for (uint32 i = 1; i <= n; ++i) {
    e[i] = e[i - 1] + abs(mu[i]);
    mu[i] += mu[i - 1];
    sigma[i] += sigma[i - 1];
  }
}

uint64 sqf_count(uint64 n) {
  uint32 cn = cbrt(n);
  uint32 now = sqrt(n);
  uint64 ret = 0;
  for (uint32 i = 1; i <= cn; ++i) {
    uint32 next = sqrt(n / (i + 1));
    ret += (uint64)i * (mu[now] - mu[next]);
    now = next;
  }
  for (uint32 i = 1; i <= now; ++i) {
    ret += (mu[i] - mu[i - 1]) * (n / (i * i));
  }
  return ret;
}

uint64 sum_sigma(uint64 n) {
  auto out = [n] (uint64 x, uint32 y) {
    return x * y > n;
  };
  auto cut = [n] (uint64 x, uint32 dx, uint32 dy) {
    return x * x * dy >= n * dx;
  };
  const uint64 sn = sqrtl(n);
  const uint64 cn = pow(n, 0.34);//cbrtl(n);
  uint64 x = n / sn;
  uint32 y = n / x + 1;
  uint64 ret = 0;
  std::stack<std::pair<uint32, uint32>> stk;
  stk.emplace(1, 0);
  stk.emplace(1, 1);
  while (true) {
    uint32 lx, ly;
    std::tie(lx, ly) = stk.top();
    stk.pop();
    while (out(x + lx, y - ly)) {
      ret += x * ly + uint64(ly + 1) * (lx - 1) / 2;
      x += lx, y -= ly;
    }
    if (y <= cn) break;
    uint32 rx = lx, ry = ly;
    while (true) {
      std::tie(lx, ly) = stk.top();
      if (out(x + lx, y - ly)) break;
      rx = lx, ry = ly;
      stk.pop();
    }
    while (true) {
      uint32 mx = lx + rx, my = ly + ry;
      if (out(x + mx, y - my)) {
        stk.emplace(lx = mx, ly = my);
      } else {
        if (cut(x + mx, lx, ly)) break;
        rx = mx, ry = my;
      }
    }
  }
  for (--y; y > 0; --y) ret += n / y;
  return ret * 2 - sn * sn;
}

int main() {
  int T;
  scanf("%d", &T);
  std::vector<uint64> tests(T);
  for (int i = 0; i < T; ++i) {
    scanf("%llu", &tests[i]);
  }
  uint64 mx = *std::max_element(tests.begin(), tests.end());
  const uint32 bound = std::max<uint32>(10000, pow(mx, 0.6));
  prepare(bound);
  for (auto &&n: tests) {
    const uint32 sn = sqrt(n);
    for (uint32 i = 1; i <= sn; ++i) if (n / i >= bound) {
      sqf[i] = sqf_count(n / i);
      tau[i] = sum_sigma(n / i);
    }
    uint64 now = 0, ret = 0;
    for (uint64 i = 1, j; i <= n; i = j + 1) {
      uint64 v = n / i;
      j = n / v;
      uint64 next = (j <= bound ? e[j] : sqf[n / j]);
      ret += (next - now) * (v <= bound ? sigma[v] : tau[n / v]);
      now = next;
    }
    printf("%llu\n", ret);
  }
  return 0;
}
