#include <cstdio>
#include <vector>
#include <tuple>
#include <set>

using int64 = long long;

const int N = 500000 + 10;

std::vector<std::pair<int, int>> query[N];
int64 bit[N];
int n, m, q;

void add(int x, int64 v) {
  for (; x <= n; x += ~x & x + 1) bit[x] += v;
}

int64 get(int x, int64 r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  std::vector<int> l(n + 1), r(n + 1), v(n + 1);
  for (int i = 1; i <= n; ++i) scanf("%d%d%d", &l[i], &r[i], &v[i]);
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    query[y].emplace_back(x, i);
  }
  std::set<std::tuple<int, int, int>> val;
  val.emplace(1, m, 0);
  std::vector<int64> ret(q);
  for (int i = 1; i <= n; ++i) {
    auto key = std::make_tuple(l[i], r[i], -1);
    auto it = val.lower_bound(key);
    if (it != val.begin()) --it;
    std::vector<std::tuple<int, int, int>> del, ins;
    ins.emplace_back(l[i], r[i], i);
    for (; it != val.end(); ) {
      int x = std::get<0>(*it);
      int y = std::get<1>(*it);
      int z = std::get<2>(*it);
      if (y < l[i]) {
        it++;
        continue;
      }
      if (x > r[i]) break;
      it = val.erase(it);
      add(z, -int64(y - x + 1) * v[z]);
      if (x <= l[i] && r[i] <= y) {
        if (x < l[i]) ins.emplace_back(x, l[i] - 1, z);
        if (y > r[i]) ins.emplace_back(r[i] + 1, y, z);
      } else if (l[i] <= x && y <= r[i]) {
      } else if (x < l[i]) {
        ins.emplace_back(x, l[i] - 1, z);
      } else if (y > r[i]) {
        ins.emplace_back(r[i] + 1, y, z);
      }
    }
    for (auto &e: ins) {
      add(std::get<2>(e), int64(std::get<1>(e) - std::get<0>(e) + 1) * v[std::get<2>(e)]);
      val.insert(e);
    }
    for (auto &q: query[i]) {
      ret[q.second] = get(n) - get(q.first - 1);
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}
