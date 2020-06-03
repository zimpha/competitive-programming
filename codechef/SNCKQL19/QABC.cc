#include <vector>
#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
      scanf("%d", &b[i]);
    }
    bool valid = true;
    for (int i = 0; i < n - 2 && valid; ++i) {
      if (a[i] <= b[i]) {
        int64 delta = b[i] - a[i];
        a[i] += delta;
        a[i + 1] += delta * 2;
        a[i + 2] += delta * 3;
      } else {
        valid = false;
      }
    }
    valid &= a == b;
    if (valid) puts("TAK");
    else puts("NIE");
  }
  return 0;
}
