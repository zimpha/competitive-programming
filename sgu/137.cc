#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<std::pair<int, int>> seq;
  std::vector<int> s(n, 1), t(n, 1);
  while (n != k) {
    seq.emplace_back(n, k);
    if (k < n) n -= k;
    else k -= n;
  }
  int m = 1;
  while (!seq.empty()) {
    std::tie(n, k) = seq.back();
    if (k < n) {
      int nn = 0;
      for (int i = 0; i < m; ++i) {
        t[nn++] = 0;
        while (s[i]--) t[nn++] = 1;
      }
      m = nn;
    } else {
      for (int i = 0; i < m; ++i) {
        t[i] = s[i] + 1;
      }
    }
    seq.pop_back();
    s.swap(t);
  }
  for (int i = 0; i < n; ++i) {
    printf("%d%c", s[i], " \n"[i == n - 1]);
  }
  return 0;
}
