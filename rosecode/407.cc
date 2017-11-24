#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>

using int64 = long long;

const int N = 1000000 + 10;

int64 s[N], c[N];
int64 ss[N];

void prepare() {
  int len = 2;
  s[0] = 0;
  s[1] = 1;
  for (int i = 1; len < N; ++i) {
    for (int j = 0; j < i && len < N; ++j) s[len++] = s[j];
  }
  for (int i = 1; i < N; ++i) {
    s[i] += s[i - 1];
    ss[i] = ss[i - 1] + s[i];
  }
  c[0] = 1;
  for (int i = 1; i < N; ++i) {
    c[i] = c[i - 1] + s[i - 1];
  }
}

int64 C(int64 n) {
  auto get = [](int64 n) {
    int64 x = sqrt(2 * (n - 2));
    while (2 + x * (x + 1) / 2 <= n) ++x;
    while (2 + x * (x + 1) / 2 > n) --x;
    return x;
  };
  auto calc = [&](int64 n) {
    // return |s_n|
    assert(n <= 2 + (int64)N * (N - 1) / 2);
    if (n < N) return c[n];
    int64 ret = c[N - 1];
    int64 v = get(N);
    int64 now = 2 + v * (v + 1) / 2;
    for (; now <= n; ) {
      int64 l = std::max(0ll, N - now) - 1, r = std::min(v, n - now);
      ret += (r - l) * c[v];
      ret += (r ? ss[r - 1] : 0) - (l - 1 >= 0 ? ss[l - 1] : 0);
      now += ++v;
    }
    return ret;
  };
  int64 ret = 0;
  while (n > N) {
    int64 x = get(n);
    ret += calc(x);
    n -= 2 + x * (x + 1) / 2;
  }
  ret += n ? s[n - 1] : 0;
  return ret;
}

int main() {
  prepare();
  std::cout << C(10) << std::endl;
  std::cout << C(10000) << std::endl;
  std::cout << C(100000000) << std::endl;
  std::cout << C(1000000000000000000) << std::endl;
  return 0;
}
