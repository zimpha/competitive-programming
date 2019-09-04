#include <cstdio>
#include <vector>

const int mod = 1e9 + 7;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> cnt(n);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x - 1]++;
  }
  int ret = 1, m = n;
  for (int i = 0; i < n; ++i) if (cnt[i]) {
    ret = 1ll * ret * cnt[i] % mod;
    m -= 1;
  }
  for (int i = 1; i <= m; ++i) {
    ret = 1ll * ret * i % mod;
  }
  printf("%d\n", ret);
  return 0;
}
