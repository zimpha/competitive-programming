#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;
const int M = 1e6 + 10 + N;

std::vector<std::pair<int, int>> white[N];
std::vector<std::pair<int, int>> black[N];
std::vector<int> idx_w[N], idx_b[N];
std::vector<int> edges[M];
int col_w[M], col_b[M];

void solve(int n, int m, std::vector<std::pair<int, int>> seg[], std::vector<int> idx[], int col[]) {
  for (int i = 0; i < m; ++i) edges[i].clear();
  for (int i = 1; i < n; ++i) {
    auto &u = seg[i], &v = seg[i - 1];
    for (size_t x = 0, y = 0; x < u.size(); ++x) {
      while (y < v.size() && v[y].second < u[x].first - 1) ++y;
      for (size_t j = y; j < v.size() && v[j].first <= u[x].second + 1; ++j) {
        edges[idx[i - 1][j]].push_back(idx[i][x]);
        edges[idx[i][x]].push_back(idx[i - 1][j]);
      }
    }
  }
  memset(col, -1, sizeof(int) * m);
  for (int i = 0; i < m; ++i) if (col[i] == -1) {
    std::vector<int> queue = {i};
    col[i] = i;
    for (size_t j = 0; j < queue.size(); ++j) {
      int u = queue[j];
      for (auto &v: edges[u]) if (col[v] == -1) {
        col[v] = i;
        queue.push_back(v);
      }
    }
  }
}

int main() {
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  for (int i = 0; i < m; ++i) {
    int x, l, r;
    scanf("%d%d%d", &x, &l, &r);
    black[x - 1].emplace_back(l - 1, r - 1);
  }
  int ws = 0, bs = 0;
  for (int i = 0; i < n; ++i) {
    auto &u = black[i], &v = white[i];
    if (u.empty()) v.emplace_back(0, n - 1);
    else {
      std::sort(u.begin(), u.end());
      int l = u[0].first, r = u[0].second, m = 0;
      for (auto &e: u) {
        if (e.first <= r + 1) r = std::max(r, e.second);
        else {
          u[m++] = {l, r};
          l = e.first, r = e.second;
        }
      }
      u[m++] = {l, r};
      u.resize(m);
      v.reserve(m + 1);
      for (int j = 0; j < m; ++j) {
        if (j) v.emplace_back(u[j - 1].second + 1, u[j].first - 1);
        else if (u[j].first != 0) v.emplace_back(0, u[j].first - 1);
      }
      if (u.back().second != n - 1) {
        v.emplace_back(u.back().second + 1, n - 1);
      }
    }
    int s = 0;
    for (auto &e: u) s += e.second - e.first + 1;
    for (auto &e: v) s += e.second - e.first + 1;
    assert(s == n);
    idx_b[i].resize(u.size());
    idx_w[i].resize(v.size());
    for (size_t j = 0; j < u.size(); ++j) idx_b[i][j] = bs++;
    for (size_t j = 0; j < v.size(); ++j) idx_w[i][j] = ws++;
  }
  solve(n, bs, black, idx_b, col_b);
  solve(n, ws, white, idx_w, col_w);

  auto get = [&] (int x, int y) -> std::pair<int, int> {
    auto &u = white[x], &v = black[x];
    int i = std::upper_bound(u.begin(), u.end(), std::make_pair(y, n)) - u.begin();
    if (i && u[i - 1].second >= y) return {0, idx_w[x][i - 1]};
    else {
      i = std::upper_bound(v.begin(), v.end(), std::make_pair(y, n)) - v.begin();
      return {1, idx_b[x][i - 1]};
    }
  };

  for (int i = 0; i < p; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    auto u = get(x1 - 1, y1 - 1);
    auto v = get(x2 - 1, y2 - 1);
    if (u.first != v.first) puts("NIE");
    else if (u.first == 0 && col_w[u.second] == col_w[v.second]) puts("TAK");
    else if (u.first == 1 && col_b[u.second] == col_b[v.second]) puts("TAK");
    else puts("NIE");
  }
  return 0;
}
