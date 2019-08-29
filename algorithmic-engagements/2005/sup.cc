#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using int64 = long long;
using pii = std::pair<int64, int64>;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<pii> es(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &es[i].first, &es[i].second);
  }
  std::sort(es.begin(), es.end());
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  int64 now = 0;
  for (int i = 0; i < n || !pq.empty(); ) {
    if (pq.empty()) {
      now = std::max<int64>(now, es[i].first);
    }
    while (i < n && es[i].first <= now) {
      pq.emplace(es[i].second, i);
      ++i;
    }
    int need = pq.top().first;
    int idx = pq.top().second;
    pq.pop();
    int64 next = now + need;
    if (i < n && next > es[i].first) {
      need -= es[i].first - now;
      es[idx].second = es[i].first;
      now = es[i].first;
      pq.emplace(need, idx);
    } else {
      es[idx].second = next;
      now = next;
    }
  }
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += es[i].second - es[i].first;
  }
  printf("%lld\n", ret);
  return 0;
}
