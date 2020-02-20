#include <cstdio>
#include <algorithm>

using pii = std::pair<int, int>;

const int N = 1001;

bool mark[N][N];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  if (n % 2 == 0 && m % 2 == 0) {
    if (k < n + m - 1 || k > n * m - 1) {
      puts("NIE");
      return 0;
    }
  } else {
    if (k < n + m - 2 || k > n * m - 1) {
      puts("NIE");
      return 0;
    }
  }
  puts("TAK");
  bool swap = false;
  if (n % 2 == 0) std::swap(n, m), swap = true;
  auto print = [&](int x1, int y1, int x2, int y2) {
    mark[x1][y1] = true;
    if (swap) printf("%d %d %d %d\n", y1, x1, y2, x2);
    else printf("%d %d %d %d\n", x1, y1, x2, y2);
  };

  int a = (n - 1) / 2, b = n - 1 - a;
  k -= n + m - 2;
  for (int i = 0, px = 1, py = 1; i < k && i < (m - 1) * a; ++i) {
    int nx = i / (m - 1) + 1;
    int ny = (nx & 1) ? 2 + i % (m - 1) : m - i % (m - 1);
    print(nx, ny, px, py);
    px = nx, py = ny;
  }
  k -= a * (m - 1);
  if (n == 2) --k;
  for (int i = 0, px = n, py = m; i < k && i < (m - 1) * b; ++i) {
    int nx = n - i / (m - 1);
    int ny = ((n - nx) & 1) ? i % (m - 1) + 1 : m - 1 - i % (m - 1);
    print(nx, ny, px, py);
    px = nx, py = ny;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (!mark[i][j] && !mark[i + 1][j]) print(i, j, i + 1, j);
    }
  }
  for (int j = 1; j < m; ++j) print(a + 1, j, a + 1, j + 1);
  return 0;
}
