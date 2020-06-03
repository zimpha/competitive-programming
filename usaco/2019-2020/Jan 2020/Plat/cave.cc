#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1000 + 10, mod = 1e9 + 7;

char s[N][N];
std::vector<int> edges[N * N];
int parent[N * N], dsu[N * N], rank[N * N];
int idx[N][N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void merge(int x, int y) {
  x = get(x), y = get(y);
  if (x == y) return;
  if (rank[x] > rank[y]) std::swap(x, y);
  dsu[x] = y;
  if (rank[x] == rank[y]) ++rank[y];
}

int64 dfs(int u) {
  int64 cnt = 1;
  for (auto &v: edges[u]) {
    cnt = cnt * dfs(v) % mod;
  }
  return (cnt + 1) % mod;
}

int main() {
  freopen("cave.in", "r", stdin);
  freopen("cave.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  //n = m = 1000;
  //for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) s[i][j] = ".#"[rand() % 2];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      dsu[i * m + j] = i * m + j;
    }
  }
  memset(parent, -1, sizeof(parent));
  int size = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < m; ++j) if (s[i][j] == '.') {
      if (i + 1 < n && s[i + 1][j] == '.') merge(i * m + j, (i + 1) * m + j);
      if (j && s[i][j - 1] == '.') merge(i * m + j, i * m + j - 1);
    }
    std::vector<std::pair<int, int>> segs;
    segs.reserve(m);
    for (int j = 0; j < m; ++j) if (s[i][j] == '.') {
      segs.emplace_back(get(i * m + j), j);
    }
    std::sort(segs.begin(), segs.end());
    for (size_t j = 0; j < segs.size(); ++j) {
      if (j == 0 || segs[j].first != segs[j - 1].first) {
        idx[i][segs[j].second] = size++;
      } else {
        idx[i][segs[j].second] = idx[i][segs[j - 1].second];
      }
    }
    for (int j = 0; j < m; ++j) if (s[i][j] == '.' && i + 1 < n && s[i + 1][j] == '.') {
      edges[idx[i][j]].push_back(idx[i + 1][j]);
      parent[idx[i + 1][j]] = idx[i][j];
    }
  }
  for (int i = 0; i < size; ++i) {
    std::sort(edges[i].begin(), edges[i].end());
    edges[i].erase(std::unique(edges[i].begin(), edges[i].end()), edges[i].end());
  }
  int64 ret = 1;
  for (int i = 0; i < size; ++i) if (parent[i] == -1) {
    ret = ret * dfs(i) % mod;
  }
  printf("%lld\n", ret);
  return 0;
}
