#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<char, int64>> s(n);
  for (int i = 0; i < n; ++i) {
    scanf(" %c%lld", &s[i].first, &s[i].second);
  }
  std::vector<std::pair<int64, int64>> as(n), bs(n);
  int64 cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i].first == '(') cnt += s[i].second;
    else cnt -= s[i].second;
    if (i) as[i] = {std::max(as[i - 1].first, cnt), std::min(as[i - 1].second, cnt)};
    else as[i] = {std::max(0ll, cnt), std::min(0ll, cnt)};
  }
  cnt = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (s[i].first == ')') cnt += s[i].second;
    else cnt -= s[i].second;
    if (i != n - 1) bs[n - 1 - i] = {std::max(bs[n - i - 2].first, cnt), std::min(bs[n - i - 2].second, cnt)};
    else bs[n - 1 - i] = {std::max(0ll, cnt), std::min(0ll, cnt)};
  }
  int q;
  scanf("%d", &q);
  for (int it = 0; it < q; ++it) {
    scanf("%d", &n);
    s.resize(n);
    for (int i = 0; i < n; ++i) {
      scanf(" %c%lld", &s[i].first, &s[i].second);
    }
    int64 cnt = 0, mx = 0, mi = 0;
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      if (s[i].first == '(') cnt += s[i].second;
      else cnt -= s[i].second;
      //if (i == 0) mx = mi = cnt;
      mx = std::max(mx, cnt), mi = std::min(mi, cnt);
      if (as[0].first + mi >= 0) continue;
      int l = 0, r = as.size() - 1;
      while (l < r) {
        int m = (l + r + 1) >> 1;
        if (as[m].first + mi < 0) l = m;
        else r = m - 1;
      }
      valid &= as[l].second + mx >= 0;
    }
    valid &= mx + as.back().second >= 0;
    valid &= mi + as.back().first >= 0;
    std::reverse(s.begin(), s.end());
    cnt = mx = mi = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i].first == ')') cnt += s[i].second;
      else cnt -= s[i].second;
      //if (i == 0) mx = mi = cnt;
      mx = std::max(mx, cnt), mi = std::min(mi, cnt);
      if (bs[0].first + mi >= 0) continue;
      int l = 0, r = bs.size() - 1;
      while (l < r) {
        int m = (l + r + 1) >> 1;
        if (bs[m].first + mi < 0) l = m;
        else r = m - 1;
      }
      valid &= bs[l].second + mx >= 0;
    }
    valid &= mx + bs.back().second >= 0;
    valid &= mi + bs.back().first >= 0;
    if (valid) puts("1");
    else puts("0");
  }
  return 0;
}
