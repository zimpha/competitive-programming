#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 1e3 + 10, M = 5e3 + 10;

int dpL[N][M], dpR[N][M];
int a[N], n, m, c;

void update(int &x, int y) {
  if (x == -1 || x > y) x = y;
}

int ys[M], ny, mx[M * 2];
bool check(int a, int b, int *x, int *y) {
  ny = 0;
  for (int i = 0; i < c; ++i) {
    if (y[i] != -1) ys[ny++] = mx[i + c] = y[i];
    else mx[i + c] = m * c;
  }
  for (int i = c - 1; i > 0; --i) {
    mx[i] = std::min(mx[i << 1], mx[i << 1 | 1]);
  }
  std::sort(ys, ys + ny);
  for (int i = 0; i < c; ++i) if (x[i] != -1 && a + x[i] < m * c) {
    int ka = (a + x[i]) / c, ra = (a + x[i]) % c;
    int kb = (b + x[i]) / c, rb = (b + x[i]) % c;
    if (ka < kb) return true;
    // mc - b - x <= y < mc - a - x
    int e = std::lower_bound(ys, ys + ny, m * c - b - x[i]) - ys;
    if (e < ny && ys[e] < m * c - a - x[i]) return true;
    // y < mc - b - x, c - rb <= ry < c - ra
    int l = c - rb, r = c - ra, y = m * c;
    for (l += c, r += c; l < r; l >>= 1, r >>= 1) {
      if (l & 1) y = std::min(y, mx[l++]);
      if (r & 1) y = std::min(y, mx[--r]);
    }
    if (y < m * c - b - x[i]) return true;
  }
  return false;
}

bool check_brutal(int a, int b, int *x, int *y) {
  std::vector<int> xs, ys;
  for (int i = 0; i < c; ++i) if (x[i] != -1) xs.push_back(x[i]);
  for (int i = 0; i < c; ++i) if (y[i] != -1) ys.push_back(y[i]);
  std::sort(xs.begin(), xs.end());
  std::sort(ys.begin(), ys.end());
  for (auto &x: xs) if (a + x < m * c) {
    for (auto &y: ys) {
      if (a + x + y >= m * c) break;
      if (a + x + y < m * c && b + x + y >= m * c) return true;
      if ((a + x + y) / c < (b + x + y) / c) return true;
    }
  }
  return false;
}

int main() {
  scanf("%d%d%d", &n, &m, &c);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  std::sort(a + 1, a + n + 1);
  memset(dpL, -1, sizeof(dpL));
  memset(dpR, -1, sizeof(dpR));
  dpL[0][0] = dpR[n + 1][0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < c; ++j) if (dpL[i - 1][j] != -1) {
      update(dpL[i][j], dpL[i - 1][j]);
      update(dpL[i][(j + a[i]) % c], dpL[i - 1][j] + a[i]);
    }
  }
  for (int i = n; i >= 1; --i) {
    for (int j = 0; j < c; ++j) if (dpR[i + 1][j] != -1) {
      update(dpR[i][j], dpR[i + 1][j]);
      update(dpR[i][(j + a[i]) % c], dpR[i + 1][j] + a[i]);
    }
  }
  int ret = 0, sum = 0, cnt = 1;
  for (int i = 1; i + 1 <= n; ++i) {
    if (!check(a[i], a[i + 1], dpL[i - 1], dpR[i + 2])) ++cnt;
    else {
      ret += cnt * sum;
      sum += cnt;
      cnt = 1;
    }
  }
  ret += cnt * sum;
  printf("%d\n", ret);
  return 0;
}
