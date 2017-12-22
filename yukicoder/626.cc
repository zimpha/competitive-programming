#include <cstdio>
#include <utility>
#include <algorithm>

using int64 = long long;
using int128 = __int128;
using pii = std::pair<int64, int64>;

const int N = 5000 + 10;

pii items[N];
int64 cap, best;
int n;

void dfs(int d, int64 value, int64 weight) {
  if (cap < weight) return;
  best = std::max(best, value);
  if (d == n) return;
  int64 t_value = value, t_weight = cap - weight;
  int t_d;
  for (t_d = d; t_d < n && items[t_d].second <= t_weight; ++t_d) {
    t_value += items[t_d].first;
    t_weight -= items[t_d].second;
  }
  if (t_d == n || t_weight == 0) {
    best = std::max(best, t_value);
    return;
  }
  double t_opt = t_value + (double)items[t_d].first * t_weight / items[t_d].second;
  if (t_opt <= best) return;
  dfs(d + 1, value + items[d].first, weight + items[d].second);
  dfs(d + 1, value, weight);
}

int main() {
  scanf("%d%lld", &n, &cap);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &items[i].first, &items[i].second);
  }
  std::sort(items, items + n, [](const pii &a, const pii &b) {
      return (int128)a.first * b.second > (int128)b.first * a.second;
  });
  best = 0;
  dfs(0, 0, 0);
  printf("%lld\n", best);
  return 0;
}
