#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64> a(n);
  int64 delta = 0, sum = 0;
  int l = -1, r = -1, cnt = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
    sum += a[i];
    cnt += a[i] > 0;
    if (a[i] == 0) {
      r = i;
      if (l == -1) l = i;
    }
  }
  std::vector<int64> s, row;
  for (int i = 0, m = 0; i < l; ++i) {
    m++; s.push_back(a[i]);
    while (m >= 3 && s[m - 3] <= s[m - 2] && s[m - 2] >= s[m - 1]) {
      s[m - 3] = s[m - 3] - s[m - 2] + s[m - 1];
      s.pop_back(); s.pop_back();
      m -= 2;
    }
  }
  std::reverse(s.begin(), s.end());
  while (s.size() >= 2 && s.back() >= s[s.size() - 2]) {
    int64 x = s.back(); s.pop_back();
    int64 y = s.back(); s.pop_back();
    if (cnt & 1) delta += x - y;
    else delta -= x - y;
  }
  for (auto &x: s) row.push_back(x);
  s.clear();
  for (int i = r + 1, m = 0; i < n; ++i) {
    m++; s.push_back(a[i]);
    while (m >= 3 && s[m - 3] <= s[m - 2] && s[m - 2] >= s[m - 1]) {
      s[m - 3] = s[m - 3] - s[m - 2] + s[m - 1];
      s.pop_back(); s.pop_back();
      m -= 2;
    }
  }
  while (s.size() >= 2 && s.back() >= s[s.size() - 2]) {
    int64 x = s.back(); s.pop_back();
    int64 y = s.back(); s.pop_back();
    if (cnt & 1) delta += x - y;
    else delta -= x - y;
  }
  for (auto &x: s) row.push_back(x);
  s.clear();
  for (int i = l, m; i <= r; ++i) {
    if (a[i] == 0) {
      for (auto &x: s) row.push_back(x);
      s.clear();
      m = 0;
    } else {
      m++; s.push_back(a[i]);
      while (m >= 3 && s[m - 3] <= s[m - 2] && s[m - 2] >= s[m - 1]) {
        s[m - 3] = s[m - 3] - s[m - 2] + s[m - 1];
        s.pop_back(); s.pop_back();
        m -= 2;
      }
    }
  }
  std::sort(row.begin(), row.end());
  std::reverse(row.begin(), row.end());
  for (size_t i = 0; i < row.size(); ++i) {
    if (i & 1) delta -= row[i];
    else delta += row[i];
  }
  printf("%lld %lld\n", (delta + sum) / 2, (sum - delta) / 2);
  return 0;
}
