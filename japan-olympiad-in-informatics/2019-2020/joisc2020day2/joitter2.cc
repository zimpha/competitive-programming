#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using int64 = long long;

const int N = 1e5 + 10;

std::set<int> in[N];
std::set<std::pair<int, int>> out[N];
int dsu[N], size[N];
int64 ret;

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void add(int u, int v) {
  int ru = get(u), rv = get(v);
  if (ru == rv) return;
  auto it = out[rv].lower_bound({ru, 0});
  if (it != out[rv].end() && it->first == ru) { // merge
    ret += (int64)size[ru] * size[rv] * 2;
    if (in[ru].size() + out[ru].size() > in[rv].size() + out[rv].size()) {
      std::swap(ru, rv);
    }
    std::vector<std::pair<int, int>> new_out;
    for (auto &e: out[ru]) {
      in[e.first].erase(e.second);
      ret -= size[e.first];
      if (e.first != rv) new_out.push_back(e);
    }
    out[ru].clear();
    ret -= (int64)size[ru] * in[ru].size();
    ret += (int64)size[ru] * in[rv].size();
    std::vector<int> new_in;
    for (auto &x: in[ru]) {
      int rx = get(x);
      out[rx].erase({ru, x});
      if (rx != rv) new_in.push_back(x);
    }
    in[ru].clear();
    dsu[ru] = rv; size[rv] += size[ru];
    for (auto &x: new_in) add(x, rv);
    for (auto &e: new_out) add(e.second, e.first);
  } else if (!in[rv].count(u)) {
    ret += size[rv];
    out[ru].emplace(rv, u);
    in[rv].insert(u);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) dsu[i] = i, size[i] = 1;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u - 1, v - 1);
    printf("%lld\n", ret);
  }
  return 0;
}
