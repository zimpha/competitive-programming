// sort an array: only allow to swap a[i], a[j] if |i-j| = k
#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, k;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &k);
  int ret = 0;
  for (int r = 0; r < k; ++r) {
    std::vector<int> b;
    for (int i = r; i < n; i += k) {
      b.push_back(a[i]);
    }
    for (size_t i = 0; i < b.size(); ++i) {
      for (size_t j = 0; j < i; ++j) {
        if (b[j] > b[i]) ++ret;
      }
    }
    std::sort(b.begin(), b.end());
    for (int i = r; i < n; i += k) {
      a[i] = b[i / k];
    }
  }
  for (int i = 1; i < n; ++i) {
    if (a[i] < a[i - 1]) ret = -1;
  }
  printf("%d\n", ret);
  return 0;
}
