#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using int64 = long long;

const int N = 3e5 + 10;

std::set<std::pair<int, int>> events[N];
int dsu[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> w(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &w[i]);
  for (int i = 0; i < n; ++i) dsu[i] = i;
  std::vector<int> a(m), b(m), s(m);
  std::vector<int64> as(m), bs(m), rest(m);
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  std::vector<bool> mark(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &s[i]);
    --a[i], --b[i];
    rest[i] = s[i];
    int bound = (s[i] + 1) / 2;
    events[a[i]].emplace(bound, i);
    events[b[i]].emplace(bound, i);
    if (bound <= w[a[i]] || bound <= w[b[i]]) {
      pq.push(i), mark[i] = true;
    }
  }

  std::vector<int> ret;
  while (!pq.empty()) {
    int e = pq.top();
    pq.pop(); mark[e] = false;
    int u = get(a[e]), v = get(b[e]);
    if (u == v || w[u] + w[v] >= s[e]) {
      events[u].erase({as[e] + (rest[e] + 1) / 2, e});
      events[v].erase({bs[e] + (rest[e] + 1) / 2, e});
      if (u != v) {
        ret.push_back(e + 1);
        if (events[u].size() > events[v].size()) std::swap(u, v);
        dsu[u] = v; w[v] += w[u];
        for (auto &e: events[u]) events[v].insert(e);
      }
    } else {
      int64 delta_a = w[u] - as[e], delta_b = w[v] - bs[e];
      events[u].erase({as[e] + (rest[e] + 1) / 2, e});
      events[v].erase({bs[e] + (rest[e] + 1) / 2, e});
      as[e] += delta_a;
      bs[e] += delta_b;
      rest[e] -= delta_a + delta_b;
      events[u].emplace(as[e] + (rest[e] + 1) / 2, e);
      events[v].emplace(bs[e] + (rest[e] + 1) / 2, e);
    }
    u = get(u); v = get(v);
    while (!events[u].empty() && events[u].begin()->first <= w[u]) {
      if (!mark[events[u].begin()->second]) {
        mark[events[u].begin()->second] = true;
        pq.push(events[u].begin()->second);
      }
      events[u].erase(events[u].begin());
    }
    while (!events[v].empty() && events[v].begin()->first <= w[v]) {
      if (!mark[events[v].begin()->second]) {
        mark[events[v].begin()->second] = true;
        pq.push(events[v].begin()->second);
      }
      events[v].erase(events[v].begin());
    }
  }
  printf("%d\n", (int)ret.size());
  for (auto &e: ret) printf("%d ", e);
  puts("");
  return 0;
}
