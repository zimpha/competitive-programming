#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n * 2 - 2);
  for (int i = 0; i < n * 2 - 2; ++i) scanf("%d", &a[i]);
  std::sort(a.begin(), a.end());
  bool valid = true;
  int bound = 0;
  std::vector<int> cnt(n), candidate(n);
  for (auto &x: a) candidate[x] = 1;
  for (int i = 0; i < n * 2 - 2; ++i) {
    if (a[i] > i + 1) valid = false;
    if (a[i] == i + 1) ++bound, candidate[a[i]] = 0;
    else cnt[a[i]]++;
  }
  if (!valid) {
    for (int i = 1; i < n; ++i) printf("-1 ");
    puts("");
    return 0;
  }
  std::vector<int64> ret(n, -1);

  int prev = 0, ptr = n - 1;
  int64 sum = 0;

  while (cnt[ptr] + prev < bound) {
    sum += (int64)cnt[ptr] * ptr;
    prev += cnt[ptr--];
  }
  ret[bound] = sum + int64(bound - prev) * ptr;

  for (int i = 1; i < n; ++i) if (candidate[i]) {
    --cnt[i], ++bound;
    if (i > ptr) sum -= i, --prev;
    while (cnt[ptr] + prev < bound) {
      sum += (int64)cnt[ptr] * ptr;
      prev += cnt[ptr--];
    }
    ret[bound] = sum + int64(bound - prev) * ptr;
  }
  for (int i = 1; i < n; ++i) {
    printf("%lld ", ret[i]);
  }
  puts("");
  return 0;
}
