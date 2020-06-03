#include <cstdio>
#include <vector>
#include <algorithm>

const int mod = 1e9 + 7;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int m = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    m = std::max(m, a[i]);
  }
  std::vector<int> val(m + 1);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int ret = (sum + 1 + mod - val[a[i]]) % mod;
    val[a[i]] = (val[a[i]] + ret) % mod;
    sum = (sum + ret) % mod;
  }
  printf("%d\n", sum);
  return 0;
}
