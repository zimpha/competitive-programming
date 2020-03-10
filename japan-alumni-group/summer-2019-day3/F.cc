#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 998244353;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
  }
  std::vector<bool> mark(n);
  std::vector<int> cnt(n + 1);
  for (int i = 0; i < n; ++i) if (!mark[i]) {
    int len = 0;
    for (int j = i; !mark[j]; j = p[j], ++len) mark[j] = 1;
    cnt[len]++;
  }
  if (!cnt[1] && !cnt[2]) {
    puts("0");
    return 0;
  }
  int64 ret = 1;
  for (int i = 1; i <= n; ++i) if (cnt[i]) {
    if (i == 1) ret = cnt[i] == 1 ? 1 : pow_mod(cnt[i], cnt[i] - 2);
    else if (i == 2 && !cnt[1]) ret = pow_mod(2, cnt[2] - 1) % mod * pow_mod(cnt[2], cnt[2] - 1) % mod;
    else {
      int w = 0;
      for (int j = 1; j < i; ++j) if (i % j == 0) w += j * cnt[j];
      ret = ret * w % mod * pow_mod(w + i * cnt[i], cnt[i] - 1) % mod;
    }
  }
  printf("%lld\n", ret);
  return 0;
}
