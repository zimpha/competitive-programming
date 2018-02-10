#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>

const int N = 10000 + 10;
std::map<int, std::vector<int>> xs, ys;
std::map<std::pair<int, int>, int> id;
int dsu[N], x[N], y[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int solve(int n) {
  for (int i = 0; i < n; ++i) dsu[i] = i;
  std::vector<std::pair<int, int>> hor, ver;
  int ret = 0;
  for (auto &&e: xs) {
    auto &v = e.second;
    std::sort(v.begin(), v.end());
    if (v.size() & 1) return 0;
    for (size_t i = 0; i < v.size(); i += 2) {
      int x = id[{e.first, v[i]}];
      int y = id[{e.first, v[i + 1]}];
      ver.emplace_back(x, y);
      dsu[get(x)] = get(y);
      ret += v[i + 1] - v[i];
    }
  }
  for (auto &&e: ys) {
    auto &v = e.second;
    std::sort(v.begin(), v.end());
    if (v.size() & 1) return 0;
    for (size_t i = 0; i < v.size(); i += 2) {
      int x = id[{v[i], e.first}];
      int y = id[{v[i + 1], e.first}];
      hor.emplace_back(x, y);
      dsu[get(x)] = get(y);
      ret += v[i + 1] - v[i];
    }
  }
  for (int i = 0; i < n; ++i) {
    if (get(i) != get(0)) return 0;
  }
  for (auto &&a: ver) {
    for (auto &&b: hor) {
      if (x[b.first] < x[a.first] && x[a.first] < x[b.second] &&
          y[a.first] < y[b.first] && y[b.first] < y[a.second]) return 0;
    }
  }
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    xs[x[i]].emplace_back(y[i]);
    ys[y[i]].emplace_back(x[i]);
    id[{x[i], y[i]}] = i;
  }
  printf("%d\n", solve(n));
  return 0;
}
