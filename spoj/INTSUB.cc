#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1e9 + 7;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int64> p(n * 2 + 1, 1);
    for (int i = 1; i <= n * 2; ++i) {
      p[i] = p[i - 1] * 2;
      if (p[i] >= mod) p[i] %= mod;
    }
    int64 ret = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = i + i; j <= n * 2; j += i) {
        ret += p[n * 2 - i - (j / i - 1)];
      }
      ret %= mod;
    }
    printf("Case %d: %lld\n", cas, ret);
  }
  return 0;
}
