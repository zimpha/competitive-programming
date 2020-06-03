#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> t(n);
    for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
    std::sort(t.begin(), t.end());
    int64 sum = 0;
    for (int i = 0; i < n - k; ++i) sum += t[i];
    if (t[n - 1] > sum) sum = t[n - 1];
    printf("%lld\n", sum);
  }
  return 0;
}
