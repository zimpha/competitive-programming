#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int mask = 0; mask < (1 << n); ++mask) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) sum += a[i];
      else sum -= a[i];
    }
    if (sum % 360 == 0) {
      puts("YES");
      return 0;
    }
  }
  puts("NO");
  return 0;
}