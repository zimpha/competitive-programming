#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using int64 = long long;

bool check(int m, int x, std::vector<int> &a) {
  int64 sum = 0;
  for (int i = 0; i < a.size(); ++i) {
    sum += std::max(a[i] - i / x, 0);
  }
  return sum >= m;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n);
  int64 sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  if (sum < m) {
    puts("-1");
    return 0;
  }
  std::sort(a.begin(), a.end(), std::greater<int>());
  int l = 1, r = n;
  while (l < r) {
    int mid = (l + r - 1) >> 1;
    if (check(m, mid, a)) r = mid;
    else l = mid + 1;
  }
  printf("%d\n", l);
  return 0;
}
