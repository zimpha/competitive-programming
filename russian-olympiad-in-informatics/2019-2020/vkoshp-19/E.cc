#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e3 + 10;

char s[N][N];
int dp[N][N], from[N][N];
int suffix[N], prefix[N];
int n, m;

std::vector<int> solve_ud() {
  memset(dp, -1, sizeof(dp));
  for (int c = 0; c < m; ++c) {
    for (int r = 0; r < n; ++r) {
      prefix[r] = r == 0 ? 0 : prefix[r - 1];
      if (s[r][c] == 'D') ++prefix[r];
    }
    for (int r = n - 1; r >= 0; --r) {
      suffix[r] = r == n - 1 ? 0 : suffix[r + 1];
      if (s[r][c] == 'U') ++suffix[r];
    }
    for (int r = 0; r < n; ++r) {
      int choose = suffix[0] + prefix[n - 1];
      if (r) choose -= prefix[r - 1];
      if (r + 1 < n) choose -= suffix[r + 1];
      if (c == 0) dp[c][r] = choose;
      else {
        for (int dr = -1; dr <= 1; ++dr) if (0 <= dr + r && dr + r < n) {
          if (dp[c - 1][r + dr] + choose > dp[c][r]) {
            dp[c][r] = dp[c - 1][r + dr] + choose;
            from[c][r] = r + dr;
          }
        }
      }
    }
  }
  std::vector<int> border(m);
  int best_r = -1;
  for (int r = 0; r < n; ++r) {
    if (best_r == -1 || dp[m - 1][r] > dp[m - 1][best_r]) {
      best_r = r;
    }
  }
  for (int c = m - 1, r = best_r; c >= 0; --c) {
    border[c] = r;
    r = from[c][r];
  }
  return border;
}

std::vector<int> solve_lr() {
  memset(dp, -1, sizeof(dp));
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      prefix[c] = c == 0 ? 0 : prefix[c - 1];
      if (s[r][c] == 'R') ++prefix[c];
    }
    for (int c = m - 1; c >= 0; --c) {
      suffix[c] = c == m - 1 ? 0 : suffix[c + 1];
      if (s[r][c] == 'L') ++suffix[c];
    }
    for (int c = 0; c < m; ++c) {
      int choose = suffix[0] + prefix[m - 1];
      if (c) choose -= prefix[c - 1];
      if (c + 1 < m) choose -= suffix[c + 1];
      if (r == 0) dp[r][c] = choose;
      else {
        for (int dc = -1; dc <= 1; ++dc) if (0 <= dc + c && dc + c < m) {
          if (dp[r - 1][c + dc] + choose > dp[r][c]) {
            dp[r][c] = dp[r - 1][c + dc] + choose;
            from[r][c] = c + dc;
          }
        }
      }
    }
  }
  std::vector<int> border(n);
  int best_c = -1;
  for (int c = 0; c < m; ++c) {
    if (best_c == -1 || dp[n - 1][c] > dp[n - 1][best_c]) {
      best_c = c;
    }
  }
  for (int r = n - 1, c = best_c; r >= 0; --r) {
    border[r] = c;
    c = from[r][c];
  }
  return border;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  auto border_ud = solve_ud();
  auto border_lr = solve_lr();
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (s[r][c] == 'D' && r < border_ud[c]) {
        if (c < border_lr[r]) s[r][c] = 'L';
        else s[r][c] = 'R';
      } else if (s[r][c] == 'U' && r > border_ud[c]) {
        if (c < border_lr[r]) s[r][c] = 'L';
        else s[r][c] = 'R';
      } else if (s[r][c] == 'L' && c > border_lr[r]) {
        if (r < border_ud[c]) s[r][c] = 'U';
        else s[r][c] = 'D';
      } else if (s[r][c] == 'R' && c < border_lr[r]) {
        if (r < border_ud[c]) s[r][c] = 'U';
        else s[r][c] = 'D';
      }
    }
  }
  for (int i = 0; i < n; ++i) puts(s[i]);
  return 0;
}
