#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5000 + 10;
const int mod = 1e9 + 7;

int low[N][4], upp[N][4];
int yl[N], yr[N], dp[N][N];
int sum_x[N], sum_y[N];
int n, m;

int get(int* dsu, int x) {
  if (x != dsu[x]) dsu[x] = get(dsu, dsu[x]);
  return dsu[x];
}

void sub(int &x, int y) {
  x -= y;
  if (x < 0) x += mod;
}

void add(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

void keep(int y, int l, int r) {
  if (yl[y] > yr[y]) return;
  l = std::max(l, yl[y]);
  r = std::min(r, yr[y]);
  if (l <= r) {
    for (int x = yl[y]; x < l; ++x) {
      sub(sum_x[x], dp[y][x]);
      sub(sum_y[y], dp[y][x]);
    }
    for (int x = yr[y]; x > r; --x) {
      sub(sum_x[x], dp[y][x]);
      sub(sum_y[y], dp[y][x]);
    }
  } else {
    for (int x = yl[y]; x <= yr[y];++x) {
      sub(sum_x[x], dp[y][x]);
      sub(sum_y[y], dp[y][x]);
    }
  }
  yl[y] = l, yr[y] = r;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
      yl[i] = 0, yr[i] = i;
      sum_x[i] = sum_y[i] = 0;
      for (int j = 0; j < 4; ++j) {
        low[i][j] = i;
        upp[i][j] = 0;
      }
    }
    for (int i = 0; i < m; ++i) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      low[r][x] = std::min(low[r][x], l);
      upp[r][x] = std::max(upp[r][x], l);
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        dp[i][j] = 0;
      }
    }
    sum_x[0] = sum_y[0] = 3;
    dp[0][0] = 3;
    int64 ret = 0;
    for (int i = 1; i <= n; ++i) {
      int x_min = upp[i][3], x_max = low[i][2];
      int y_min = upp[i][2], y_max = low[i][1];
      for (int j = 0; j < i; ++j) {
        sum_y[j] = (sum_y[j] % mod + mod) % mod;
        sum_x[j] = (sum_x[j] % mod + mod) % mod;
      }
      for (int y = 0; y < y_min; ++y) keep(y, i, i);
      for (int y = y_min; y < y_max; ++y) keep(y, x_min, x_max - 1);
      for (int y = y_max; y < i; ++y) keep(y, i, i);
      if (i == n) {
        for (int x = x_min; x < x_max; ++x) {
          ret += sum_x[x];
        }
      } else {
        for (int y = y_min; y < y_max; ++y) {
          add(dp[i][y], sum_y[y]);
        }
        for (int x = x_min; x < x_max; ++x) {
          add(dp[i][x], sum_x[x]);
        }
        for (int j = 0; j <= i; ++j) {
          add(sum_x[j], dp[i][j]);
          add(sum_y[i], dp[i][j]);
        }
      }
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}
