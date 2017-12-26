#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

using uint64 = unsigned long long;

constexpr int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
constexpr int dy[] = {-2, 2, -1, 1, -2, 2, -1, 1};

constexpr int S = 16777216, N = 30;

uint64 mark[S / 64];
int x[N], y[N], dis[S];
char g[N][N];
int n, m, s;

void decode(int mask) {
  for (int i = 0; i < s; ++i) {
    g[x[i]][y[i]] = mask >> (i * 2) & 3;
  }
}

int encode() {
  int mask = 0;
  for (int i = 0; i < s; ++i) {
    mask |= g[x[i]][y[i]] << (i * 2);
  }
  return mask;
}

void prepare(int src) {
  std::queue<int> queue;
  queue.emplace(src);
  mark[src >> 6] |= uint64(1) << (src & 63);
  dis[src] = 0;
  while (!queue.empty()) {
    decode(queue.front());
    src = queue.front();
    queue.pop();
    for (int i = 0; i < s; ++i) if (g[x[i]][y[i]]) {
      for (int d = 0; d < 8; ++d) {
        int xx = x[i] + dx[d], yy = y[i] + dy[d];
        if (xx < 0 || xx >= n || yy < 0 || yy >= m || g[xx][yy]) continue;
        std::swap(g[xx][yy], g[x[i]][y[i]]);
        int next = encode();
        if (~mark[next >> 6] >> (next & 63) & 1) {
          mark[next >> 6] |= uint64(1) << (next & 63);
          dis[next] = dis[src] + 1;
          queue.emplace(next);
        }
        std::swap(g[xx][yy], g[x[i]][y[i]]);
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int src = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%s", g[i]);
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '#') continue;
      if (g[i][j] == 'R') src |= 1 << (s * 2);
      if (g[i][j] == 'B') src |= 2 << (s * 2);
      if (g[i][j] == 'Y') src |= 3 << (s * 2);
      x[s] = i;
      y[s++] = j;
    }
  }
  prepare(src);
  int q;
  scanf("%d", &q);
  for (int it = 0; it < q; ++it) {
    int tar = 0;
    for (int i = 0; i < n; ++i) scanf("%s", g[i]);
    for (int i = 0; i < s; ++i) {
      int o = 0;
      if (g[x[i]][y[i]] == 'R') o = 1;
      if (g[x[i]][y[i]] == 'B') o = 2;
      if (g[x[i]][y[i]] == 'Y') o = 3;
      tar |= o << (i * 2);
    }
    if (mark[tar >> 6] >> (tar & 63) & 1) printf("%d\n", dis[tar]);
    else puts("-1");
  }
  return 0;
}
