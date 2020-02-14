#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const int N = 1000 + 10;

bool mark[N][N];
char s[N][N];
int idx[N][N];
int score[256], cnt[256];
int n, m;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

void bfs(int x, int y) {
  memset(cnt, 0, sizeof(cnt));
  std::vector<std::pair<int, int>> queue;
  queue.emplace_back(x, y);
  mark[x][y] = 1;
  for (size_t h = 0; h < queue.size(); ++h) {
    x = queue[h].first, y = queue[h].second;
    if (s[x][y] != '.') cnt[(int)s[x][y]]++;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
      if (mark[xx][yy] || s[xx][yy] == '#' || s[xx][yy] == '?' || s[xx][yy] == '+') continue;
      mark[xx][yy] = 1;
      queue.emplace_back(xx, yy);
    }
  }
  std::vector<int> cities;
  for (size_t h = 0; h < queue.size(); ++h) {
    x = queue[h].first, y = queue[h].second;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 0 || xx >= n || yy < 0 || yy > m) continue;
      if (s[xx][yy] != '#') continue;
      cities.push_back(idx[xx][yy]);
    }
  }
  std::sort(cities.begin(), cities.end());
  cities.erase(std::unique(cities.begin(), cities.end()), cities.end());
  int mx = 0;
  for (int i = 0; i < 256; ++i) {
    if (cnt[i] > mx) mx = cnt[i];
  }
  if (mx == 0) return;
  for (int i = 0; i < 256; ++i) {
    if (cnt[i] == mx) score[i] += cities.size() * 3;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  memset(idx, -1, sizeof(idx));
  for (int i = 0, cnt = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (idx[i][j] != -1 || s[i][j] != '#') continue;
      std::vector<std::pair<int, int>> queue = {{i, j}};
      idx[i][j] = cnt;
      for (size_t h = 0; h < queue.size(); ++h) {
        int x = queue[h].first, y = queue[h].second;
        for (int i = 0; i < 4; ++i) {
          int xx = x + dx[i], yy = y + dy[i];
          if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
          if (idx[xx][yy] != -1 || s[xx][yy] != '#') continue;
          idx[xx][yy] = cnt;
          queue.emplace_back(xx, yy);
        }
      }
      ++cnt;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mark[i][j] || s[i][j] == '#' || s[i][j] == '?' || s[i][j] == '+') continue;
      bfs(i, j);
    }
  }
  int mx = 0;
  for (int i = 0; i < 256; ++i) {
    if (score[i] > mx) mx = score[i];
  }
  printf("%d\n", mx);
  for (auto i : std::vector<char>{'R', 'Y', 'G', 'B', 'K'}) {
    if (score[(int)i] == mx) printf("%c ", i);
  }
  puts("");
  return 0;
}
