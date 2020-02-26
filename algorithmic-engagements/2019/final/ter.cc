#include <cstdio>
#include <vector>

using int64 = long long;

struct Rect {
  int x1, y1;
  int x2, y2;
  int c;
};

const int N = 1000 + 10;

int sum12[N][N], sum23[N][N], sum2[N][N];

int64 solve(int n, int X, int Y, const std::vector<Rect> &rec) {
  for (int i = 0; i <= X + 1; ++i) {
    for (int j = 0; j <= Y + 1; ++j) {
      sum12[i][j] = sum23[i][j] = sum2[i][j] = 0;
    }
  }
  int64 total = 0;
  for (int i = 0; i < n; ++i) {
    total += rec[i].c;
    if (rec[i].x1 == 1 && rec[i].y1 == 1) {
      sum12[rec[i].x2][rec[i].y2] += rec[i].c;
    } else if (rec[i].x2 == X && rec[i].y2 == Y) {
      sum23[rec[i].x1][rec[i].y1] += rec[i].c;
    } else {
      sum2[rec[i].x1][rec[i].y1] += rec[i].c;
      sum2[rec[i].x1][rec[i].y2 + 1] -= rec[i].c;
      sum2[rec[i].x2 + 1][rec[i].y1] -= rec[i].c;
      sum2[rec[i].x2 + 1][rec[i].y2 + 1] += rec[i].c;
    }
  }
  for (int i = X; i >= 1; --i) {
    for (int j = Y; j >= 1; --j) {
      sum12[i][j] += sum12[i + 1][j] + sum12[i][j + 1] - sum12[i + 1][j + 1];
    }
  }
  for (int i = 1; i <= X; ++i) {
    for (int j = 1; j <= Y; ++j) {
      sum23[i][j] += sum23[i - 1][j] + sum23[i][j - 1] - sum23[i - 1][j - 1];
      sum2[i][j] += sum2[i - 1][j] + sum2[i][j - 1] - sum2[i - 1][j - 1];
    }
  }

  auto cost = [] (int64 x) { return x * (x - 1) / 2; };
  const int go[3][2] = {{1, 2}, {0, 2}, {0, 1}};

  int rest = total - sum12[1][1] - sum23[X][Y];
  int64 ret = std::max(cost(sum12[1][1] + rest) + cost(sum23[X][Y]), cost(sum12[1][1]) + cost(sum23[X][Y] + rest));
  for (int i = 1; i <= X; ++i) {
    for (int j = 1; j <= Y; ++j) {
      if (i == 1 && j == 1) continue;
      if (i == X && j == Y) continue;
      const int w[3] = {sum12[1][1] - sum12[i][j], sum2[i][j], sum23[X][Y] - sum23[i][j]};
      int c12 = sum12[i][j], c23 = sum23[i][j];
      int rest = total - sum12[1][1] - sum2[i][j] - sum23[X][Y];
      for (int mask = 0; mask < 8; ++mask) {
        int cnt[3] = {c23, 0, c12};
        for (int k = 0; k < 3; ++k) cnt[go[k][mask >> k & 1]] += w[k];
        int64 sum = 0;
        for (int k = 0; k < 3; ++k) sum += cost(cnt[k]);
        for (int k = 0; k < 3; ++k) {
          ret = std::max(ret, sum - cost(cnt[k]) + cost(cnt[k] + rest));
        }
      }
    }
  }
  return ret;
}

int main() {
  int n, X, Y;
  scanf("%d%d%d", &n, &X, &Y);
  std::vector<Rect> rec(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d%d", &rec[i].x1, &rec[i].y1, &rec[i].x2, &rec[i].y2, &rec[i].c);
  }
  int64 ret = solve(n, X, Y, rec);
  for (int i = 0; i < n; ++i) {
    int x1 = Y - rec[i].y2 + 1, x2 = Y - rec[i].y1 + 1;
    int y1 = rec[i].x1, y2 = rec[i].x2;
    rec[i].x1 = x1, rec[i].x2 = x2;
    rec[i].y1 = y1, rec[i].y2 = y2;
  }
  ret = std::max(ret, solve(n, Y, X, rec));
  printf("%lld\n", ret);
  return 0;
}
