#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 20050321;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> cnt(n + 1);
  int p = 1;
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l;
    for (int j = 1; j < l; ++j) cnt[j] = cnt[j] * 2 % mod;
    for (int j = r + 1; j < n; ++j) cnt[j] = cnt[j] * 2 % mod;
    cnt[l] = (cnt[l] + p) % mod;
    cnt[r] = (cnt[r] + p) % mod;
    p = p * 2 % mod;
    int ret = p;
    for (int i = 1; i < n; ++i) ret = (ret + cnt[i]) % mod;
    printf("%d\n", ret);
  }
  return 0;
}
