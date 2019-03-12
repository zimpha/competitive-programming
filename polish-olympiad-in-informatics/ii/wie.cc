#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>

struct Edge {
  int x, y, t;
};

int side(int x, int y, int o) {
  if (x == o || y == o) return 0;
  if (x < y) return x < o && o < y ? 1 : -1;
  else return y < o && o < x ? -1 : 1;
}

int solve(std::vector<Edge> edges) {
  std::vector<Edge> a, b;
  for (auto &&e: edges) {
    if (e.t == 1) a.push_back(e);
    else b.push_back(e);
  }
  if (b.empty()) return a.size();
  int p = rand() % b.size();
  int x = b[p].x, y = b[p].y;
  a.clear();
  b.clear();
  for (auto &&e: edges) {
    if (e.x == x && e.y == y) e.t = 1;
    if (side(x, y, e.x) >= 0 && side(x, y, e.y) >= 0) a.push_back(e);
    if (side(x, y, e.x) <= 0 && side(x, y, e.y) <= 0) b.push_back(e);
  }
  return std::max(solve(std::move(a)), solve(std::move(b)));
}

int main() {
  srand(time(0));
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<Edge> edges;
  for (int i = 0; i < n; ++i) {
    edges.push_back({i, (i + 1) % n, 1});
  }
  for (int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    edges.push_back({x - 1, y - 1, 0});
  }
  printf("%d\n", solve(edges));
  return 0;
}
