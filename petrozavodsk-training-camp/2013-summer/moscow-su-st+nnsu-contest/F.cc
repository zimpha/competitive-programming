#include <cstdio>
#include <array>
#include <algorithm>
#include <set>

using i64 = long long;

const int N = 30;
const int mod = 1e9 + 7;

using state = std::array<int, 6>;

int binom[N][N];
bool col[N][6];
std::set<state> mark;
int n;

int solve(const state &cnt) {
  int ret = 1, s = 0;
  for (int i = 0; i < 6; ++i) {
    ret = (i64)ret * binom[s + cnt[i]][cnt[i]] % mod;
    s += cnt[i];
  }
  return ret;
}

int dfs(int d, state &cnt) {
  if (mark.count(cnt)) return 0;
  mark.insert(cnt);
  if (d == n * n) return solve(cnt);
  int ret = 0;
  for (int i = 0; i < 6; ++i) if (col[d][i]) {
    cnt[i]++;
    ret += dfs(d + 1, cnt);
    cnt[i]--;
    ret %= mod;
  }
  return ret;
}

int main() {
  freopen("patterns.in", "r", stdin);
  freopen("patterns.out", "w", stdout);
  for (int i = 0; i < N; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
  }
  scanf("%d", &n);
  for (int i = 0; i < n * n; ++i) {
    static char buf[10];
    scanf("%s", buf);
    for (int j = 0; j < 6; ++j) {
      if (buf[j] == 'R') col[i][0] = 1;
      if (buf[j] == 'G') col[i][1] = 1;
      if (buf[j] == 'B') col[i][2] = 1;
      if (buf[j] == 'Y') col[i][3] = 1;
      if (buf[j] == 'C') col[i][4] = 1;
      if (buf[j] == 'M') col[i][5] = 1;
    }
  }
  state cnt;
  for (int i = 0; i < 6; ++i) cnt[i] = 0;
  int ret = dfs(0, cnt);
  printf("%d\n", ret);
  return 0;
}
