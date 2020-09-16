#include <cstdio>
#include <cstring>
#include <string>

const int mod = 1e9 + 7;

// 0: x = l, 1: l < x < r, 2: x = r
int dp[2][8][7][70][2187];
bool eq[7][20], good[10];
std::string l[7], r[7];
char buf[20];
int pw[10];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

int main() {
  freopen("intervals.in", "r", stdin);
  freopen("intervals.out", "w", stdout);
  pw[0] = 1;
  for (int i = 0, x; i < 10; ++i) {
    if (i) pw[i] = pw[i - 1] * 3;
    scanf("%d", &x);
    if (x) good[i] = 1;
  }
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", buf);
    l[i] = buf;
    scanf("%s", buf);
    r[i] = buf;
    m = std::max<int>(m, r[i].size());
  }
  m += 1;
  std::string zero(m * 2, '0');
  for (int i = 0; i < n; ++i) {
    l[i] = zero.substr(0, m - l[i].size()) + l[i];
    r[i] = zero.substr(0, m - r[i].size()) + r[i];
    eq[i][0] = true;
    for (int j = 0; j < m; ++j) {
      eq[i][j + 1] = l[i][j] == r[i][j];
      eq[i][j + 1] &= eq[i][j];
    }
  }

  dp[0][0][0][0][0] = 1;
  for (int i = 0; i < m; ++i) {
    int u = i & 1, v = u ^ 1;
    for (int j = 0; j < n; ++j) {
      for (int carry = 0; carry < n; ++carry) {
        for (int sum = 0; sum <= j * 9; ++sum) {
          for (int mask = 0; mask < pw[n]; ++mask) {
            int ways = dp[u][j][carry][sum][mask];
            if (ways == 0) continue;
            int state = mask / pw[j] % 3;
            int dl = 0, dr = 9;
            if (state == 0 || eq[j][i]) dl = l[j][i] - '0';
            if (state == 2 || eq[j][i]) dr = r[j][i] - '0';
            for (int d = dl; d <= dr; ++d) {
              int new_state = 1;
              if ((state == 2 || eq[j][i]) && d == r[j][i] - '0') new_state = 2;
              if ((state == 0 || eq[j][i]) && d == l[j][i] - '0') new_state = 0;
              int new_mask = mask + (new_state - state) * pw[j];
              add(dp[u][j + 1][carry][sum + d][new_mask], ways);
            }
          }
        }
      }
    }
    bool is_zero = true;
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k <= i; ++k) {
        if (l[j][k] != '0') is_zero = false;
      }
    }
    for (int carry = 0; carry < n; ++carry) {
      for (int new_carry = 0; new_carry < n; ++new_carry) {
        int sum_l = std::max(0, carry * 10 - new_carry);
        int sum_r = (carry + 1) * 10 - new_carry;
        for (int sum = sum_l; sum < sum_r; ++sum) {
          for (int mask = 0; mask < pw[n]; ++mask) {
            int ways = dp[u][n][carry][sum][mask];
            if (ways == 0) continue;
            if (good[(sum + new_carry) % 10] || (sum + new_carry == 0 && mask == 0 && is_zero && i != m - 1)) {
              add(dp[v][0][new_carry][0][mask], ways);
            }
          }
        }
      }
    }
    memset(dp[u], 0, sizeof(dp[u]));
  }
  int ret = 0;
  for (int mask = 0; mask < pw[n]; ++mask) {
    add(ret, dp[m & 1][0][0][0][mask]);
  }
  printf("%d\n", ret);
  return 0;
}
