#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n), b(n - 1);
    for (int i = 0; i < n - 1; ++i) scanf("%*d%*d%d", &b[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int left = 0, right = n;
    while (left < right) {
      int mid = (left + right - 1) / 2;
      std::vector<int> c;
      for (int i = mid; i < n; ++i) c.push_back(a[i]);
      for (int i = 0; i < mid; ++i) c.push_back(1e9 + 10);
      bool valid = true;
      for (int i = 0; i < n - 1; ++i) {
        if (c[i] < b[i]) valid = false;
      }
      if (valid) right = mid;
      else left = mid + 1;
    }
    printf("%d\n", left);
  }
  return 0;
}
