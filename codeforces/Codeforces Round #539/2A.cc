#include <cstdio>
#include <algorithm>

int dp[200][200];

int main() {
  int n, v;
  scanf("%d%d", &n, &v);
  int ret = std::min(n - 1, v), p = 2;
  for (int i = v + 1; i < n; ++i) {
    ret += p;
    ++p;
  }
  printf("%d\n", ret);
  return 0;
}
