#include <cstdio>
#include <vector>
#include <set>
#include <queue>

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::set<int>> row(n), col(m);
    std::vector<std::vector<bool>> removed(n, std::vector<bool>(m));
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    std::vector<std::vector<int>> balance(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        row[i].insert(j);
        col[j].insert(i);
        scanf("%d", &a[i][j]);
      }
    }
    std::set<std::pair<int, int>> pq;
    int64 ret = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        sum += a[i][j];
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          balance[i][j] += a[x][y] - a[i][j];
        }
        pq.emplace(balance[i][j], i * m + j);
      }
    }
    auto gao = [&](int x, int y) {
      auto ir = row[x].find(y);
      auto ir_n = ir; ++ir_n;
      auto ir_p = ir;
      if (ir_n != row[x].end()) {
        int yy = *ir_n;
        balance[x][yy] -= a[x][y] - a[x][yy];
      }
      if (ir != row[x].begin()) {
        --ir_p;
        int yy = *ir_p;
        balance[x][yy] = a[x][y] - a[x][yy];
      }
      if (ir_n != row[x].end() && ir != row[x].begin()) {
        int y1 = *ir_p, y2 = *ir_n;
        balance[x][y1] += a[x][y2] - a[x][y1];
        balance[x][y2] += a[x][y1] - a[x][y2];
      }
      auto ic = col[y].find(x);
      auto ic_n = ic; ++ic_n;
      auto ic_p = ic;
      if (ic_n != col[y].end()) {
        int xx = *ic_n;
        balance[xx][y] -= a[x][y] - a[xx][y];
      }
      if (ic != col[y].begin()) {
        --ic_p;
        int xx = *ic_p;
        balance[xx][y] = a[x][y] - a[xx][y];
      }
      if (ic_n != col[y].end() && ic != col[y].begin()) {
        int x1 = *ir_p, x2 = *ic_n;
        balance[x1][y] += a[x2][y] - a[x1][y];
        balance[x2][y] += a[x1][y] - a[x2][y];
      }
      row[x].erase(y);
      col[y].erase(x);
    };

    while (true) {
      std::vector<std::pair<int, int>> del;
      while (!pq.empty()) {
        auto e = *pq.rbegin();
        int x = e.second / m;
        int y = e.second % m;
        if (e.first <= 0) break;
        pq.erase(e);
        del.emplace_back(x, y);
        sum -= a[x][y];
        gao(x, y);
      }
      ret += sum;
      if (del.empty()) continue;
      std::set<int> mark;
      for (auto &e: del) {
        int x = e.first, y = e.second;
        auto ir1 = row[x].lower_bound(y);
        if (ir1 != row[x].end()) {
          int yy = *ir1;
          if (!mark.count(x * m + yy)) {
            mark.insert(x * m + yy);
            pq.erase({balance[x][yy], x * m + yy});
            pq.emplace(balance[x][yy], x * m + yy);
          }
        }
        auto ir2 = ir1;
      }
    }
  }
  return 0;
}
