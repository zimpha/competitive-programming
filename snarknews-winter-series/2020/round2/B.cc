#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

std::pair<int, int> a[N], buf[N];

int64 solve(int l, int r) {
  if (l + 1 == r) return 0;
  int m = (l + r) >> 1;
  int64 ret = solve(l, m) + solve(m, r);
  int x = l, y = m, z = l;
  while (x < m && y < r) {
    if (a[x].second > a[y].second) buf[z++] = a[x++];
    else buf[z++] = a[y++];
  }
  while (x < m) buf[z++] = a[x++];
  while (y < r) buf[z++] = a[y++];
  static int sl[N], sr[N];
  int tl = 0, tr = 0;
  for (int x = l, y = m; x < m; ++x) {
    while (y < r && a[y].second > a[x].second) {
      while (tr >= 1 && a[y].first <= a[sr[tr]].first) --tr;
      sr[++tr] = y++;
    }
    while (tl >= 1 && a[x].first >= a[sl[tl]].first) --tl;
    if (tr) {
      int bound = tl == 0 ? N : a[sl[tl]].second;
      int left = 1, right = tr + 1;
      while (left < right) {
        int mid = (left + right - 1) >> 1;
        if (mid > tr || a[sr[mid]].second <= bound) right = mid;
        else left = mid + 1;
      }
      ret += tr - left + 1;
    }
    sl[++tl] = x;
  }
  for (int i = l; i < r; ++i) a[i] = buf[i];
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  std::sort(a, a + n);
  int64 ret = solve(0, n);
  printf("%lld\n", ret);
  return 0;
}
