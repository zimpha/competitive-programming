#include <cmath>
#include <cstdio>
#include <algorithm>

const int N = 6e3 + 10;

char s[N];
int col[N], val[N];
int close[3][N], open[3][N];
int n;

int solve(int balance) {
  int sum[3] = {0, 0, 0};
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') val[i] = 1;
    else val[i] = -1;
    sum[col[i]] += val[i];
  }
  if (abs(sum[2]) % 2 != abs(balance) % 2) return -1;
  if (abs(sum[1]) % 2 != abs(balance) % 2) return -1;
  if (abs(sum[0]) % 2 != abs(balance) % 2) return -1;
  int ret = 0;
  int x[3] = {0, 0, 0}, y[3] = {0, 0, 0};
  for (int c = 0; c < 3; ++c) {
    int expected = c == 2 ? balance : -balance;
    if (sum[c] < expected) {
      for (int i = 0; i < n && sum[c] < expected; ++i) {
        if (col[i] == c && val[i] == -1) val[i] = 1, sum[c] += 2, ++ret, x[c]++;
      }
    } else {
      for (int i = n - 1; i >= 0 && sum[c] > expected; --i) {
        if (col[i] == c && val[i] == 1) val[i] = -1, sum[c] -= 2, ++ret, y[c]++;
      }
    }
    if (sum[c] != expected) return -1;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j) close[j][i] = i ? close[j][i - 1] : 0;
    if (val[i] == -1) close[col[i]][i]++;
  }
  open[0][n] = open[1][n] = open[2][n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < 3; ++j) open[j][i] = open[j][i + 1];
    if (val[i] == 1) open[col[i]][i]++;
  }
  int s02 = 0, s12 = 0;
  int m0 = 0, m1 = 0, m2 = 0, m02 = 0, m12 = 0;
  for (int i = 0; i < n; ++i) {
    if (col[i] == 0) s02 += val[i];
    else if (col[i] == 1) s12 += val[i];
    else if (col[i] == 2) s02 += val[i], s12 += val[i];
    if (s02 < 0) {
      int t0 = std::min(close[0][i], open[0][i + 1]);
      int t2 = std::min(close[2][i], open[2][i + 1]);
      int bound = (abs(s02) + 1) / 2;
      if (t0 + t2 < bound) return -1;
      m0 = std::max(m0, bound - t2);
      m2 = std::max(m2, bound - t0);
      m02 = std::max(m02, bound);
    }
    if (s12 < 0) {
      int t1 = std::min(close[1][i], open[1][i + 1]);
      int t2 = std::min(close[2][i], open[2][i + 1]);
      int bound = (abs(s12) + 1) / 2;
      if (t1 + t2 < bound) return -1;
      m1 = std::max(m1, bound - t2);
      m2 = std::max(m2, bound - t1);
      m12 = std::max(m12, bound);
    }
  }
  int b0 = std::min(open[0][0], close[0][n - 1]);
  int b1 = std::min(open[1][0], close[1][n - 1]);
  int b2 = std::min(open[2][0], close[2][n - 1]);
  int c0 = std::max(m0, m02 - b2);
  int c1 = std::max(m1, m12 - b2);
  int c2 = std::max(m2, std::max(m02 - c0, m12 - c1));
  if (c0 > b0 || c1 > b1 || c2 > b2) return -1;
  ret += 2 * (c0 + c1 + c2);
  return ret;
}

int main() {
  scanf("%d%s", &n, s);
  for (int i = 0; i < n; ++i) scanf("%d", &col[i]);
  int ret = -1;
  for (int b = -n; b <= n; ++b) {
    auto tmp = solve(b);
    if (tmp != -1 && (ret == -1 || tmp < ret)) ret = tmp;
  }
  printf("%d\n", ret);
  return 0;
}
