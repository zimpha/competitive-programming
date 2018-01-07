#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
#include <utility>

using pii = std::pair<int, int>;

constexpr int N = 1000 + 10;
constexpr int dx[] = {0, 0, 1, -1};
constexpr int dy[] = {1, -1, 0, 0};

char s[N][N];
int n, m;

void bfs(int x, int y, int &x1, int &x2, int &y1, int &y2) {
  std::queue<pii> queue;
  queue.emplace(x, y);
  s[x][y] = '.';
  x1 = x2 = x;
  y1 = y2 = y;
  while (!queue.empty()) {
    std::tie(x, y) = queue.front();
    if (x < x1) x1 = x;
    if (x > x2) x2 = x;
    if (y < y1) y1 = y;
    if (y > y2) y2 = y;
    queue.pop();
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m || s[xx][yy] != 'W') continue;
      s[xx][yy] = '.';
      queue.emplace(xx, yy);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%s", s[i]);
    }
    std::vector<std::vector<pii>> add(n), sub(n);
    std::vector<int> left(m), right(m);
    int total = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s[i][j] != 'W') continue;
        int x1, x2, y1, y2;
        bfs(i, j, x1, x2, y1, y2);
        if (x1 == 0 || x2 == n - 1 || y1 == 0 || y2 == m - 1) continue;
        add[x1 - 1].emplace_back(y1, y2);
        sub[x2 + 1].emplace_back(y1, y2);
        left[y1 - 1]++, right[y2 + 1]++;
        ++total;
      }
    }
    bool find = false;
    for (int i = 0; i < n && !find; ++i) {
      for (auto &&e: add[i]) {
        left[e.first - 1]--;
        right[e.second + 1]--;
        total--;
      }
      int l = -1, r = -1;
      for (int j = 0; j < m; ++j) {
        if (left[j]) l = j;
      }
      for (int j = m - 1; j >= 0; --j) {
        if (right[j]) r = j;
      }
      if (!total) find = true;
      if (l != -1 && r != -1 && l <= r) find = true;
      for (auto &&e: sub[i]) {
        left[e.first - 1]++;
        right[e.second + 1]++;
        total++;
      }
    }
    puts(find ? "YES" : "NO");
  }
  return 0;
}
