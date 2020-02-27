#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    int64 total = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      total += a[i];
    }
    int64 sum = 0, best = a[0];
    for (int i = 0; i + 1 < n; ++i) {
      if (sum <= 0) sum = a[i];
      else sum += a[i];
      if (sum > best) best = sum;
    }
    std::reverse(a.begin(), a.end());
    sum = 0;
    for (int i = 0; i + 1 < n; ++i) {
      if (sum <= 0) sum = a[i];
      else sum += a[i];
      if (sum > best) best = sum;
    }
    if (best >= total) puts("NO");
    else puts("YES");
  }
  return 0;
}
