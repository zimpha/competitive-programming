#include <cstdio>
#include <vector>

const int N = 300;

char cake[N][N];
int sum[N][N];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i)
    scanf("%s", cake[i]);
  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      sum[i][j] = cake[i][j] - '0';
      sum[i][j] += sum[i + 1][j] + sum[i][j + 1];
      sum[i][j] -= sum[i + 1][j + 1];
    }
  }
  std::vector<int> row(k, n), col(k, m);
  bool valid = true;
  for (int i = 1, x = n - 1, y = m - 1; i < k && valid; ++i) {
    while (x >= 0 && sum[x][0] < i * k) --x;
    while (y >= 0 && sum[0][y] < i * k) --y;
    if (x < 0 || sum[x][0] != i * k) valid = false;
    if (y < 0 || sum[0][y] != i * k) valid = false;
    row[i] = x;
    col[i] = y;
  }
  row.push_back(0);
  col.push_back(0);
  if (!valid) {
    puts("NO");
    return 0;
  }
  for (int i = 1; i <= k && valid; ++i) {
    for (int j = 1; j <= k && valid; ++j) {
      if (sum[row[i]][col[j]] + sum[row[i - 1]][col[j - 1]] -
          sum[row[i]][col[j - 1]] - sum[row[i - 1]][col[j]] != 1)
        valid = false;
    }
  }
  if (valid) {
    puts("YES");
    for (int i = k - 1; i >= 1; --i) printf("%d ", row[i]);
    puts("");
    for (int i = k - 1; i >= 1; --i) printf("%d ", col[i]);
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}
