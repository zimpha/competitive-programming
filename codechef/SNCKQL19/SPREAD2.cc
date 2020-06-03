#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    int64 sum = a[0];
    int ret = 0;
    for (int i = 1, j; i < n; ) {
      ++ret;
      int64 cnt = 0;
      for (j = 0; j < sum && i + j < n; ++j) cnt += a[j + i];
      sum += cnt;
      i += j;
    }
    printf("%d\n", ret);
  }
  return 0;
}
