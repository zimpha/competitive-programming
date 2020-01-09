#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 3000 + 10;

int lcs[N][N], s[N];
int cnt[N], cur[N];
int n, m;

// 1. a b c b^r a^r => sort [b^r]
// 2. a b a^r c => sort [a^r c]
// 3. a b c b^r a^r => sort [c b^r]
// 4. a b a^r c => sort [b a^r c]
int solve(int l, int r, int o) {
  if (l < 0 || r >= n) return 0;
  for (int i = 1; i <= m; ++i) {
    cnt[i] = cur[i] = 0;
  }
  for (int i = l; i >= 0; --i) {
    if (i == l || s[i] >= s[i + 1]) cnt[s[i]]++;
    else break;
  }
  int p = 1, co = 0, q = m;
  while (q > 0 && cnt[q] == 0) --q;
  while (cnt[p] == 0) ++p;
  int sum = 0, ret = 0;
  for (int i = r; i < n && q; ++i) {
    if (s[i] == o) ++co;
    else {
      if (p == s[i]) sum -= std::min(cnt[p], cur[p]);
      ++cur[s[i]];
      if (p == s[i]) sum += std::min(cnt[p], cur[p]);
      while (p < q && cur[p] == cnt[p]) {
        ++p;
        sum += std::min(cnt[p], cur[p]);
      }
      if (cur[s[i]] > cnt[s[i]]) q = std::min(q, s[i]);
      while (q > 0 && cnt[q] == 0) --q;
      while (p > q) sum -= std::min(cnt[p], cur[p]), --p;
    }
    ret = std::max(ret, co + sum * 2);
    if (sum + co == i - r + 1 && l >= sum && i + 1 < n) {
      ret = std::max(ret, co + sum * 2 + 2 * lcs[l - sum][i + 1]);
    }
  }
  return ret;
}

int solve() {
  for (int i = 0; i < n; ++i) {
    for (int j = n - 1; j >= 0; --j) {
      if (s[i] != s[j]) lcs[i][j] = 0;
      else {
        lcs[i][j] = 1;
        if (i && j + 1 < n) lcs[i][j] += lcs[i - 1][j + 1];
      }
    }
  }
  for (int i = 1; i <= m; ++i) cnt[i] = 0;
  for (int i = 0; i < n; ++i) cnt[s[i]]++;
  int ret = *std::max_element(cnt + 1, cnt + 1 + m);
  for (int i = 0; i < n; ++i) {
    if (i && i + 1 < n) {
      int l = lcs[i - 1][i + 1];
      ret = std::max(ret, solve(i - 1 - l, i + 1 + l, 0) + 1 + 2 * l);
    }
    if (i && lcs[i - 1][i]) {
      int l = lcs[i - 1][i];
      ret = std::max(ret, solve(i - 1 - l, i + l, 0) + l * 2);
    }
    int o = -1;
    for (int j = i + 1; j < n && o == -1; ++j) {
      if (s[j] < s[i]) o = s[j];
    }
    if (o != -1) ret = std::max(ret, solve(i, i + 1, o));
  }
  return ret;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
  int ret1 = solve();
  std::reverse(s, s + n);
  for (int i = 0; i < n; ++i) s[i] = m + 1 - s[i];
  int ret2 = solve();
  printf("%d\n", std::max(ret1, ret2));
  return 0;
}
