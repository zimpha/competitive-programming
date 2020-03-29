#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n + 1), b(n), idx(n + 1);
  for (int i = 0; i <= n; ++i) scanf("%d", &a[i]), idx[i] = i;
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return a[x] < a[y];
  });
  std::sort(b.begin(), b.end());
  std::vector<int> suffix(n + 1), prefix(n + 1);
  for (int i = 0; i < n; ++i) {
    prefix[i] = std::max(a[idx[i]] - b[i], 0);
    if (i) prefix[i] = std::max(prefix[i], prefix[i - 1]);
  }
  for (int i = n; i >= 1; --i) {
    suffix[i] = std::max(a[idx[i]] - b[n - 1 - (n - i)], 0);
    if (i != n) suffix[i] = std::max(suffix[i], suffix[i + 1]);
  }
  for (int i = 0; i <= n; ++i) {
    int ret = 0;
    if (i) ret = std::max(ret, prefix[i - 1]);
    if (i != n) ret = std::max(ret, suffix[i + 1]);
    a[idx[i]] = ret;
  }
  for (int i = 0; i <= n; ++i) printf("%d ", a[i]);
  puts("");
  return 0;
}
