#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      b[i] = a[i];
    }
    std::sort(b.begin(), b.end());
    int s = 0;
    for (int i = 0; i < n; ++i) {
      if (a[i] == b[0]) {
        s = i;
        break;
      }
    }
    if (s == 0 && a.back() == b[0]) {
      s = n - 1;
      while (s > 0 && a[s - 1] == b[0]) --s;
    }
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      valid &= b[i] == a[(i + s) % n];
    }
    if (valid) puts("YES");
    else puts("NO");
  }
  return 0;
}
