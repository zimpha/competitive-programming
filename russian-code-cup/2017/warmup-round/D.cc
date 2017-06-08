#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10;

const int popcnt[4] = {0, 1, 1, 2};

int dp_min[N][4][4], dp_max[N][4][4];
int n, x, y;

bool valid(int knights, int knaves) {
  if (x == -1) return knaves == y;
  if (y == -1) return knights == x;
  return knaves == y && knights == x;
}

bool valid(int o, int knights, int knaves) {
  if (o) return valid(knights, knaves);
  else return !valid(knights, knaves);
}

bool check_left(int left, int mid) {
  int a[2][2] = {{left & 1, left >> 1}, {mid & 1, mid >> 1}};
  int knights_up = a[1][1] + a[0][0];
  int knaves_up = 2 - knights_up;
  int knights_down = a[1][0] + a[0][1];
  int knaves_down = 2 - knights_down;
  return valid(a[1][0], knights_up, knaves_up) && valid(a[1][1], knights_down, knaves_down);
}

bool check_mid(int left, int mid, int right) {
  int a[3][2] = {{left & 1, left >> 1}, {mid & 1, mid >> 1}, {right & 1, right >> 1}};
  int knights_up = a[0][0] + a[1][1] + a[2][0];
  int knaves_up = 3 - knights_up;
  int knights_down = a[0][1] + a[1][0] + a[2][1];
  int knaves_down = 3 - knights_down;
  return valid(a[1][0], knights_up, knaves_up) && valid(a[1][1], knights_down, knaves_down);
}

bool check_right(int mid, int right) {
  int a[2][2] = {{mid & 1, mid >> 1}, {right & 1, right >> 1}};
  int knights_up = a[0][1] + a[1][0];
  int knaves_up = 2 - knights_up;
  int knights_down = a[0][0] + a[1][1];
  int knaves_down = 2 - knights_down;
  return valid(a[0][0], knights_up, knaves_up) && valid(a[0][1], knights_down, knaves_down);
}

bool check_self(int mid) {
  int knights_up = mid >> 1;
  int knaves_up = 1 - knights_up;
  int knights_down = mid & 1;
  int knaves_down = 1 - knights_down;
  return valid(mid & 1, knights_up, knaves_up) && valid(mid >> 1, knights_down, knaves_down);
}

int main() {
  scanf("%d%d%d", &n, &x, &y);
  for (int i = 0; i < n; ++i) {
    for (int a = 0; a < 4; ++a) {
      for (int b = 0; b < 4; ++b) {
        dp_min[i][a][b] = 2 * n + 1;
        dp_max[i][a][b] = -1;
      }
    }
  }
  int best_min = n * 2 + 1, best_max = -1;
  if (n == 1) {
    for (int mid = 0; mid < 4; ++mid) {
      if (check_self(mid)) {
        best_min = std::min(best_min, popcnt[mid]);
        best_max = std::max(best_max, popcnt[mid]);
      }
    }
    if (best_max == -1) puts("-1");
    else printf("%d\n%d\n", best_min, best_max);
    return 0;
  }
  for (int a = 0; a < 4; ++a) {
    for (int b = 0; b < 4; ++b) {
      if (check_right(a, b)) {
        dp_min[1][a][b] = dp_max[1][a][b] = popcnt[a] + popcnt[b];
      }
    }
  }
  for (int i = 1; i < n - 1; ++i) {
    for (int left = 0; left < 4; ++left) {
      for (int mid = 0; mid < 4; ++mid) {
        if (dp_max[i][left][mid] == -1) continue;
        for (int right = 0; right < 4; ++right) {
          if (check_mid(left, mid, right)) {
            dp_max[i + 1][mid][right] = std::max(dp_max[i + 1][mid][right], dp_max[i][left][mid] + popcnt[right]);
            dp_min[i + 1][mid][right] = std::min(dp_min[i + 1][mid][right], dp_min[i][left][mid] + popcnt[right]);
          }
        }
      }
    }
  }
  for (int left = 0; left < 4; ++left) {
    for (int mid = 0; mid < 4; ++mid) {
      if (check_left(left, mid)) {
        best_min = std::min(best_min, dp_min[n - 1][left][mid]);
        best_max = std::max(best_max, dp_max[n - 1][left][mid]);
      }
    }
  }
  if (best_max == -1) puts("-1");
  else printf("%d\n%d\n", best_min, best_max);
  return 0;
}
