#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, k, s;
  scanf("%d%d%d", &n, &k, &s);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::sort(a.begin(), a.end());
  int ret = 0;
  s = s * k;
  while (!a.empty() && s > 0) {
    s -= a.back();
    a.pop_back();
    ++ret;
  }
  printf("%d\n", ret);
  return 0;
}
